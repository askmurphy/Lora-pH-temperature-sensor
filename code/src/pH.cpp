/*

////////////////////////// pH sensor //////////////

One, two or three-point calibration can be done.

https://cimpleo.com/blog/simple-arduino-ph-meter/

//Arduino pH-meter
//PH Probe Sensor Pinout
//TO – Temperature output
//DO – 3.3V pH limit trigger
//PO – PH analog output
//Gnd – Gnd for PH probe
//Gnd – Gnd for board
//VCC – 5V DC
//POT 1 – Analog reading offset (Nearest to BNC connector)
//POT 2 – PH limit setting
*/ 

#include "ph_grav.h"     
#define PH_SENSOR_GPIO 36

float pHsensor_value=0;

   Gravity_pH pH = Gravity_pH(PH_SENSOR_GPIO);
   uint8_t user_bytes_received = 0;     
   const uint8_t bufferlen = 32;    
   char user_data[bufferlen];   

void pH_init(void)
{
   delay(200);
   if (pH.begin()) {                                     
      Serial.println("Loaded EEPROM");
   }   
}

void readpH(void)
{
   pHsensor_value=pH.read_ph();
   if (pHsensor_value>14) { // pH meter not connected..
      pHsensor_value=-1;
   }
}

float pH_cal4(void)
{
   pH.cal_low();   
   return(pH.pH_getLow());
}

float pH_cal7(void)
{
   pH.cal_mid();   
   return(pH.pH_getMid());
}

float pH_cal10(void)
{
   pH.cal_high();  
   return(pH.pH_getHigh());
}

void pH_clear(void)
{
   Serial.print("pH Low: ");
   Serial.println(pH.pH_getLow());

   Serial.print("pH Mid: ");
   Serial.println(pH.pH_getMid());

   Serial.print("pH High: ");
   Serial.println(pH.pH_getHigh());

   pH.cal_clear(); 
   pH_init();
}