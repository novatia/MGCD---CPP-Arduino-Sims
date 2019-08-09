#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		EVState::EVState (EVState *previous_state,unsigned long state_entry_time)
		{
			m_StateEntryTime = state_entry_time;
			m_PreviousState = previous_state;
			m_DM = DisplayManager::GetInstance();
			
		}

		EVState* EVState::loop()
		{
			return this;
		}
		
		void EVState::print()
		{
		
		}
				
		DisplayManager* EVState::GetDisplay()
		{
			return m_DM;
		}
		
		char* EVState::GetStateName()
		{
			return "";
		}
		
		unsigned long EVState::GetStateEntryTime() const
		{
			return m_StateEntryTime;
		}
		
		EVState* EVState::GetPreviousState() const
		{
			return m_PreviousState;
		}
	}
}