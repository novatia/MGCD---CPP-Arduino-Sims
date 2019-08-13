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
			
				const char *m_ActivateBIOChip = "Activate BIOChip?";
				EVState* ActivateBIOChipMenu[2];
			
				const char *m_ActivationChoices[2] = {"Yes (1)","No (0)"};
				const char m_ActivationKeys[2] = {'1','0'};
				EVState* m_ActivationMenuState;
				
				const char *m_ActivatingBIOChip = "Activating...";
				EVState* m_ActivatingState;
				
				const char *m_ActivationError = "Error BIOChip   already active.";
				EVState* m_ErrorState;
				
				
			public:
				~BIOChipON_State();
				BIOChipON_State( Keypad* keypad, EVState* previous_state, EVState* next_state,const char *message, unsigned short int message_len, unsigned short int PIN_len, unsigned long state_creation_time);
				
				EVState* loop() override;
				void SetErrorPreviousState(EVState* previous_state);
				
				void ClearPIN();
				
		};
	}
}
