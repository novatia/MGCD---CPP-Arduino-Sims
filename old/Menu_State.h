#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		class Menu_State  : public EVState
		{
			public:
				EVState* loop();
				Menu_State(EVState* previous_state, unsigned long state_entry_time);
		};
	}
}