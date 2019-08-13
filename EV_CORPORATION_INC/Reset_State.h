#include "EVState.h"

namespace EVCorporation
{
	namespace EVStates
	{
		/*Wait 10 s*/
		class Reset_State : public EVState 
		{
			private:
				char *m_Message;
				unsigned short int m_MessageLenght;
				unsigned short int m_TimeOut;
				
				bool m_Blink;
				bool m_PressButton;
				
			public:
				~Reset_State();
				Reset_State();
				
				EVState* loop() override;
		};
	}
}