#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		class AdminMenu_State  : public EVState
		{
			public:
				EVState* loop();
				AdminMenu_State(EVState* previous_state, unsigned long state_entry_time);
		};
	}
}