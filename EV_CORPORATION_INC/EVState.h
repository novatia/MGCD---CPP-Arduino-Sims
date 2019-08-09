#pragma once
#include "DisplayManager.h"

#define STATE_TIME_OUT_MS 10000
#define SHORT_STATE_TIME_OUT_MS 4000

namespace EVCorporation
{
	namespace EVStates
	{
		class EVState 
		{
			private:
				unsigned long m_StateEntryTime;
				EVState* m_PreviousState;
				DisplayManager *m_DM;
				
								
			public:
				EVState (EVState* previous_state,unsigned long state_entry_time);
				virtual EVState* loop(); //loop interface manage input and route correct state
				virtual void print();
				virtual char* GetStateName();
				unsigned long GetStateEntryTime() const;
				EVState*  GetPreviousState() const;
				
				DisplayManager *GetDisplay();
		};

	}
}