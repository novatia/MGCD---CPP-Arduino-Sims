#include "BIOChipManager.h"

namespace EVCorporation
{
	BIOChipManager* BIOChipManager::m_Instance;
		
	BIOChipManager::BIOChipManager()
	{
		m_BIOChips[0] = "6824";
		m_BIOChips[1] = "5249";
		m_BIOChips[2] = "8221";
		m_BIOChips[3] = "1438";
	}
	
	BIOChipManager* BIOChipManager::GetInstance()
	{
		if (m_Instance == nullptr)
			m_Instance = new BIOChipManager();		
		
		return m_Instance;
	}
	
	bool BIOChipManager::DisableBIOChip(char *PIN)
	{
		if (CheckBIOChipPIN(PIN))
		{
			m_Enabled[GetBIOChipPINIndex(PIN)] = false;
		}
	}
	
	bool BIOChipManager::EnableBIOChip(char *PIN)
	{
		if (CheckBIOChipPIN(PIN))
		{
			m_Enabled[GetBIOChipPINIndex(PIN)] = true;
		}
	}
	
	bool BIOChipManager::CheckBIOChipPIN(char *PIN)
	{
		if ( GetBIOChipPINIndex(PIN)<0 )
			return false;
		return true;
	}
	
	short int BIOChipManager::GetBIOChipPINIndex(char *PIN)
	{
		int index=-1;
		
		for (unsigned short int i = 0; i<4; i++)
		{
			index = i;
			
			for (unsigned short int j = 0; j<4; j++) 
			{
				if (PIN[j] != m_BIOChips[i][j])
					index = -1;
			}
		}
		
		return index;
	}
	
	void BIOChipManager::resetBIOChips()
	{
		m_Enabled[0] = true;
		m_Enabled[1] = true;
		m_Enabled[2] = true;
		m_Enabled[3] = true;
	}
} 