#include "BIOActivating_State.h"
#include "BIOActivatingError_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		BIOActivating_State::BIOActivating_State(EVState* previous_state, unsigned long state_entry_time): EVState( previous_state, state_entry_time) {
			
		}
		
		EVState* BIOActivating_State::loop()
		{
			GetDisplay()->printBIOActivatingPage();
			
			if ( millis() - GetStateEntryTime() > 5000 )
			{
				GetDisplay()->clear();
				delete GetPreviousState();
				return new BIOActivatingError_State(this,millis());
			}
			
			return this;
		}
	}
}