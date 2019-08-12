#pragma once
#include <UTFT.h>

namespace EVCorporation
{
	class DisplayManager 
	{
		private:
			unsigned int m_Blink = 255;
			
			static DisplayManager* m_Instance;
			UTFT* m_ITDB02_28;
			
			bool m_PrintedBody;
			bool m_PrintedHeader;
			bool m_PrintedFooter;
			
			DisplayManager();
			void printHeader();
			void printFooter();
			
		public:
			static DisplayManager* GetInstance();

			void setup( UTFT* ITDB02_28 );
			void clear();
			
			void printTextNTOPage(const char* message, bool blink);
			void printPINPage(char *message, char* PIN, unsigned short int PIN_len);
			void printUserMenuPage(char *message, char **choices, unsigned short int choices_count  );
			
	};
}