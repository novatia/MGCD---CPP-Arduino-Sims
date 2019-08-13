#include "EVState.h"
#include "Keypad.h"

namespace EVCorporation
{
	namespace EVStates
	{
		
		//ONLY USED FOR POINTERS
		EVState::EVState()
		{
		}
		
		EVState::~EVState()
		{
			
		}
		
		EVState::EVState (EVState *previous_state,unsigned long state_creation_timestamp)
		{
			m_StateCreationTimestamp = state_creation_timestamp;
			m_PreviousState = previous_state;
			m_DM = DisplayManager::GetInstance();
		}
		
		EVState::EVState (EVState *previous_state,EVState *next_state,unsigned long state_creation_timestamp)
		{
			m_StateCreationTimestamp = state_creation_timestamp;
			m_PreviousState = previous_state;
			
			m_NextStates[0] = next_state;
			
			m_DM = DisplayManager::GetInstance();
		}
		
		EVState::EVState (Keypad* keypad, EVState *previous_state,unsigned long state_creation_timestamp)
		{
			m_StateCreationTimestamp = state_creation_timestamp;
			m_PreviousState = previous_state;
			m_DM = DisplayManager::GetInstance();
			m_Keypad = keypad;
		}
		
		EVState::EVState (Keypad* keypad, EVState *previous_state,EVState *next_state,unsigned long state_creation_timestamp)
		{
			m_StateCreationTimestamp = state_creation_timestamp;
			m_PreviousState = previous_state;
			
			m_NextStates[0] = next_state;

			m_DM = DisplayManager::GetInstance();
			m_Keypad = keypad;
		}

		EVState::EVState (Keypad* keypad, EVState *previous_state,EVState **next_states,const char **choices,const char *keys,unsigned short int next_states_len, unsigned long state_creation_timestamp)
		{
			m_StateCreationTimestamp = state_creation_timestamp;
			m_PreviousState = previous_state;
			
			m_NextStatesLen = next_states_len;
			
			for (unsigned short int i=0;i<next_states_len;i++){
				m_NextStates[i] = next_states[i];
				m_Choices[i] = choices[i];
				m_Keys[i] = keys[i];
			}

			m_DM = DisplayManager::GetInstance();
			m_Keypad = keypad;
		}

		EVState* EVState::loop()
		{
			return this;
		}
			
		DisplayManager* EVState::GetDisplay()
		{
			return m_DM;
		}
		
		Keypad* EVState::GetKeypad()
		{
			return m_Keypad;
		}
		
		unsigned long EVState::GetStateCreationTimestamp() const
		{
			return m_StateCreationTimestamp;
		}
		
		void EVState::SetStateCreationTimestamp(unsigned long int StateCreationTimestamp )
		{
			m_StateCreationTimestamp = StateCreationTimestamp;
		}
		
		
		void EVState::SetPreviousState(EVState* previous_state)
		{
			m_PreviousState = previous_state;
		}
		
		EVState* EVState::GetPreviousState() const
		{
			return m_PreviousState;
		}
		
		EVState* EVState::GetNextState() const
		{
			return m_NextStates[0];
		}
		
		
		EVState* EVState::GetNextState(char key) const
		{
			if (key == m_Keys[0])
				return m_NextStates[0];
			
			if (key == m_Keys[1])
				return m_NextStates[1];
			
			if (key == m_Keys[2])
				return m_NextStates[2];
			
			return nullptr;
		}
		
		void EVState::SetNextState(EVState* next_state)
		{
			m_NextStates[0] = next_state;
		}
		
		char** EVState::GetChoices()
		{
		
			return m_Choices;
		}
		
		unsigned short int EVState::GetNextStatesCount()
		{
			return m_NextStatesLen;
		}

   
    void EVState::SetLED(TextColors color) {
          m_EnableLED=true;
          m_LEDColor = color;
          m_LEDBlink = false;
    }

    void EVState::SetLED(TextColors color,bool blink) {
          m_EnableLED=true;
          m_LEDColor = color;
          m_LEDBlink = blink;
    }
    
    void EVState::SetLoader(){
          m_EnableLoader=true;
    }

    bool EVState::HasLoader()
    {
      return m_EnableLoader;
    }
    
    bool EVState::HasLED()
    {
      return m_EnableLED; 
    }

    void EVState::SetLEDColor()
    {
      if (!HasLED())
        return; 

      if ( m_LEDBlink )
      {
        if ( millis() - m_LED_blink_ts > LED_BLINK_TICK )
        {
          m_LED_blink_ts = millis();
          m_LED_value--;
          
          if (m_LED_value==0)
            m_LED_value = 255;
        }
      }
      else 
      {
        m_LED_value = 0;
      }
      
      if (m_LEDColor == TextColors::Red)
      {
        analogWrite(BLUE_PIN,255);
        analogWrite(GREEN_PIN,255);
        analogWrite(RED_PIN,m_LED_value);
      }
      

      if (m_LEDColor == TextColors::Green)
      {
        analogWrite(BLUE_PIN,255);
        analogWrite(GREEN_PIN,m_LED_value);
        analogWrite(RED_PIN,255); 
      }

      if (m_LEDColor == TextColors::Blue)
      {
        analogWrite(BLUE_PIN,m_LED_value);
        analogWrite(GREEN_PIN,255);
        analogWrite(RED_PIN,255); 
      }

      if (m_LEDColor == TextColors::White)
      {
        analogWrite(BLUE_PIN,m_LED_value);
        analogWrite(GREEN_PIN,m_LED_value);
        analogWrite(RED_PIN,m_LED_value); 
      }

      if (m_LEDColor == TextColors::Black)
      {
        analogWrite(BLUE_PIN,255);
        analogWrite(GREEN_PIN,255);
        analogWrite(RED_PIN,255); 
      }

    }
    
    void EVState::SetTextColor(TextColors color){
      m_TextColor =color;
     
     }
    
     TextColors EVState::GetTextColor(){
      return m_TextColor;
     }
	}
}
