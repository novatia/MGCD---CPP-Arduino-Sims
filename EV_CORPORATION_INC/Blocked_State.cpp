#include "Blocked_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		Blocked_State::Blocked_State(EVState* previous_state, unsigned long state_entry_time): EVState( previous_state, state_entry_time)
		{
			
		}
		
		EVState* Blocked_State::loop()
		{
			GetDisplay()->printPINErrorPage();
			
			if ( millis()-GetStateEntryTime() > STATE_TIME_OUT_MS )
			{
				GetDisplay()->clear();
				return GetPreviousState();
			}
					
			return this;
		}
	}
}