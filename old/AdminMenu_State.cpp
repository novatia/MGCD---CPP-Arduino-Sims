#include "InputManager.h"

#include "AdminMenu_State.h"
#include "BIOActivateChip_State.h"
#include "BIOActivate_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		AdminMenu_State::AdminMenu_State(EVState* previous_state, unsigned long state_entry_time): EVState( previous_state, state_entry_time) {
			
		}
		
		EVState* AdminMenu_State::loop()
		{
			GetDisplay()->printAdminMenuPage();
			
			InputManager* IM = InputManager::GetInstance();
			char button_pressed = IM->GetButtonPressed();
			
			if ( button_pressed )
			{
				if (button_pressed == '1' )
				{
					GetDisplay()->clear();
					delete GetPreviousState();
					return new BIOActivateChip_State(this,millis(), new BIOActivate_State(this,millis() ) );
				}

				if (button_pressed == '2')
				{
					GetDisplay()->clear();
					delete GetPreviousState();
					return nullptr;
				}
				
			}
			
			//RED LED ON
			
			
			
			
			return this;
		}
	}
}