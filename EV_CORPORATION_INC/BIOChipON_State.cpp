#include "BIOChipON_State.h"
#include "TextNTO_State.h"
#include "Menu_State.h"
#include "BIOChipManager.h"
#include "DisplayManager.h"

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
		
		
		void BIOChipON_State::SetErrorPreviousState(EVState* previous_state)
		{
			if (previous_state==nullptr)
			{
				return;
			}
			
			if (m_ErrorState==nullptr)
			{
				  return;
			}
			
			m_ErrorState->SetPreviousState(previous_state);
      m_ErrorState->SetNextState(previous_state);
		}
		
		BIOChipON_State::BIOChipON_State (Keypad* keypad, EVState* previous_state, EVState* next_state,const char *message, unsigned short int message_len, unsigned short int PIN_len, unsigned long state_creation_time) : EVState( keypad, previous_state, next_state, state_creation_time ) 
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
			
			m_ErrorState = new TextNTO_State(keypad, nullptr, nullptr, m_CurrentTS, m_ActivationError, 32, 15, true, true);
      m_ErrorState->SetTextColor(TextColors::Red);
      m_ErrorState->SetLED(TextColors::Green, true );
      
			m_ActivatingState = new TextNTO_State(keypad, m_ErrorState, nullptr, m_CurrentTS, m_ActivatingBIOChip, 15, 5, false, false);
			m_ActivatingState->SetLoader();
      m_ActivatingState->SetLED(TextColors::Blue);
      
			ActivateBIOChipMenu[0] = m_ActivatingState;
			ActivateBIOChipMenu[1] = this;
			
			m_ActivationMenuState =  new Menu_State(keypad, nullptr, ActivateBIOChipMenu, m_ActivationChoices, m_ActivationKeys, 2, m_ActivateBIOChip,18, millis());
			m_ActivationMenuState->SetPreviousState(this);
			
			m_BlockedState = new TextNTO_State(keypad, this, nullptr, m_CurrentTS, m_TooManyError, 15, 10, true, false);
			SetNextState(m_ActivationMenuState);
			ClearPIN();
		}
		
		
		EVState* BIOChipON_State::loop()
		{
      SetLEDColor();
			if ( m_ResetTS ) 
			{
				m_CurrentTS = millis();
				m_ResetTS = false;
			}
			
			GetDisplay()->printPINPage(m_Message, m_CloneID, m_CloneID_len);
      GetDisplay()->SetLoader(HasLoader(),STATE_TIME_OUT_MS);
     
			char button_pressed =GetKeypad()->getKey();
			
			if ( button_pressed )
			{
				m_CurrentTS = millis();
				
				if ( HasLoader() )
            GetDisplay()->ResetLoader();
       
				m_CloneID[m_CloneIDIndex] = button_pressed;
		
				m_CloneIDIndex++;
				
				if ( m_CloneIDIndex > ( m_CloneID_len - 1) )
				{
					bool pin_checked = true;
					BIOChipManager *BIOM = BIOChipManager::GetInstance();
					
					pin_checked = BIOM->CheckBIOChipPIN(m_CloneID);
							Serial.print(pin_checked);			
					if ( pin_checked ) 
					{
						BIOM->EnableBIOChip(m_CloneID);
						
						
						if (HasLoader())
                  GetDisplay()->ResetLoader();
            GetDisplay()->clear();
           
            
						Serial.println("Clone ID Ok");
						ClearPIN();
            
						EVState *next_state = GetNextState();
						if ( next_state == nullptr) 
						{
							return this;
						}
						
						next_state->SetStateCreationTimestamp ( millis());
						return next_state;
					}
					else
					{
						Serial.print(m_CloneID);
						Serial.println(" ID not matching");
						ClearPIN();
						m_ErrorCount++;
						
						if (m_ErrorCount>2)
						{
							m_ResetTS = true;
							m_ErrorCount = 0;
							
							if (HasLoader())
                  GetDisplay()->ResetLoader();
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
				
				if (HasLoader())
            GetDisplay()->ResetLoader();
				GetDisplay()->clear();
        
        EVState *previous_state = GetPreviousState();
        if ( previous_state == nullptr) 
        {
          return this;
        }
        
        previous_state->SetStateCreationTimestamp( millis());
				return previous_state;
			}
			
			return this;
		}
	}
}
