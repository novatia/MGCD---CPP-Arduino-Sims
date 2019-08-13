#include "BIOChipDetached_State.h"
#include "BIOChipManager.h"
#include "TextNTO_State.h"
#include "Reset_State.h"

namespace EVCorporation
{
	namespace EVStates
	{
		
		BIOChipDetached_State::~BIOChipDetached_State()
		{
			delete[] m_Message;
		}
		
		void BIOChipDetached_State::SetCloneID(char* CloneID)
		{
			m_CloneID[0] = CloneID[0];
			m_CloneID[1] = CloneID[1];
			m_CloneID[2] = CloneID[2];
			m_CloneID[3] = CloneID[3];
		} 
		
		BIOChipDetached_State::BIOChipDetached_State(Keypad* keypad,  EVState* previous_state, EVState* next_state, unsigned long state_entry_time, const char *message, unsigned short int message_len, unsigned short int time_out, bool blink, bool press_button ): EVState(keypad, previous_state, next_state, state_entry_time)
		{
			m_Message = new char[message_len]();
			
			for ( int i=0; i < message_len ; i++ ) 
			{
				m_Message[i] = message[i];
			}
		
			m_MessageLenght = message_len;
			
			m_TimeOut = time_out;
			m_Blink = blink;
			m_PressButton = press_button;

			m_ResetState = new Reset_State();
    
			m_AllDetachedState = new TextNTO_State(keypad, m_ResetState, nullptr, 0, m_AllDetached, 29, 30, false, true);
		}
   
		
		EVState* BIOChipDetached_State::loop()
		{
			GetDisplay()->printTextNTOPage( m_Message, m_Blink );
			
			if ( m_TimeOut != 0 )
			{
				
				if ( millis() - GetStateCreationTimestamp() > m_TimeOut * 1000 )
				{
           m_Disable = true;
				}
			}
			
			if ( m_PressButton ) 
			{
				char button_pressed = GetKeypad()->getKey();
				
				if ( button_pressed )
				{
          m_Disable = true;
				}
			}

      if (m_Disable)
      {
            BIOChipManager* BIOM = BIOChipManager::GetInstance();
            
            Serial.println(BIOM->IsEnabled(m_CloneID));
            BIOM->DisableBIOChip(m_CloneID);
            Serial.println(BIOM->IsEnabled(m_CloneID));
            Serial.println(BIOM->AllDisabled());
           
            if ( BIOM->AllDisabled() )
            {
                Serial.println("All detached... Game end.");
                GetDisplay()->clear();
                m_AllDetachedState->SetStateCreationTimestamp(millis());
                return m_AllDetachedState;
            }                                                                                                     
            
            EVState* previous_state = GetPreviousState();
           
            if ( previous_state == nullptr) 
            {
              Serial.println("No previous state Setted");
              return this;
            }
            m_Disable = false;
            previous_state->SetStateCreationTimestamp(millis());
            GetDisplay()->clear();
            return previous_state;
     }
					
			return this;
		}
	}
}
