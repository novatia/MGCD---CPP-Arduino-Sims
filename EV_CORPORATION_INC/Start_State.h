#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		/* EV CORPORATION INC. e scritta lampeggiante “premere un tasto per continuare” 
			
			Premere un tasto qualsiasi per continuare
			
			OnkeyPress: Goto UserPIN_State;
		*/
		class Start_State : public EVState
		{
			public:
				EVState* loop();
				Start_State(unsigned long state_entry_time);
				Start_State(EVState* previous_state, unsigned long state_entry_time);																		
		};
	}
}