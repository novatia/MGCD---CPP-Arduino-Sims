#include "KeysConstants.h"
#include "DisplayManager.h"

#define BLINK_MS 500

#define RED		255,0,0
#define BLUE	0,0,255
#define BLACK	0,0,0
#define WHITE	255,255,255

#define BACKGROUND_COLOR BLUE
#define TEXT_COLOR BLUE
#define ALARM_TEXT_COLOR RED

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
		
		m_ITDB02_28->clrScr();
	}

	void DisplayManager::printHeader()
	{
		if ( !m_PrintedHeader ) 
		{
			const char *title = "EV CORPORATION INC.";
			m_ITDB02_28->setColor(BACKGROUND_COLOR);
			m_ITDB02_28->fillRect(0, 0, 320, 30);
			
			m_ITDB02_28->setColor(WHITE);
			m_ITDB02_28->setBackColor(BACKGROUND_COLOR);
			
			m_ITDB02_28->print(title, CENTER, 7);
			
			m_PrintedHeader = true;
		}
	}

	void DisplayManager::printFooter()
	{	if ( !m_PrintedFooter ) 
		{
			//drawKeys();
			//drawSpinner();
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
				m_ITDB02_28->setColor(0, 0, m_Blink);
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

	/*
	void DisplayManager::printStartPage()
	{
			unsigned long ts = millis(); 
			
			printHeader();
			
			if ( (ts % BLINK_MS) == 0 ) {
				if (m_Blink > 0)
					m_Blink = 0;	
				else 
					m_Blink = 255;
				
				m_ITDB02_28->setColor(0, 0, m_Blink);
				m_ITDB02_28->setBackColor(BLACK);
				m_ITDB02_28->print("Press a button", CENTER, 80);
			}
			
			printFooter();
	}
	
	void DisplayManager::printNoDataPage()
	{
			
			unsigned long ts = millis(); 
			
			printHeader();
			
			if ( (ts % BLINK_MS) == 0 ) {
				if (m_Blink > 0)
					m_Blink = 0;	
				else 
					m_Blink = 255;
				
				m_ITDB02_28->setColor(m_Blink, 0, 0);
				m_ITDB02_28->setBackColor(BLACK);
				m_ITDB02_28->print("No data available", CENTER, 80);
			}
			
			printFooter();
	}


	void DisplayManager::printPINErrorPage()
	{
			
			
			printHeader();
			
			unsigned long ts = millis(); 
			
			if ( (ts % BLINK_MS) == 0 ) {
				if (m_Blink > 0)
					m_Blink = 0;	
				else 
					m_Blink = 255;
				
				m_ITDB02_28->setColor(m_Blink, 0, 0);
				m_ITDB02_28->setBackColor(BLACK);
				m_ITDB02_28->print("Too many error", CENTER, 80);
			}
			
			printFooter();
	}


	void DisplayManager::printUserMenuPage()
	{
		printHeader();

		m_ITDB02_28->setColor(TEXT_COLOR);
		m_ITDB02_28->setBackColor(BLACK);
		m_ITDB02_28->print("User menu", CENTER, 80);
		
		m_ITDB02_28->print("1)Download BIOData", 1, 120);
		m_ITDB02_28->print("2)Manage BIOChip", 1, 140);
		m_ITDB02_28->print("3)Show BIOData", 1, 160);
		
		printFooter();
	}

	void DisplayManager::printAdminPINPage(char* PIN)
	{
		unsigned long ts = millis(); 

		printHeader();

		m_ITDB02_28->setColor(TEXT_COLOR);
		m_ITDB02_28->setBackColor(BLACK);
		m_ITDB02_28->print("Insert Admin PIN", CENTER, 80);
		
		if (PIN[0]!=0)
		{
			m_ITDB02_28->print("*",60,100);
		} else {
			m_ITDB02_28->print("_",60,100);
		}
		
		if (PIN[1]!=0)
		{
			m_ITDB02_28->print("*",80,100);
		} else {
			m_ITDB02_28->print("_",80,100);
		}
		
		if (PIN[2]!=0)
		{
			m_ITDB02_28->print("*",100,100);
		} else {
			m_ITDB02_28->print("_",100,100);
		}
		
		if (PIN[3]!=0)
		{
			m_ITDB02_28->print("*",120,100);
		} else {
			m_ITDB02_28->print("_",120,100);
		}
		
		if (PIN[4]!=0)
		{
			m_ITDB02_28->print("*",140,100);
		} else {
			m_ITDB02_28->print("_",140,100);
		}
			
		printFooter();
	}

	void DisplayManager::printAdminMenuPage()
	{
		printHeader();

		m_ITDB02_28->setColor(TEXT_COLOR);
		m_ITDB02_28->setBackColor(BLACK);
		m_ITDB02_28->print("Admin menu", CENTER, 80);
		
		m_ITDB02_28->print("1)Activate BIOChip", 1, 120);
		m_ITDB02_28->print("2)Detach BIOChip", 1, 140);
		
		printFooter();
	}
	
	void DisplayManager::printBIOActivateChipPage(char* CloneID)
	{
		unsigned long ts = millis(); 

		printHeader();

		m_ITDB02_28->setColor(TEXT_COLOR);
		m_ITDB02_28->setBackColor(BLACK);
		m_ITDB02_28->print("Insert Clone ID", CENTER, 80);
		
		if (CloneID[0]!=0)
		{
			m_ITDB02_28->print("*",60,100);
		} else {
			m_ITDB02_28->print("_",60,100);
		}
		
		if (CloneID[1]!=0)
		{
			m_ITDB02_28->print("*",80,100);
		} else {
			m_ITDB02_28->print("_",80,100);
		}
		
		if (CloneID[2]!=0)
		{
			m_ITDB02_28->print("*",100,100);
		} else {
			m_ITDB02_28->print("_",100,100);
		}
		
		if (CloneID[3]!=0)
		{
			m_ITDB02_28->print("*",120,100);
		} else {
			m_ITDB02_28->print("_",120,100);
		}
			
		printFooter();
	}
	
	void DisplayManager::printBIOActivatePage()
	{
		printHeader();

		m_ITDB02_28->setColor(TEXT_COLOR);
		m_ITDB02_28->setBackColor(BLACK);
		m_ITDB02_28->print("Activate BIOChip?", CENTER, 80);
		
		m_ITDB02_28->print("Yes(1)/No(0)", 1, 120);
		
		printFooter();
	}
	
	void DisplayManager::printBIOActivatingPage()
	{
			printHeader();

		m_ITDB02_28->setColor(TEXT_COLOR);
		m_ITDB02_28->setBackColor(BLACK);
		m_ITDB02_28->print("Activating...", CENTER, 80);
		
		printFooter();
	}
	
	void DisplayManager::printBIOActivatingErrorPage()
	{
		printHeader();

		unsigned long ts = millis(); 
			
		if ( (ts % BLINK_MS) == 0 ) {
				if (m_Blink > 0)
					m_Blink = 0;	
				else 
					m_Blink = 255;
				
				m_ITDB02_28->setColor(m_Blink, 0, 0);
				m_ITDB02_28->setBackColor(BLACK);
				
				m_ITDB02_28->print("Error BIOChip already", CENTER, 80);
				m_ITDB02_28->print("activated.", CENTER, 120);
		}

		printFooter();
	}
	
	void DisplayManager::printBIODeactivateChipPage(char* CloneID)
	{
		
	}
	
	void DisplayManager::printBIODeactivatePage()
	{
		
	}
	
	void DisplayManager::printBIODeactivationSuccessPage()
	{
		
	}

	void DisplayManager::printBIOAllDeactivationSuccessPage()
	{
		
	}
	
	*/
}
