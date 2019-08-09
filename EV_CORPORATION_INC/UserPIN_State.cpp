#include "UserPIN_State.h"
#include "Menu_State.h"
#include "Start_State.h"
#include "Blocked_State.h"
#include "InputManager.h"

namespace EVCorporation
{
	namespace EVStates
	{
		void UserPIN_State::ClearPIN() 
		{
			m_PINIndex = 0;
			m_UserPIN[0] = 0;
			m_UserPIN[1] = 0;
			m_UserPIN[2] = 0;
			m_UserPIN[3] = 0;
		}
		
		UserPIN_State::UserPIN_State (EVState* previous_state,unsigned long state_entry_time) : EVState( previous_state, state_entry_time) {
			m_CurrentTS = millis();
			ClearPIN();
		}
		
		EVState* UserPIN_State::loop()
		{
			if (m_ResetTS)
				m_CurrentTS = millis();
			
			GetDisplay()->printUserPINPage(m_UserPIN);
			
			InputManager* IM = InputManager::GetInstance();
			char button_pressed = IM->GetButtonPressed();
			
			if ( button_pressed )
			{
				m_CurrentTS = millis();
				
				m_UserPIN[m_PINIndex] = button_pressed;
				Serial.print(m_UserPIN[m_PINIndex]);
				m_PINIndex++;
				
				if ( m_PINIndex > 3 )
				{
					//check pin 3845
					if ( m_UserPIN[0]=='3' && m_UserPIN[1]=='8'&& m_UserPIN[2]=='4'&& m_UserPIN[3]=='5' )
					{
						GetDisplay()->clear();
						delete GetPreviousState();
						return new Menu_State(this,millis());
					}
					else
					{
						ClearPIN();
						m_ErrorCount++;
						
						if (m_ErrorCount>2)
						{
							m_ResetTS = true;
							m_ErrorCount = 0;
							GetDisplay()->clear();
							return new Blocked_State(this,millis());
						}
					}
				}
			}
		
			if ( millis() - m_CurrentTS >= STATE_TIME_OUT_MS )
			{
				GetDisplay()->clear();
				return GetPreviousState();
			}
			
			return this;
		}
	}
}