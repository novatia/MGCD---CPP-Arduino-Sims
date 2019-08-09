#pragma once
#include <UTFT.h>

namespace EVCorporation
{
	class DisplayManager {
		private:

			static DisplayManager* m_Instance;
			UTFT* m_ITDB02_28;
			bool m_Printed;
			
			DisplayManager();
			void printHeader();
			void printFooter();
			
		public:
			static DisplayManager* GetInstance();

			void setup( UTFT* ITDB02_28 );
			void clear();
						
			void printStartPage();
			void printUserPINPage(char* PIN);
			void printUserMenuPage();
			void printNoDataPage();
			void printAdminPINPage(char* PIN);
			void printAdminMenuPage();
			void drawKeys();
	};
}