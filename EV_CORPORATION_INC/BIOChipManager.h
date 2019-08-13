#pragma once

namespace EVCorporation
{
	class BIOChipManager 
	{
		private:
			const char *m_BIOChips[4];
			bool m_Enabled[4];
			
			static BIOChipManager* m_Instance;
			
			BIOChipManager();

		public:
			static BIOChipManager* GetInstance();
			bool DisableBIOChip(char *PIN);
			bool EnableBIOChip(char *PIN);
      bool IsEnabled(char *PIN);
			void resetBIOChips();
			bool CheckBIOChipPIN(char *PIN);
			short int GetBIOChipPINIndex(char *PIN);
	};
}
