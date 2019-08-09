#include "InputManager.h"

#include "AdminPIN_State.h"
#include "AdminMenu_State.h"
#include "Blocked_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		void AdminPIN_State::ClearPIN() 
		{
			m_PINIndex = 0;
			m_UserPIN[0] = 0;
			m_UserPIN[1] = 0;
			m_UserPIN[2] = 0;
			m_UserPIN[3] = 0;
			m_UserPIN[4] = 0;
		}
		
		AdminPIN_State::AdminPIN_State (EVState* previous_state,unsigned long state_entry_time) : EVState( previous_state, state_entry_time) {
			m_CurrentTS = millis();
			ClearPIN();
		}
		
		EVState* AdminPIN_State::loop()
		{
			if (m_ResetTS)
				m_CurrentTS = millis();
			
			GetDisplay()->printAdminPINPage(m_UserPIN);
			
			InputManager* IM = InputManager::GetInstance();
			char button_pressed = IM->GetButtonPressed();
			
			if ( button_pressed )
			{
				m_CurrentTS = millis();
				
				m_UserPIN[m_PINIndex] = button_pressed;
				Serial.print(m_UserPIN[m_PINIndex]);
				m_PINIndex++;
				
				if ( m_PINIndex > 4 )
				{
					//check pin 3845
					if ( m_UserPIN[0]=='1' && m_UserPIN[1]=='6' && m_UserPIN[2]=='2' && m_UserPIN[3]=='4' && m_UserPIN[4]=='5' )
					{
						GetDisplay()->clear();
						delete GetPreviousState();
						return new AdminMenu_State(this,millis());
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
							delete GetPreviousState();
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