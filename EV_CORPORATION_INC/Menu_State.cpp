#include "Menu_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		
		Menu_State::~Menu_State()
		{
			delete[] m_Message;
		}
		
		Menu_State::Menu_State(Keypad* keypad, EVState* previous_state, EVState** next_states,const char **choices, const char* keys, unsigned short int next_states_len, const char *message, unsigned short int message_len ,unsigned long state_creation_time): EVState( keypad, previous_state, next_states, choices, keys, next_states_len, state_creation_time)
		{
			m_Message = new char[message_len]();
			
			for ( int i=0; i < message_len ; i++ ) 
			{
				m_Message[i] = message[i];
			}
			
			m_MessageLenght = message_len;
		}
		
		EVState* Menu_State::loop()
		{
			GetDisplay()->printUserMenuPage( m_Message, GetChoices(), GetNextStatesCount() );
			
			char button_pressed = GetKeypad()->getKey();
			
			if ( button_pressed )
			{
				EVState *next_state = GetNextState(button_pressed);
				
				if ( next_state == nullptr) {
					return this;
				}
					
				next_state->SetStateCreationTimestamp(millis());
					
				GetDisplay()->clear();
				return next_state;
			}
			
			return this;
		}
	}
}
