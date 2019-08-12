#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		
		class BIOChipON_State : public EVState
		{	
			private:
				char *m_CloneID;
				char *m_Message;
				unsigned short int m_CloneID_len;
				unsigned short int m_CloneIDIndex   = 0;
				unsigned short int m_ErrorCount = 0;
				unsigned long m_CurrentTS;
				bool m_ResetTS;
				const char *m_TooManyError = "Too many error";
				EVState* m_BlockedState;
				
			public:
				EVState* loop();
				BIOChipON_State( Keypad* keypad, EVState* previous_state, EVState* next_state,const char *message, unsigned short int message_len, unsigned short int PIN_len, unsigned long state_creation_time);
				~BIOChipON_State();
				void ClearPIN();
		};
	}
}