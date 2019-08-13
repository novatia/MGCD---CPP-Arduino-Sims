#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		/*
			Inserire PIN User
			_ _ _ _
			barra di caricamento sul fondo dello schermo per
			indicare l’inattività dell’utente
			
			TO 10s GOTO Start_State
			3x error wait 10s return this state.
		*/
		class PIN_State : public EVState
		{	
			private:
				char *m_PIN;
				char *m_UserPIN;
				char *m_Message;

        bool m_EnableLoader;
        bool m_EnableLED;
        
       
				unsigned short int m_PIN_len;
				unsigned short int m_PINIndex   = 0;
				unsigned short int m_ErrorCount = 0;
				unsigned long m_CurrentTS;
				bool m_ResetTS;
				const char *m_TooManyError = "Too many error";
				EVState* m_BlockedState;
				
			public:
				EVState* loop();
				PIN_State(Keypad* keypad, EVState* previous_state, EVState* next_state,const char *message, unsigned short int message_len,const char *PIN,unsigned short int PIN_len, unsigned long state_creation_time);
				~PIN_State();
				void ClearPIN();

        void SetLoader();
        void SetLED();
		};
	}
}
