#include "BIOChipManager.h"

namespace EVCorporation
{
	BIOChipManager* BIOChipManager::m_Instance;
		
	BIOChipManager::BIOChipManager()
	{
    m_BIOChips[0][0] = 0;
    m_BIOChips[0][1] = 0;
    m_BIOChips[0][2] = 0;
    m_BIOChips[0][3] = 0;

		m_BIOChips[1][0] = '5';
    m_BIOChips[1][1] = '2';
    m_BIOChips[1][2] = '4';
    m_BIOChips[1][3] = '9';

    m_BIOChips[2][0] = '8';
    m_BIOChips[2][1] = '2';
    m_BIOChips[2][2] = '2';
    m_BIOChips[2][3] = '1';

    m_BIOChips[3][0] = '1';
    m_BIOChips[3][1] = '4';
    m_BIOChips[3][2] = '3';
    m_BIOChips[3][3] = '8';

    m_BIOChips[4][0] = '6';
    m_BIOChips[4][1] = '8';
    m_BIOChips[4][2] = '2';
    m_BIOChips[4][3] = '4';

		resetBIOChips();
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
      short int index = GetBIOChipPINIndex(PIN);
    
			m_Enabled[index] = false;
		}
	}
	
	bool BIOChipManager::EnableBIOChip(char *PIN)
	{
		if (CheckBIOChipPIN(PIN))
		{
      short int index = GetBIOChipPINIndex(PIN);
    
      m_Enabled[index] = true;
		}
	}

  bool BIOChipManager::IsEnabled(char *PIN)
  {
     short int index = GetBIOChipPINIndex(PIN) ;
    
     if ( index < 0 )
        return false;

     return m_Enabled[index];
  }
  
  
  bool BIOChipManager::AllDisabled() 
  {
		bool one_attached = false;
		
		for (int i=0;i<CHIPS;i++)
			one_attached = one_attached | m_Enabled[i];
		
		return !one_attached;
  }
  
	bool BIOChipManager::CheckBIOChipPIN(char *PIN)
	{
		  return GetBIOChipPINIndex(PIN) > 0;
	}
	
	short int BIOChipManager::GetBIOChipPINIndex(char *PIN)
	{
		short int index = -1;
		
		for (int i = 0; i<CHIPS; i++)
		{
			index = i;
			char *next_pin = m_BIOChips[i];
     
			for (int j = 0; j<4; j++) 
			{
				if (PIN[j] != next_pin[j])
					index = -1;
			}
			
      if ( index >= 0 )
        break;
		}
		
		return index;
	}
	
	void BIOChipManager::resetBIOChips()
	{
    for ( int i=0; i<CHIPS; i++)
    {
  		  m_Enabled[i] = true;
  	}

    m_Enabled[0] = false;
  }
}
