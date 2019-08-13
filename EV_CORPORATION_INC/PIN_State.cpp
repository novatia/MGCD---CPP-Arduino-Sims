#include "PIN_State.h"
#include "TextNTO_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		void PIN_State::ClearPIN() 
		{
      Serial.println("Clear PIN");
			m_PINIndex = 0;
			
			for (unsigned short int i=0;i<m_PIN_len;i++)
			{
				m_UserPIN[i] = 0;
			}
			
			m_ResetTS = true;
		}
		
		PIN_State::~PIN_State ()
		{
			delete[] m_PIN;
			delete[] m_UserPIN;
			delete m_BlockedState;
		}
		
		PIN_State::PIN_State (Keypad* keypad, EVState* previous_state, EVState* next_state,const char *message, unsigned short int message_len,const char *PIN,unsigned short int PIN_len, unsigned long state_creation_time) : EVState( keypad, previous_state, next_state, state_creation_time ) 
		{
			m_CurrentTS = millis();
			
			m_PIN 	  = new char[PIN_len]();
			m_UserPIN = new char[PIN_len]();
			
			m_PIN_len = PIN_len;
			
			for (unsigned short int i = 0;i < 5; i++ )
			{
				m_PIN[i] = 0;
			}
			
			for (unsigned short int i = 0;i < PIN_len; i++ ) 
			{
				m_PIN[i] = PIN[i];
			}
			
			m_Message = new char[message_len]();
			
			for ( int i=0; i < message_len ; i++ ) 
			{
				m_Message[i] = message[i];
			}
			
			m_BlockedState = new TextNTO_State(keypad, this, nullptr, m_CurrentTS, m_TooManyError, 15, 10000, false, true);
			
			ClearPIN();
		}
		
		
		EVState* PIN_State::loop()
		{
			if ( m_ResetTS ) 
			{
				m_CurrentTS = millis();
				ClearPIN();
				m_ResetTS = false;
			}
			
			if (m_EnableLoader)
			    GetDisplay()->SetLoader(STATE_TIME_OUT_MS);
        
			GetDisplay()->printPINPage(m_Message, m_UserPIN, m_PIN_len);
			
			char button_pressed =GetKeypad()->getKey();
			
			if ( button_pressed )
			{
				m_CurrentTS = millis();
				
				if (m_EnableLoader)
              GetDisplay()->ResetLoader();
     
				m_UserPIN[m_PINIndex] = button_pressed;
				Serial.print(m_UserPIN[m_PINIndex]);
				m_PINIndex++;
				
				if ( m_PINIndex > m_PIN_len - 1 )
				{
					bool pin_checked = true;
					
					for (unsigned int i = 0; i < m_PIN_len; i++ ) {
						if (m_UserPIN[i] != m_PIN[i] ) 
							pin_checked = false;
					} 
										
					if (pin_checked) 
					{ 
						GetDisplay()->clear();
            if (m_EnableLoader)
                GetDisplay()->ResetLoader();
                
						Serial.println(" PIN Ok");
						EVState *next_state = GetNextState();
					
						ClearPIN();
						
						if ( next_state == nullptr) {
							Serial.println("No Nextstate Setted");
							
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
						
						if (m_EnableLoader)
              GetDisplay()->ResetLoader();
     
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

    void PIN_State::SetLED(){
          m_EnableLED=true;
    }
    
    void PIN_State::SetLoader(){
          m_EnableLoader=true;
    }
   }
}
