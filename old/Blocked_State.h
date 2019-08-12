#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		/*Wait 10 s*/
		class Blocked_State : public EVState 
		{
			public:
				EVState* loop();
				Blocked_State(EVState* previous_state, unsigned long state_entry_time);
		};
	}
}