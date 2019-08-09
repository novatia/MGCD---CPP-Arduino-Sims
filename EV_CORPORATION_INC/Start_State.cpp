#include "Start_State.h"
#include "UserPIN_State.h"
#include "InputManager.h"


namespace EVCorporation
{
	namespace EVStates
	{
		Start_State::Start_State(unsigned long state_entry_time) : EVState( nullptr, state_entry_time)
		{
			
		}
		
		Start_State::Start_State(EVState* previous_state, unsigned long state_entry_time) : EVState( previous_state, state_entry_time)
		{
			
		}

		EVState* Start_State::loop()
		{
			GetDisplay()->printStartPage();
			
			InputManager* IM = InputManager::GetInstance();
			char button_pressed = IM->GetButtonPressed();
				
			if ( button_pressed )
			{
				GetDisplay()->clear();
				delete GetPreviousState();
				return new UserPIN_State(this,millis());
			}
			
			return this;
		}
	}
}