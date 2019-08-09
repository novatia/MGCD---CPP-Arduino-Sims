#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		class BIOActivateChip_State  : public EVState
		{
			private:
				char m_BIOChip[4];
				int m_BIOChipIndex=0;
				int m_ErrorCount = 0;
				unsigned long m_CurrentTS;
				bool m_ResetTS;
				EVState* m_NextState;
			public:
				EVState* loop();
				BIOActivateChip_State( EVState* previous_state, unsigned long state_entry_time,EVState* next_state );
				void ClearBIOChip();
		};
	}
}