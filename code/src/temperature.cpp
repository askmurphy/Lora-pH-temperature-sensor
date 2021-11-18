// TTGO T-Beam Lora 
// https://github.com/tekk/TTGO-T-Beam-Car-Tracker

  ////////////////////////// temperatuur sensor //////////////
#include "OneWire.h"
#include "DallasTemperature.h"
#include "temperature.h"

float tempsensor_value=0;
// Data wire is plugged into pin 25 TTGO T-Beam
#define ONE_WIRE_BUS 25 
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void readTemperature_setup(void)
{
   sensors.begin();
}

float randomTemperature() 
{
   float tempC=0;  
   // print a random number from 0 to 299
   //  randNumber = random(300);
   //  Serial.println(randNumber);
   // print a random number from 10 to 19
   tempC = random(10, 40);
   //Serial.println(randNumber);
   return(tempC);
}

void readTemperature(void)
{
   tempsensor_value=0;    
   sensors.requestTemperatures(); // Send the command to get temperatures
   tempsensor_value = sensors.getTempCByIndex(0);
   Serial.print(F("Temperatuur: "));
   // random:
   // tempC=randomTemperature();
   Serial.println(tempsensor_value);
}
   