#include "BIOChipDetached_State.h"
#include "BIOChipManager.h"

namespace EVCorporation
{
	namespace EVStates
	{
		
		BIOChipDetached_State::~BIOChipDetached_State()
		{
			delete[] m_Message;
		}
		
		BIOChipDetached_State::BIOChipDetached_State(Keypad* keypad,  EVState* previous_state, EVState* next_state, unsigned long state_entry_time, const char *message, unsigned short int message_len, unsigned short int time_out, bool blink, bool press_button,char *CloneID ): EVState(keypad, previous_state, next_state, state_entry_time)
		{
			m_Message = new char[message_len]();
			
			for ( int i=0; i < message_len ; i++ ) 
			{
				m_Message[i] = message[i];
			}
			
				
			for ( int i=0; i < 4 ; i++ ) 
			{
				m_CloneID[i] = CloneID[i];
			}
			
			m_MessageLenght = message_len;
			
			m_TimeOut = time_out;
			m_Blink = blink;
			m_PressButton = press_button;
		}
		
		EVState* BIOChipDetached_State::loop()
		{
			GetDisplay()->printTextNTOPage( m_Message, m_Blink );
			
			if ( m_TimeOut != 0 )
			{
				
				if ( millis() - GetStateCreationTimestamp() > m_TimeOut * 1000 )
				{
					BIOChipManager* BIOM = BIOChipManager::GetInstance();
					BIOM->DisableBIOChip(m_CloneID);
					EVState* previous_state = GetPreviousState();
         
					if ( previous_state == nullptr) 
					{
						Serial.println("No previous state Setted");
						return this;
					}
					
					previous_state->SetStateCreationTimestamp(millis());
					
					GetDisplay()->clear();
				    
					return previous_state;
				}
			}
			
			if ( m_PressButton ) 
			{
				char button_pressed = GetKeypad()->getKey();
				
				if ( button_pressed )
				{
					EVState *next_state = GetNextState();
					
					if ( next_state == nullptr) {
						//Serial.println("No Nextstate Setted");
						return this;
					}
					
					next_state->SetStateCreationTimestamp(millis());
					
					GetDisplay()->clear();
					//delete GetPreviousState();
					return next_state;
				}
			}
			
					
			return this;
		}
	}
}
