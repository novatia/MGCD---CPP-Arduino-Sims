#include "Blocked_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		Blocked_State::Blocked_State(EVState* previous_state, unsigned long state_entry_time): EVState( nullptr, state_entry_time)
		{
			
		}
		
		EVState* Blocked_State::loop()
		{
			if  (GetStateEntryTime() > millis() + STATE_TIME_OUT_MS)
			{
				return GetPreviousState();
			}
					
			return this;
		}
	}
}