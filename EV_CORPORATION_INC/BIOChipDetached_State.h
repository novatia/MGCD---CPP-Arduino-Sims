#pragma once
#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		/*Wait 10 s*/
		class BIOChipDetached_State : public EVState 
		{
			private:
				char *m_Message;
				unsigned short int m_MessageLenght;
				unsigned short int m_TimeOut;
				
				bool m_Blink;
				bool m_PressButton;
				char m_CloneID[4];
				bool m_Disable;
				const char *m_AllDetached = "All ID detached!Rebooting...";
				EVState* m_AllDetachedState;
       EVState* m_ResetState;
      
				
			public:
				~BIOChipDetached_State();
				BIOChipDetached_State(Keypad* keypad, EVState* previous_state, EVState* next_state, unsigned long state_entry_time,const char *message, unsigned short int message_len, unsigned short int time_out, bool blink, bool press_button);
				
				EVState* loop() override;
				void SetCloneID(char* CloneID);
		};
	}
}
