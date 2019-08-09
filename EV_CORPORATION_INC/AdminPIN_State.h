#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		class AdminPIN_State  : public EVState
		{
			public:
				EVState* loop();
				AdminPIN_State(EVState* previous_state, unsigned long state_entry_time);
		};
	}
}