#pragma once
#include <URTouch.h>
#include <Keypad.h>





namespace EVCorporation
{
	class InputManager {
		private:
			static InputManager* m_Instance;
			Keypad* m_Keypad;
			char m_Digit;
			InputManager();
			
		public:
			static InputManager* GetInstance();
			char GetButtonPressed();
			void setup(Keypad* keypad);
			void loop();
	};
}