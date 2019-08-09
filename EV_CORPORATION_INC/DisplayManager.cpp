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
	uint8_t blink = 0;
	
	void DisplayManager::setup( UTFT* ITDB02_28)
	{
		m_ITDB02_28 = ITDB02_28;
		
		clear();
	}
	
	DisplayManager* DisplayManager::m_Instance;
		
	DisplayManager::DisplayManager()
	{
		m_ITDB02_28 = new UTFT(ITDB28,38,39,40,41);
	}
		
	DisplayManager* DisplayManager::GetInstance()
	{
		if (m_Instance == nullptr)
			m_Instance = new DisplayManager();		
		
		return m_Instance;
	}

	void DisplayManager::clear()
	{
		m_Printed = false;
		m_ITDB02_28->clrScr();
	}

	void DisplayManager::printHeader()
	{
		if (!m_Printed) 
		{
						
			m_ITDB02_28->setColor(BACKGROUND_COLOR);
			m_ITDB02_28->fillRect(0, 0, 320, 30);
			
			m_ITDB02_28->setColor(WHITE);
			m_ITDB02_28->setBackColor(BACKGROUND_COLOR);
			
			m_ITDB02_28->print("EV CORPORATION INC.", CENTER, 7);
		}
	}

	void DisplayManager::printFooter()
	{	if (!m_Printed) 
		{
			//drawKeys();
			
			//drawSpinner();
		}
	}

	void DisplayManager::printStartPage()
	{
			
			unsigned long ts = millis(); 
			
			printHeader();
			
			if ( (ts % BLINK_MS) == 0 ) {
				if (blink > 0)
					blink = 0;	
				else 
					blink = 255;
				
				m_ITDB02_28->setColor(0, 0, blink);
				m_ITDB02_28->setBackColor(BLACK);
				m_ITDB02_28->print("Press a button", CENTER, 80);
			
			}
			
			printFooter();
			
			m_Printed = true;
	}
	
	void DisplayManager::printNoDataPage()
	{
			
			unsigned long ts = millis(); 
			
			printHeader();
			
			if ( (ts % BLINK_MS) == 0 ) {
				if (blink > 0)
					blink = 0;	
				else 
					blink = 255;
				
				m_ITDB02_28->setColor(blink, 0, 0);
				m_ITDB02_28->setBackColor(BLACK);
				m_ITDB02_28->print("No data available", CENTER, 80);
			}
			
			printFooter();
			
			m_Printed = true;
	}


	void DisplayManager::printPINErrorPage()
	{
			
			
			printHeader();
			
			unsigned long ts = millis(); 
			
			if ( (ts % BLINK_MS) == 0 ) {
				if (blink > 0)
					blink = 0;	
				else 
					blink = 255;
				
				m_ITDB02_28->setColor(blink, 0, 0);
				m_ITDB02_28->setBackColor(BLACK);
				m_ITDB02_28->print("Too many error", CENTER, 80);
			}
			
			printFooter();
			
			m_Printed = true;
	}

	void DisplayManager::printUserPINPage(char* PIN)
	{
		unsigned long ts = millis(); 

		printHeader();

		m_ITDB02_28->setColor(TEXT_COLOR);
		m_ITDB02_28->setBackColor(BLACK);
		m_ITDB02_28->print("Insert User PIN", CENTER, 80);
		
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
			
		printFooter();
			
		m_Printed = true;
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
		m_Printed = true;
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
			
		m_Printed = true;
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
		m_Printed = true;
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
			
		m_Printed = true;
	}
	
	void DisplayManager::printBIOActivatePage()
	{
		printHeader();

		m_ITDB02_28->setColor(TEXT_COLOR);
		m_ITDB02_28->setBackColor(BLACK);
		m_ITDB02_28->print("Activate BIOChip?", CENTER, 80);
		
		m_ITDB02_28->print("Yes(1)/No(0)", 1, 120);
		
		printFooter();
		m_Printed = true;
	}
	
	void DisplayManager::printBIOActivatingPage()
	{
			printHeader();

		m_ITDB02_28->setColor(TEXT_COLOR);
		m_ITDB02_28->setBackColor(BLACK);
		m_ITDB02_28->print("Activating...", CENTER, 80);
		
		printFooter();
		m_Printed = true;
	}
	
	void DisplayManager::printBIOActivatingErrorPage()
	{
		printHeader();

		unsigned long ts = millis(); 
			
		if ( (ts % BLINK_MS) == 0 ) {
				if (blink > 0)
					blink = 0;	
				else 
					blink = 255;
				
				m_ITDB02_28->setColor(blink, 0, 0);
				m_ITDB02_28->setBackColor(BLACK);
				
				m_ITDB02_28->print("Error BIOChip already", CENTER, 80);
				m_ITDB02_28->print("activated.", CENTER, 120);
		}

		printFooter();
		m_Printed = true;
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
	
	void DisplayManager::drawKeys()
	{
		int x;
		int top_left_corner_x;
		int top_left_corner_y;
		
		int bottom_right_corner_x;
		int bottom_right_corner_y;
		
		// Draw the upper row of buttons
		for (x=0; x<6; x++)
		{
			top_left_corner_x 		= KEY_LEFT + ( x * ( KEY_BUTTON_SIZE + KEY_LEFT_OFFSET ) );
			bottom_right_corner_x 	= KEY_LEFT + ( x * ( KEY_BUTTON_SIZE + KEY_LEFT_OFFSET ) ) + KEY_BUTTON_SIZE;
			
			top_left_corner_y 		= KEY_TOP + KEY_TOP_OFFSET;
			bottom_right_corner_y 	= KEY_TOP + KEY_TOP_OFFSET + KEY_BUTTON_SIZE;
			
			m_ITDB02_28->setColor(0, 255, 0);
			m_ITDB02_28->fillRoundRect ( top_left_corner_x, top_left_corner_y, bottom_right_corner_x, bottom_right_corner_y);
			
			m_ITDB02_28->setColor(0, 0, 0);
			m_ITDB02_28->setBackColor(0, 255, 0);
			
			if (x<5)
				m_ITDB02_28->printNumI(	x+1 , top_left_corner_x + KEY_BUTTON_SIZE/2, top_left_corner_y + KEY_BUTTON_SIZE/2 );
			else 
			{
				m_ITDB02_28->setColor(0, 255, 0);
				m_ITDB02_28->fillRoundRect ( top_left_corner_x, top_left_corner_y, bottom_right_corner_x + KEY_BUTTON_SIZE, bottom_right_corner_y);
				
				m_ITDB02_28->setColor(0, 0, 0);
				m_ITDB02_28->setBackColor(0, 255, 0);
				m_ITDB02_28->print("OK", top_left_corner_x + KEY_BUTTON_SIZE/2, top_left_corner_y + KEY_BUTTON_SIZE/2);
			}
		}
		
		// Draw the center row of buttons
		for (x=0; x<6; x++)
		{
			top_left_corner_x 		= KEY_LEFT + ( x * ( KEY_BUTTON_SIZE + KEY_LEFT_OFFSET ) );
			bottom_right_corner_x 	= KEY_LEFT + ( x * ( KEY_BUTTON_SIZE + KEY_LEFT_OFFSET ) ) + KEY_BUTTON_SIZE;
			
			top_left_corner_y 		= KEY_TOP + 2*KEY_TOP_OFFSET + KEY_BUTTON_SIZE;
			bottom_right_corner_y 	= KEY_TOP + 2*KEY_TOP_OFFSET + 2*KEY_BUTTON_SIZE;
			
			m_ITDB02_28->setColor(0, 255, 0);
			m_ITDB02_28->fillRoundRect ( top_left_corner_x, top_left_corner_y, bottom_right_corner_x, bottom_right_corner_y);
			
			m_ITDB02_28->setColor(0, 0, 0);
			m_ITDB02_28->setBackColor(0, 255, 0);
			
			if (x<4)
			{
			  m_ITDB02_28->printNumI(x+6,top_left_corner_x + KEY_BUTTON_SIZE/2, top_left_corner_y + KEY_BUTTON_SIZE/2 );
			}
			else 
			{
				if (x==4)
				{
					m_ITDB02_28->print("0", top_left_corner_x + KEY_BUTTON_SIZE/2, top_left_corner_y + KEY_BUTTON_SIZE/2);
				}
				else 
				{
					m_ITDB02_28->setColor(0, 255, 0);
					m_ITDB02_28->fillRoundRect ( top_left_corner_x, top_left_corner_y, bottom_right_corner_x + KEY_BUTTON_SIZE, bottom_right_corner_y);
					
					m_ITDB02_28->setColor(0, 0, 0);
					m_ITDB02_28->setBackColor(0, 255, 0);
					m_ITDB02_28->print("KO", top_left_corner_x + KEY_BUTTON_SIZE/2, top_left_corner_y + KEY_BUTTON_SIZE/2 );
				}
			}
		}
		

		
		/*
		
		// Draw the lower row of buttons
		  m_ITDB02_28->setColor(0, 0, 255);
		  m_ITDB02_28->fillRoundRect (KEY_LEFT_OFFSET, KEY_TOP+130, 150, 3*KEY_BUTTON_SIZE);
		  m_ITDB02_28->setColor(255, 255, 255);
		  m_ITDB02_28->drawRoundRect (KEY_LEFT_OFFSET, KEY_TOP+130, 150, 3*KEY_BUTTON_SIZE);
		  m_ITDB02_28->print("Clear", 40, 147);
		  m_ITDB02_28->setColor(0, 0, 255);
		  m_ITDB02_28->fillRoundRect (160, KEY_TOP+130, 300, 3*KEY_BUTTON_SIZE);
		  m_ITDB02_28->setColor(255, 255, 255);
		  m_ITDB02_28->drawRoundRect (160, KEY_TOP + 130, 300, 3*KEY_BUTTON_SIZE);
		  m_ITDB02_28->print("Enter", 190, 147);
		  m_ITDB02_28->setBackColor (0, 0, 0);
		*/
	}
}