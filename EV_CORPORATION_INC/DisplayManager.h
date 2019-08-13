#pragma once
#include <UTFT.h>

#define WIDTH_RESOLUTION 320

namespace EVCorporation
{
	class DisplayManager 
	{
		private:
			unsigned int m_Blink = 255;
			bool m_EnableLED;
      bool m_EnableLoader;
      
      //parameter coming from main loop
      unsigned int m_Timeout;
    
      //current parameter
      unsigned long m_CurrentStartTime=0;
      unsigned long m_CurrentTime = 0;
      unsigned long m_CurrentTick = 0;
      unsigned int m_LastProgress = 0;

      
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

      void SetLoader(unsigned int time_out);
       void ResetLoader();
      unsigned int GetProgress();
	};
}
