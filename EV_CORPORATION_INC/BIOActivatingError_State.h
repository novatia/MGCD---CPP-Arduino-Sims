#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		class BIOActivatingError_State : public EVState
		{
			public:
				EVState* loop();
				BIOActivatingError_State(EVState* previous_state, unsigned long state_entry_time);																		
		};
	}
}