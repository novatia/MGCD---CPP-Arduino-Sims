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
		class UserPIN_State : public EVState
		{	
			private:
				char m_UserPIN[4];
				int m_PINIndex=0;
				int m_ErrorCount = 0;
				unsigned long m_CurrentTS;
			public:
				EVState* loop();
				UserPIN_State(EVState* previous_state, unsigned long state_entry_time);
				void ClearPIN();
		};
	}
}