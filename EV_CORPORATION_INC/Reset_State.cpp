#include "Reset_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		
		void(* resetFunc) (void) = 0; 
    	
		
		Reset_State::~Reset_State()
		{
			
		}
		
		Reset_State::Reset_State(): EVState(nullptr, nullptr, nullptr, 0)
		{
			
		}
		
		EVState* Reset_State::loop()
		{
			resetFunc();
			return this;
		}
	}
}
