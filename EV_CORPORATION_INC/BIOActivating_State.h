#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		class BIOActivating_State : public EVState
		{
			public:
				EVState* loop();
				BIOActivating_State(EVState* previous_state, unsigned long state_entry_time);
		}; 
	}
}