#include "EVState.h"
#include "BIOChipDetached_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		
		class BIOChipOFF_State : public EVState
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
			
				const char *m_AlreadyDetachedError = "Warning!BIOChip already detached";
				EVState* m_AlreadyDetachedState;
			
			
				const char *m_DeactivateBIOChip = "Detach BIOChip?";
				EVState* DeactivateBIOChipMenu[2];
			
				const char *m_DeactivationChoices[2] = {"Yes (1)","No (0)"};
				const char m_DeactivationKeys[2] = {'1','0'};
				EVState* m_DeactivationMenuState;
				
				
				const char *m_DeactivatingBIOChip = "Detaching       BIO-Chip...";
				EVState* m_DeactivatingState;
				
				const char *m_DeactivatedBIOChip = "BIOChip detachedProcedure done.";
				BIOChipDetached_State* m_DeactivationSuccessState;
				
			public:
				~BIOChipOFF_State();
				BIOChipOFF_State( Keypad* keypad, EVState* previous_state, EVState* next_state,const char *message, unsigned short int message_len, unsigned short int PIN_len, unsigned long state_creation_time);
				
				EVState* loop() override;
				void SetSuccessPreviousState(EVState* previous_state);
				
				void ClearPIN();
				
		};
	}
}
