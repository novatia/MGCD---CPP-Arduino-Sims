#include "BIOActivatingError_State.h"
#include "InputManager.h"
#include "AdminMenu_State.h"


namespace EVCorporation
{
	namespace EVStates
	{
		
		BIOActivatingError_State::BIOActivatingError_State(EVState* previous_state, unsigned long state_entry_time) : EVState( previous_state, state_entry_time)
		{
			
		}

		EVState* BIOActivatingError_State::loop()
		{
			GetDisplay()->printBIOActivatingErrorPage();
			
			InputManager* IM = InputManager::GetInstance();
			char button_pressed = IM->GetButtonPressed();
			
			if ( button_pressed || ( millis() - GetStateEntryTime() >= 15000 ) )
			{
				GetDisplay()->clear();
				delete GetPreviousState();
				return new AdminMenu_State(this,millis());
			}
			
			return this;
		}
	}
}