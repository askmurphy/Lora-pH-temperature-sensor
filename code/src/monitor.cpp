#include "pH.h" 
#include "temperature.h"
#include "display.h"
#include "gps.h"
#include "interface.h"
#include "common.h"

void monitor_init(void)
{  
   pHsensor_value=0; 
   tempsensor_value=0;
   lat_value=0;
   lng_value=0;
   alt_value=0;   
   hdop_value=0;
   sats_value=0;   
   menuMode=0;
   buttons_Init(); // must be initialized before the the others below!
   pH_init();
   readTemperature_setup();
   display_init();
   gps_setup();
}

void monitor_update(void)
{
   gps_loop(); 
   readTemperature();
   readpH();
   readbuttons(); 
   display_sensors();
}

void monitor_displayCounterReset(void)
{
   display_counterReset();
}

void monitor_displayLoRa(void)
{
   displayLoRaTransmit();
}

float monitor_gpsLatitude(void)
{
   return(lat_value);
}

float monitor_gpsLongitude(void)
{
   return(lng_value);
}

float monitor_gpsAltitude(void)
{
   return(alt_value);
}