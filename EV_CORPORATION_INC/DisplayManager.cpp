#include "KeysConstants.h"
#include "DisplayManager.h"

namespace EVCorporation
{
	DisplayManager* DisplayManager::m_Instance;
		
	DisplayManager::DisplayManager()
	{
		
	}
		
	void DisplayManager::setup( UTFT* ITDB02_28)
	{
		m_ITDB02_28 = ITDB02_28;
		clear();
	}
	
	DisplayManager* DisplayManager::GetInstance()
	{
		if (m_Instance == nullptr)
			m_Instance = new DisplayManager();		
		
		return m_Instance;
	}

	void DisplayManager::clear()
	{
		m_PrintedBody    = false;
		m_PrintedHeader  = false;
		m_PrintedFooter  = false;
		m_EnableLoader   = false;
   
		m_ITDB02_28->clrScr();
	}

	void DisplayManager::printHeader()
	{
		if ( !m_PrintedHeader ) 
		{
			const char *title = "EV CORPORATION INC.";
			m_ITDB02_28->setColor(BACKGROUND_COLOR);
			m_ITDB02_28->fillRect(0, 0, 319, 30);
			
			m_ITDB02_28->setColor(WHITE);
			m_ITDB02_28->setBackColor(BACKGROUND_COLOR);
			
			m_ITDB02_28->print(title, CENTER, 7);
			
			m_PrintedHeader = true;
		}
	}

  unsigned int DisplayManager::GetProgress()
  {
      unsigned int progress =  WIDTH_RESOLUTION * ( m_CurrentTime - m_CurrentStartTime ) / m_Timeout;
      if (progress>319)
        progress = 319;
      return progress;
  }

  void DisplayManager::SetLoader(bool EnableLoader, unsigned int time_out)
  {
      m_EnableLoader = EnableLoader;

      if (!m_EnableLoader)
        return;

      //main loop parameters
      m_Timeout  = time_out;
      
      if ( m_CurrentStartTime == 0 )
      {
        //first time entered set current start time to NOW and current tick to NOW
        m_CurrentStartTime = millis();
        m_CurrentTick = millis();
      }

      //update current time
      m_CurrentTime = millis();
  }

  void DisplayManager::ResetLoader()
  {
      Serial.println("Reset loader");
      m_ITDB02_28->setColor(BLACK);
      m_ITDB02_28->fillRect(0, 210, 319, 239);
      
      //m_CurrentTime - m_CurrentStartTime
      m_CurrentStartTime = 0;
      m_CurrentTime = 0;
      m_CurrentTick = 0;
  }

	void DisplayManager::printFooter()
	{	
	  if ( m_EnableLoader )
    {
       
        if (  (m_CurrentTime - m_CurrentTick)  >= LOADER_TICK )
        {
          //ticked greater then LOADER_TICK... update current tick
           m_CurrentTick = m_CurrentTime;
           m_LastProgress = GetProgress();
          
           m_ITDB02_28->setColor(BACKGROUND_COLOR);
           m_ITDB02_28->fillRect(0, 210, m_LastProgress, 239);
        }
    }
    
	  if ( !m_PrintedFooter ) 
		{
			m_PrintedFooter = true;
		}
	}

	/* 
		Message can be max 32 chars  (2 rows)
		timo_out is expressed in SECONDS
	*/
	void DisplayManager::printTextNTOPage(const char* message, bool blink)
	{
			unsigned long ts = millis(); 
			String msg(message);
			
			printHeader();
			
			if ( blink && ((ts % BLINK_MS) == 0) )
			{
				if ( m_Blink > 0 )
				{
				//	Serial.println( "Shut down" );
					m_Blink = 0;	
				}
				else 
				{
				//	Serial.println( "Rise up" );
					m_Blink = 255;
				}
				
				//Serial.println( m_Blink );
				
				m_PrintedBody = false;
			}
			else 
			{
				if ( !blink ) {
					//Serial.println( "Fixed" );
					m_Blink = 0xFF;
				}
			}
			
			if ( !m_PrintedBody )
			{
      
        if (m_TextColor == TextColors::Blue)
				  m_ITDB02_28->setColor(0, 0, m_Blink);
         
        if (m_TextColor == TextColors::Red)
          m_ITDB02_28->setColor(m_Blink, 0, 0);
       
        if (m_TextColor == TextColors::Green)
          m_ITDB02_28->setColor(0, m_Blink, 0);
        
        if (m_TextColor == TextColors::White)
          m_ITDB02_28->setColor(m_Blink, m_Blink, m_Blink);
          
				m_ITDB02_28->setBackColor(BLACK);
				
				if ( strlen(message) > 16 )
				{
					m_ITDB02_28->print(msg.substring(0,16), 0, 80);
					m_ITDB02_28->print(msg.substring(16), 0, 100);
				}
				else 
				{
					m_ITDB02_28->print(msg, CENTER, 80);
				}
				
				m_PrintedBody = true;
			}
			
			printFooter();
	}
	
	
	void DisplayManager::printPINPage(char *message, char* PIN,unsigned short int PIN_len)
	{
		unsigned long ts = millis(); 
		const char *star = "*";
		const char *underscore = "_";
		
		printHeader();

		m_ITDB02_28->setColor(TEXT_COLOR);
		m_ITDB02_28->setBackColor(BLACK);
		m_ITDB02_28->print(message, CENTER, 80);
		
		if (PIN[0]!=0)
		{
			m_ITDB02_28->print(star,60,100);
		} else {
			m_ITDB02_28->print(underscore,60,100);
		}
		
		if (PIN[1]!=0)
		{
			m_ITDB02_28->print(star,80,100);
		} else {
			m_ITDB02_28->print(underscore,80,100);
		}
		
		if (PIN[2]!=0)
		{
			m_ITDB02_28->print(star,100,100);
		} else {
			m_ITDB02_28->print(underscore,100,100);
		}
		
		if (PIN[3]!=0)
		{
			m_ITDB02_28->print(star,120,100);
		} else {
			m_ITDB02_28->print(underscore,120,100);
		}
		
		if (PIN_len==5){
			if (PIN[4]!=0)
			{
				m_ITDB02_28->print(star,140,100);
			} else {
				m_ITDB02_28->print(underscore,140,100);
			}
		}
		
		printFooter();
	}
	
	void  DisplayManager::printUserMenuPage( char *message, char **choices, unsigned short int choices_count  )
	{
		printHeader();	
		
		if ( !m_PrintedBody )
		{
			m_ITDB02_28->setColor(TEXT_COLOR);
			m_ITDB02_28->setBackColor(BLACK);
			m_ITDB02_28->print(message, CENTER, 80);
		
			unsigned short int y_pos = 100;
			
			for (unsigned short int i = 0;i<choices_count;i++) 
			{
				m_ITDB02_28->print(choices[i], 0, y_pos);
				y_pos+=20;
			}
			
			m_PrintedBody = true;
		}
			
		printFooter();
	}

  void DisplayManager::SetTextColor(TextColors color){
    m_TextColor = color;
  }
      
}
