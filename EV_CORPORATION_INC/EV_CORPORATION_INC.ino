#include <UTFT.h>
#include <Keypad.h>

#include "BIOChipManager.h"

#include "TextNTO_State.h"
#include "PIN_State.h"
#include "Menu_State.h"
#include "BIOChipON_State.h"
#include "BIOChipOFF_State.h"

using namespace EVCorporation;
using namespace EVStates;

#define BLUE_PIN  11
#define GREEN_PIN 12
#define RED_PIN   13

extern uint8_t BigFont[];
UTFT ITDB02_28(ITDB28,38,39,40,41); //needed to be injected because of heap problems with the library loaded dinamically

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns

char keys[ROWS][COLS] = {
  {'1','4','7','*'},
  {'2','5','8','0'},
  {'3','6','9','#'},
  {'A','B','C','D'}
};

byte rowPins[ROWS] = {49, 47, 45, 43}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {48, 46, 44, 42}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const char *press_a_button = "Press a button";

DisplayManager* m_DisplayManager;
BIOChipManager* m_BIOChipManager;

EVState* m_CurrentState;


void setup() 
{
    Serial.begin(9600);
    
    ITDB02_28.InitLCD();
    ITDB02_28.setFont(BigFont);
    ITDB02_28.clrScr();
 
    m_DisplayManager = DisplayManager::GetInstance();
    m_DisplayManager->setup(&ITDB02_28);
  
    const char* UserPIN = "3845";
    const char* AdminPIN= "16245";
    const char* UserPINMessage =  "Insert user PIN";
    const char* AdminPINMessage = "Insert admin PIN";
    const char* UserMenuMessage = "User menu";
    const char* NoDataMessage = "*** No data ***";
    const char* AdminMenuMessage = "Admin menu";
    const char* BIOChipPINMessage = "Insert Clone ID";
  
    BIOChipON_State* BIOChipONState = new BIOChipON_State(&keypad, nullptr, nullptr, BIOChipPINMessage,16,4,millis());
    BIOChipOFF_State* BIOChipOFFState = new BIOChipOFF_State(&keypad, nullptr, nullptr, BIOChipPINMessage,16,4,millis());
    
    EVState* AdminMenu[2];
    
    const char AdminMenuKeys[3] = {'1','2'};
    const char* AdminMenuChoices[3] = {"1)Activate BIOChip","2)Detach BIOChip"};
    AdminMenu[0] = BIOChipONState;
    AdminMenu[1] = BIOChipOFFState; 
    
    EVState* admin_menu_state     =  new Menu_State(&keypad, nullptr, AdminMenu, AdminMenuChoices, AdminMenuKeys, 2, AdminMenuMessage,11, millis());

    BIOChipONState->SetPreviousState(admin_menu_state);
    BIOChipONState->SetErrorPreviousState(admin_menu_state);

    BIOChipOFFState->SetPreviousState(admin_menu_state);
    BIOChipOFFState->SetSuccessPreviousState(admin_menu_state);
    
    
    EVState* admin_pin_state =  new PIN_State(&keypad, nullptr, admin_menu_state, AdminPINMessage,17,AdminPIN,5,millis());
    
    EVState* user_menu_1 =   new TextNTO_State(&keypad, nullptr, nullptr, millis(), NoDataMessage, 16, 4, true, false);
  
    EVState* UserMenu[3];
    const char UserMenuKeys[3] = {'1','2','3'};
    const char* MenuChoices[3] = {"1)Download BIOData","2)Manage BIOChip","3)Show BIOData"};
    
    UserMenu[0] = user_menu_1;
    UserMenu[1] = admin_pin_state;
    UserMenu[2] = user_menu_1;
        
    EVState* menu_state     =  new Menu_State(&keypad, nullptr, UserMenu, MenuChoices, UserMenuKeys, 3, UserMenuMessage,10, millis());
    
    user_menu_1->SetPreviousState(menu_state);
    admin_pin_state->SetPreviousState(menu_state);
    
    EVState* user_pin_state =  new PIN_State(&keypad, nullptr, menu_state, UserPINMessage,16,UserPIN,4,millis());
    EVState* start_state    =  new TextNTO_State(&keypad, nullptr, user_pin_state, millis(), press_a_button, 15, 0, true, true);
    
    user_pin_state->SetPreviousState(start_state);
    
    m_CurrentState = start_state;
}

void loop() 
{
     m_CurrentState =  m_CurrentState->loop();
}
