#include "NoData_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		NoData_State::NoData_State(EVState* previous_state, unsigned long state_entry_time): EVState( previous_state, state_entry_time) {
			
		}
		
		EVState* NoData_State::loop()
		{
			GetDisplay()->printNoDataPage();
			
			if ( millis()-GetStateEntryTime() > SHORT_STATE_TIME_OUT_MS )
			{
				GetDisplay()->clear();
				return GetPreviousState();
			}
			return this;
		}
	}
}