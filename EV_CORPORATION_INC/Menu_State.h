#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		class Menu_State  : public EVState
		{
			private:
				char *m_Message;
				unsigned short int m_MessageLenght;
				
			public:
				~Menu_State();
				Menu_State(Keypad* keypad, EVState* previous_state, EVState** next_states,const char **choices,const char* keys, unsigned short int next_states_len, const char *message, unsigned short int message_len ,unsigned long state_creation_time);
				
				EVState* loop() override;
		};
	}
}