#pragma once

namespace EVCorporation
{
	class BIOChipManager 
	{
		private:
			char m_BIOChips[4];
			bool m_Enabled[4];
			
			static BIOChipManager* m_Instance;
			
			BIOChipManager();

		public:
			static DisplayManager* GetInstance();
			bool DisableBIOChip(char *PIN);
			bool EnableBIOChip(char *PIN);
			void resetBIOChips();
			
	};
}