// TTGO T-Beam Lora 

#include "Arduino.h"
#include "display.h"
#include "common.h"
#include <EasyButton.h>

// constants won't change. They're used here to set pin numbers:
// PCB button 4 (near GPS antenna) = calibration MENU
// PCB button 2 = calibrate SET

// gpio-0: don't use it, works as reset!
// gpio-32: don't use it, GPIO32 is connected to DIO2 of the LoRa radio 
// gpio-33: is not resetting status..

// use a powered HUB when connected to a computer/laptop, otherwise application will crash sometimes:
// FAILURE: .pio\libdeps\ttgo_t_beam_v1\MCCI LoRaWAN LMIC library\src\lmic\radio.c:1065

// options: 2,4,13,(14 Lora?),15,35,39  the number of the pushbutton pin

const int buttonPinMENU = 2;    
const int buttonPinSET = 4;    
const int buttonPinUSER = 13;   

EasyButton buttonMenu(buttonPinMENU);
EasyButton buttonSet(buttonPinSET);
EasyButton buttonUser(buttonPinUSER);

bool buttonMenu_pressed = false;
bool buttonSet_pressed = false;
bool buttonUser_pressed = false;
int buttonUser_status=0;

void buttonUserPressed()
{
   buttonUser_pressed = true;
   Serial.println("User Button pressed");
}

void buttonUsersequenceEllapsed()
{
   Serial.println("User Button Double click");
}

void buttonUserISR()
{
   buttonUser.read();
}

void buttonMenuPressed()
{
   buttonMenu_pressed = true;
   Serial.println("Menu Button pressed");
}

void buttonMenusequenceEllapsed()
{
   Serial.println("Menu Button Double click");
}

void buttonMenuISR()
{
   buttonMenu.read();
}

void buttonSetPressed()
{
   buttonSet_pressed = true;
   Serial.println("Set Button pressed");
}

void buttonSetsequenceEllapsed()
{
   Serial.println("Set Button Double click");
}

void buttonSetISR()
{
   buttonSet.read();
}

void buttons_Init(void)
{  
   buttonUser.begin();
   buttonUser.onPressed(buttonUserPressed);
   buttonUser.onSequence(2, 1500, buttonUsersequenceEllapsed);
   if (buttonUser.supportsInterrupt()) {buttonUser.enableInterrupt(buttonUserISR);}
   buttonMenu.begin();
   buttonMenu.onPressed(buttonMenuPressed);
   buttonMenu.onSequence(2, 1500, buttonMenusequenceEllapsed);
   if (buttonMenu.supportsInterrupt()) {buttonMenu.enableInterrupt(buttonMenuISR);}
   buttonSet.begin();
   buttonSet.onPressed(buttonSetPressed);
   buttonSet.onSequence(2, 1500, buttonSetsequenceEllapsed);
   if (buttonSet.supportsInterrupt()) {buttonSet.enableInterrupt(buttonSetISR);}
}

void readbuttons(void) 
{
   if (buttonUser_pressed) {
      buttonUser_pressed = false;
      display_toggle();
   }
   if (buttonMenu_pressed) {
      buttonMenu_pressed = false;
      menuMode+=1;
      if (menuMode>menuMax) { menuMode=0;}
      display_Menubutton_pressed();
   }
   if (buttonSet_pressed) {
      buttonSet_pressed = false;      
      display_Setbutton_pressed();
   }
} 