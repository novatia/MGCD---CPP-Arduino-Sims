#include "InputManager.h"
#include "BIOActivateChip_State.h"
#include "Blocked_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		void BIOActivateChip_State::ClearBIOChip() 
		{
			m_BIOChipIndex = 0;
			m_BIOChip[0] = 0;
			m_BIOChip[1] = 0;
			m_BIOChip[2] = 0;
			m_BIOChip[3] = 0;
		}
		
		BIOActivateChip_State::BIOActivateChip_State (EVState* previous_state,unsigned long state_entry_time, EVState* next_state ) : EVState( previous_state, state_entry_time) {
			m_CurrentTS = millis();
			m_NextState = next_state;
			ClearBIOChip();
		}
		
		EVState* BIOActivateChip_State::loop()
		{
			if (m_ResetTS)
				m_CurrentTS = millis();
			
			GetDisplay()->printBIOActivateChipPage(m_BIOChip);
			
			InputManager* IM = InputManager::GetInstance();
			char button_pressed = IM->GetButtonPressed();
			
			if ( button_pressed )
			{
				m_CurrentTS = millis();
				
				m_BIOChip[m_BIOChipIndex] = button_pressed;
				Serial.print(m_BIOChip[m_BIOChipIndex]);
				m_BIOChipIndex++;
				
				if ( m_BIOChipIndex > 3 )
				{
					bool bio_check = false;
					//check biochips
					
					//if ok goto m_NextState delete previous state
					if ( bio_check )
					{
						GetDisplay()->clear();
						delete GetPreviousState();
						return m_NextState;
					}
					else
					{
						ClearBIOChip();
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
		
			return this;
		}
	}
}