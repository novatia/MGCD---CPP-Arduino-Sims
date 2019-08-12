#include "InputManager.h"
#include "Menu_State.h"
#include "NoData_State.h"
#include "AdminPIN_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		Menu_State::Menu_State(EVState* previous_state, unsigned long state_entry_time): EVState( previous_state, state_entry_time) {
			
		}
		
		EVState* Menu_State::loop()
		{
			GetDisplay()->printUserMenuPage();
			
			InputManager* IM = InputManager::GetInstance();
			char button_pressed = IM->GetButtonPressed();
			
			if ( button_pressed )
			{
				if (button_pressed == '1' || button_pressed == '3')
				{
					GetDisplay()->clear();
					delete GetPreviousState();
					return new NoData_State(this,millis());
				}

				if (button_pressed == '2')
				{
					GetDisplay()->clear();
					delete GetPreviousState();
					return new AdminPIN_State(this,millis());
				}
			}
			return this;
		}
	}
}