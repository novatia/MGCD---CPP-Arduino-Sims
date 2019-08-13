#pragma once

#define CHIPS 5

namespace EVCorporation
{
	class BIOChipManager 
	{
		private:
			static BIOChipManager* m_Instance;
      bool m_Enabled[CHIPS];
			char m_BIOChips[CHIPS][4];
      
			BIOChipManager();

		public:
			static BIOChipManager* GetInstance();
			bool DisableBIOChip(char *PIN);
			bool EnableBIOChip(char *PIN);
			bool IsEnabled(char *PIN);
			bool AllDisabled();
			void resetBIOChips();
			bool CheckBIOChipPIN(char *PIN);
			short int GetBIOChipPINIndex(char *PIN);
	};
}
