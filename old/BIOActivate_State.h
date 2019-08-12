#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		class BIOActivate_State  : public EVState
		{
			public:
				EVState* loop();
				BIOActivate_State(EVState* previous_state, unsigned long state_entry_time);
		};
	}
}