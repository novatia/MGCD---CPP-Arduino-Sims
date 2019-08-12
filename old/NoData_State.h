#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		class NoData_State : public EVState
		{
			public:
				EVState* loop();
				NoData_State(EVState* previous_state, unsigned long state_entry_time);
		}; 
	}
}