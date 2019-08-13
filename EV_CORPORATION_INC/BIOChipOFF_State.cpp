#include "BIOChipOFF_State.h"
#include "TextNTO_State.h"
#include "Menu_State.h"
#include "BIOChipDetached_State.h"
#include "BIOChipManager.h"

namespace EVCorporation
{
	namespace EVStates
	{
		void BIOChipOFF_State::ClearPIN() 
		{
			m_CloneIDIndex = 0;
			
			for (unsigned short int i=0;i<m_CloneID_len;i++)
			{
				m_CloneID[i] = 0;
			}
			
			m_ResetTS = true;
		}
		
		BIOChipOFF_State::~BIOChipOFF_State ()
		{
			
			delete[] m_CloneID;
			delete m_BlockedState;
		}
		
		
		void BIOChipOFF_State::SetSuccessPreviousState(EVState* previous_state)
		{
			if ( previous_state == nullptr )
			{
				return;
			}
			
			m_DeactivationSuccessState->SetPreviousState(previous_state);
      m_DeactivationSuccessState->SetNextState(previous_state);
		}
		
		BIOChipOFF_State::BIOChipOFF_State (Keypad* keypad, EVState* previous_state, EVState* next_state,const char *message, unsigned short int message_len, unsigned short int PIN_len, unsigned long state_creation_time) : EVState( keypad, previous_state, next_state, state_creation_time ) 
		{
			m_CurrentTS = millis();
			
			m_CloneID = new char[PIN_len+1]();
			m_CloneID[3] = 0;
			m_CloneID_len = PIN_len;
						
			m_Message = new char[message_len]();
			
			for ( int i=0; i < message_len ; i++ ) 
			{
				m_Message[i] = message[i];
			}
			
			m_DeactivationSuccessState = new BIOChipDetached_State(keypad,nullptr, nullptr, m_CurrentTS,m_DeactivatedBIOChip, 32, 15, false, true);
			
			m_AlreadyDetachedState = new TextNTO_State(keypad, this, nullptr, m_CurrentTS, m_AlreadyDetachedError, 33, 5, false, false);
									
			m_DeactivatingState = new TextNTO_State(keypad, m_DeactivationSuccessState, nullptr, m_CurrentTS, m_DeactivatingBIOChip, 28, 5, false, false);
			
			DeactivateBIOChipMenu[0] = m_DeactivatingState;
			DeactivateBIOChipMenu[1] = this;
			
			m_DeactivationMenuState =  new Menu_State(keypad, nullptr, DeactivateBIOChipMenu, m_DeactivationChoices, m_DeactivationKeys, 2, m_DeactivateBIOChip, 16, millis());
			m_DeactivationMenuState->SetPreviousState(this);
			
			m_BlockedState = new TextNTO_State(keypad, this, nullptr, m_CurrentTS, m_TooManyError, 15, 10, true, false);
			SetNextState(m_DeactivationMenuState);
			ClearPIN();
		}
		
		
		EVState* BIOChipOFF_State::loop()
		{
			if ( m_ResetTS ) 
			{
				m_CurrentTS = millis();
				m_ResetTS = false;
			}
			
			GetDisplay()->printPINPage(m_Message, m_CloneID, m_CloneID_len);
			
			char button_pressed =GetKeypad()->getKey();
			
			if ( button_pressed )
			{
				m_CurrentTS = millis();
				
				m_CloneID[m_CloneIDIndex] = button_pressed;
		
				m_CloneIDIndex++;
				
				if ( m_CloneIDIndex > ( m_CloneID_len - 1) )
				{
					bool pin_checked = true;
					BIOChipManager *BIOM = BIOChipManager::GetInstance();
					
					pin_checked = BIOM->CheckBIOChipPIN(m_CloneID);
					
					Serial.print(m_CloneID);
					
					if ( pin_checked ) 
					{
						if ( !BIOM->IsEnabled(m_CloneID) ) 
						{		
								Serial.println(" Already detached");
								//already detached
								m_ResetTS = true;
								GetDisplay()->clear();
								m_AlreadyDetachedState->SetStateCreationTimestamp( millis());
								return m_AlreadyDetachedState;
						}
						
						GetDisplay()->clear();
						Serial.println(" Clone ID Ok... detaching");
						
						EVState *next_state = GetNextState();

						if ( next_state == nullptr) 
						{
							Serial.println("No Nextstate Setted");
							
							return this;
						}
						
						m_DeactivationSuccessState->SetCloneID(m_CloneID);
						ClearPIN();
						next_state->SetStateCreationTimestamp ( millis());
						return next_state;
					}
					else
					{
						Serial.print(m_CloneID);
						Serial.println(" Clone ID not matching");
						ClearPIN();
						m_ErrorCount++;
						
						if (m_ErrorCount>2)
						{
							m_ResetTS = true;
							m_ErrorCount = 0;
							
							GetDisplay()->clear();
							
							//not removing previous state because going to blocked then returning back
							m_BlockedState->SetStateCreationTimestamp( millis());
							return m_BlockedState;
						}
					}
				}
			}
		
			if ( millis() - m_CurrentTS >= STATE_TIME_OUT_MS )
			{
				m_ErrorCount = 0;
				m_ResetTS = true;
				Serial.println("Clone ID timed out");
				GetDisplay()->clear();
				return GetPreviousState();
			}
			
			return this;
		}
	}
}
