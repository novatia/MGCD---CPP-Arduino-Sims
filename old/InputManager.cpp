#include "KeysConstants.h"
#include "InputManager.h"

namespace EVCorporation
{
	InputManager* InputManager::m_Instance;
	
	InputManager::InputManager()
	{
		
	}
	
	InputManager* InputManager::GetInstance()
	{
		if (m_Instance == nullptr)
			m_Instance = new InputManager();		
		
		return m_Instance;
	}
	
	char InputManager::GetButtonPressed()
	{
		char digit = m_Digit;
		m_Digit = 0;
		return digit;
	}
	
	void InputManager::setup(Keypad* keypad) 
	{
		m_Keypad = keypad;
		m_Digit = 0;	
	}
	
	void InputManager::loop()
	{
		m_Digit = m_Keypad->getKey();
		
		if (m_Digit!=0)
			Serial.println(m_Digit);
		
	}
}