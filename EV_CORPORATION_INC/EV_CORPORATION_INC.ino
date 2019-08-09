#include <UTFT.h>
#include <Keypad.h>


#include "InputManager.h"
#include "Start_State.h"


using namespace EVCorporation;
using namespace EVStates;




extern uint8_t BigFont[];
UTFT ITDB02_28(ITDB28,38,39,40,41); //needed to be injected because of heap problems with the library loaded dinamically



const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {43, 45, 47, 49}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {42, 44, 46, 48}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


DisplayManager* m_DisplayManager;
InputManager*   m_InputManager;
EVState* m_CurrentState;

void setup() 
{
  Serial.begin(9600);
  
  ITDB02_28.InitLCD();
  ITDB02_28.setFont(BigFont);
  ITDB02_28.clrScr();

  m_DisplayManager = DisplayManager::GetInstance();
  m_DisplayManager->setup(&ITDB02_28);

  m_InputManager = InputManager::GetInstance();
  m_InputManager->setup(&keypad);

  m_CurrentState = new Start_State(millis());
}
void loop() 
{
   m_InputManager->loop(); //read digit
   m_CurrentState = m_CurrentState->loop(); //update state
}
