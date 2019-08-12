#include "BIOChipON_State.h"
#include "TextNTO_State.h"
#include "BIOChipManager.h"

namespace EVCorporation
{
	namespace EVStates
	{
		void BIOChipON_State::ClearPIN() 
		{
			m_CloneIDIndex = 0;
			
			for (unsigned short int i=0;i<m_CloneID_len;i++)
			{
				m_CloneID[i] = 0;
			}
			
			m_ResetTS = true;
		}
		
		BIOChipON_State::~BIOChipON_State ()
		{
			
			delete[] m_CloneID;
			delete m_BlockedState;
		}
		
		BIOChipON_State::BIOChipON_State (Keypad* keypad, EVState* previous_state, EVState* next_state,const char *message, unsigned short int message_len, unsigned short int PIN_len, unsigned long state_creation_time) : EVState( keypad, previous_state, next_state, state_creation_time ) 
		{
			m_CurrentTS = millis();
			
			m_CloneID = new char[PIN_len]();
			
			m_CloneID_len = PIN_len;
						
			m_Message = new char[message_len]();
			
			for ( int i=0; i < message_len ; i++ ) 
			{
				m_Message[i] = message[i];
			}
			
			m_BlockedState = new TextNTO_State(keypad, this, nullptr, m_CurrentTS, m_TooManyError, 15, 10000, false, true);
			
			ClearPIN();
		}
		
		
		EVState* BIOChipON_State::loop()
		{
			if ( m_ResetTS ) 
			{
				Serial.println("Reset user TO");
				m_CurrentTS = millis();
				m_ResetTS = false;
			}
			
			GetDisplay()->printPINPage(m_Message, m_CloneID, m_CloneID_len);
			
			char button_pressed =GetKeypad()->getKey();
			
			if ( button_pressed )
			{
				m_CurrentTS = millis();
				
				m_CloneID[m_CloneIDIndex] = button_pressed;
				Serial.print(m_CloneID[m_CloneIDIndex]);
				m_CloneIDIndex++;
				
				if ( m_CloneIDIndex > m_CloneID_len - 1 )
				{
					bool pin_checked = true;
					BIOChipManager *BIOM = BIOChipManager::GetInstance();
					
					pin_checked = BIOM->CheckBIOChipPIN(m_CloneID);
										
					if (pin_checked) 
					{
						BIOM->EnableBIOChip(m_CloneID);
						
						GetDisplay()->clear();
						Serial.println("CLONE ID Ok");
						
						EVState *next_state = GetNextState();
					
						if ( next_state == nullptr) 
						{
							Serial.println("No Nextstate Setted");
							ClearPIN();
							return this;
						}
						
						delete GetPreviousState();
						
						next_state->SetStateCreationTimestamp ( millis());
						
						return next_state;
					}
					else
					{
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
				Serial.println("User PIN timeout");
				GetDisplay()->clear();
				return GetPreviousState();
			}
			
			return this;
		}
	}
}