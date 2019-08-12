#include "TextNTO_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		
		TextNTO_State::~TextNTO_State()
		{
			delete[] m_Message;
		}
		
		TextNTO_State::TextNTO_State(Keypad* keypad,  EVState* previous_state, EVState* next_state, unsigned long state_entry_time, const char *message, unsigned short int message_len, unsigned short int time_out, bool blink, bool press_button ): EVState(keypad, previous_state, next_state, state_entry_time)
		{
			m_Message = new char[message_len]();
			
			for ( int i=0; i < message_len ; i++ ) 
			{
				m_Message[i] = message[i];
			}
			
			m_MessageLenght = message_len;
			
			m_TimeOut = time_out;
			m_Blink = blink;
			m_PressButton = press_button;
		}
		
		EVState* TextNTO_State::loop()
		{
			GetDisplay()->printTextNTOPage( m_Message, m_Blink );
			
			if ( m_TimeOut != 0 )
			{
				
				if ( millis() - GetStateCreationTimestamp() > m_TimeOut * 1000 )
				{
					GetDisplay()->clear();
					return GetPreviousState();
				}
			}
			
			if ( m_PressButton ) 
			{
				char button_pressed = GetKeypad()->getKey();
				
				if ( button_pressed )
				{
					//Serial.println("PRESSED");
					EVState *next_state = GetNextState();
					
					if ( next_state == nullptr) {
						Serial.println("No Nextstate Setted");
						return this;
					}
					
					next_state->SetStateCreationTimestamp(millis());
					
					GetDisplay()->clear();
					
					delete GetPreviousState();
					return next_state;
				}
			}
			
					
			return this;
		}
	}
}