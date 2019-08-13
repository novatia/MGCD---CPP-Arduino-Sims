#pragma once
#include "DisplayManager.h"
#include "Keypad.h"

#define STATE_TIME_OUT_MS 10000

namespace EVCorporation
{
	namespace EVStates
	{
		class EVState 
		{
			private:
				unsigned long m_StateCreationTimestamp;
				EVState* m_PreviousState;
				EVState* m_NextStates[3];
				char *m_Choices[3];
				char m_Keys[3];
				unsigned short int m_NextStatesLen;
				DisplayManager *m_DM;
				Keypad* m_Keypad;
								
			public:
				// moved here because crash using Super class calloc
				~EVState ();
				EVState ();
				EVState (Keypad* keypad, EVState* previous_state,unsigned long state_creation_timestamp);
				EVState (Keypad* keypad, EVState* previous_state,EVState* next_state,unsigned long state_creation_timestamp);
				EVState (Keypad* keypad, EVState* previous_state,EVState** next_states,const char **choices,const char *keys,unsigned short int next_states_len, unsigned long state_creation_timestamp);
				
				EVState (EVState* previous_state,unsigned long state_creation_timestamp);
				EVState (EVState* previous_state,EVState* next_state,unsigned long state_creation_timestamp);
				virtual EVState* loop(); //loop interface manage input and route correct state
				
				unsigned long GetStateCreationTimestamp() const;
				void SetStateCreationTimestamp(unsigned long int StateCreationTimestamp );
				
				void SetPreviousState(EVState* previous_state);
				EVState*  GetPreviousState() const;
				
				void SetNextState(EVState* next_state) ;
				EVState*  GetNextState() const;
				EVState*  GetNextState(char key) const;
				
				DisplayManager *GetDisplay();
				Keypad *GetKeypad();
				
				char **GetChoices();
				unsigned short int GetNextStatesCount();
				
		};

	}
}
