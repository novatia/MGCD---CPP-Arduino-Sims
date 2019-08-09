#include "InputManager.h"

#include "BIOActivate_State.h"
#include "BIOActivating_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		BIOActivate_State::BIOActivate_State(EVState* previous_state, unsigned long state_entry_time): EVState( previous_state, state_entry_time) {
			
		}
		
		EVState* BIOActivate_State::loop()
		{
			GetDisplay()->printBIOActivatePage();
			
			InputManager* IM = InputManager::GetInstance();
			char button_pressed = IM->GetButtonPressed();
			
			if ( button_pressed )
			{
				//yes
				if (button_pressed == '1' )
				{
					GetDisplay()->clear();
					delete GetPreviousState();
					return new BIOActivating_State(this,millis());
				}

				//no
				if (button_pressed == '0')
				{
					GetDisplay()->clear();
					return GetPreviousState();
				}
				
			}
			
			//RED LED ON
			
			
			
			
			return this;
		}
	}
}