    ////////////////// 1602 LCD I2C //////////////
    #include "Arduino.h"
    #include "Wire.h"
    #include "LiquidCrystal_I2C.h"
    #include "common.h"
    #include "pH.h"

    LiquidCrystal_I2C lcd(0x3F,20,4); 

   char tt[32]; // used to sprintf for LCD output

   boolean displaystate=true;       

   void display_clr_banner(int displaymode)
   {
      lcd.clear();
      lcd.setCursor(0,0);
      switch(displaymode) {
         case display_LoRa: 
            lcd.print("LoRa monitor");
         break;
         case display_Calibration: 
            lcd.print("Calibration");
         break;
         default: // display_Setting
            lcd.print("Settings");
      }
   } 

  // void(* resetFunc) (void) = 0;//declare reset function at address 0
   void display_reset(void)
   {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LoRa monitor");
      lcd.setCursor(0,1);
      lcd.print("RESETTING...");
      delay(delaytime);  
     // resetFunc(); //call reset 
   } 

   void display_state(bool mode)
   {
      if (mode) {         
         lcd.setBacklight(true);
         displaystate=1;
      } else {          
         lcd.setBacklight(false);
         displaystate=0;
      }
   } 

   void display_toggle(void)
   {
      display_state(!displaystate);      
   }

   void display_init()
   {
      // 1602 LCD init //
      lcd.init();                     
      lcd.backlight();   
   }

   void display_counterReset(void)
   {
      display_clr_banner(display_LoRa); 
      lcd.setCursor(0,1);
      lcd.print("Ticker reset cmd");
      delay(delaytime);
   }

   void Userbutton_pressed(void)
   {
      display_state(buttonUser_status); 
      buttonUser_status=!buttonUser_status;   
   }

   void display_GPS(void)
   {        
      if (gpsMode==menuMode_GPSon || gpsMode==menuMode_GPSonPlus)
      {
         if (lat_value>0) {
            lcd.clear();
            lcd.setCursor(0,0);
            sprintf(tt, "Lat: %f", lat_value);
            lcd.print(tt);
            lcd.setCursor(0,1);
            sprintf(tt, "Lng: %f", lng_value);
            lcd.print(tt);
            delay(delaytime);                    
            if (gpsMode==menuMode_GPSonPlus) {
               lcd.clear();
               lcd.setCursor(0,0);         
               lcd.print("GPS data");
               lcd.setCursor(0,1);
               sprintf(tt, "Sat: %d", sats_value);
               lcd.print(tt);
               lcd.setCursor(8,1);
               sprintf(tt, "Hdop: %d", hdop_value);
               lcd.print(tt);
               delay(delaytime);
            }
         } else {
            display_clr_banner(true); 
            lcd.setCursor(0,1);
            lcd.print("No GPS data yet...");
            delay(delaytimeShort);
         }
      }      
   }

  void display_sensors(void)
   {  
      if (menuMode==0) {
         display_clr_banner(display_LoRa);      
         lcd.setCursor(0,1);
         lcd.print("pH");
         lcd.setCursor(3,1);
         lcd.print("    ");
         lcd.setCursor(3,1);
         if (pHsensor_value<0) {
            lcd.print("???");
         } else {
            sprintf(tt, "%d.%02d", (int)pHsensor_value, (int)(pHsensor_value*100)%100);
            lcd.print(tt);
         }
         lcd.setCursor(10,1);
         lcd.print("    ");
         lcd.setCursor(10,1);
         if (tempsensor_value<-100) {
            lcd.print("???");
         } else {
            lcd.print(tempsensor_value);
         }
         lcd.setCursor(14,1);
         lcd.print("'C");
         delay(delaytime);
         display_GPS();
      }
   }

   void display_Menubutton_pressed(void)
   {
      if (displaystate==0) {         
         display_toggle();
      }    
      switch(menuMode) {
         case menuMode_pH4: 
            display_clr_banner(display_Calibration); 
            lcd.setCursor(0,1);   
            lcd.print("Use pH4: set    ");
         break;
         case menuMode_pH7: 
            display_clr_banner(display_Calibration); 
            lcd.setCursor(0,1);   
            lcd.print("Use pH7: set    ");
         break;
         case menuMode_pH10: 
            display_clr_banner(display_Calibration); 
            lcd.setCursor(0,1);   
            lcd.print("Use pH10: set   ");
         break;      
         case menuMode_pHDefaults: 
            display_clr_banner(display_Calibration); 
            lcd.setCursor(0,1);   
            lcd.print("pH defaults: set");
         break;      
         case menuMode_GPSon: 
            display_clr_banner(display_Setting); 
            lcd.setCursor(0,1);   
            lcd.print("Enable GPS: set");
         break;      
         case menuMode_GPSonPlus: 
            display_clr_banner(display_Setting); 
            lcd.setCursor(0,1);   
            lcd.print("Enable GPS+: set");
         break;      
         case menuMode_GPSoff: 
            display_clr_banner(display_Setting); 
            lcd.setCursor(0,1);   
            lcd.print("Disable GPS: set");
         break;      
         default: 
            menuMode=0;
            display_clr_banner(display_LoRa);   
            display_sensors();           
      }          
   }

   void calibrated(void)
   {
     switch(menuMode) {
         case menuMode_pH4:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("pH4 calibrated");
         break;
         case menuMode_pH7:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("pH7 calibrated");           
         break;
         case menuMode_pH10:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("pH10 calibrated");      
         break;  
         case menuMode_pHDefaults: 
         break;
      }
   }

   void display_Setbutton_pressed(void)
   {
      float tmp=0;
      switch(menuMode) {
         case menuMode_pH4:
            display_clr_banner(display_Calibration);   
            lcd.setCursor(0,1); 
            lcd.print("Calibrating pH4");
            tmp=pH_cal4();
            delay(delaytime);
            calibrated();
            lcd.setCursor(0,1);
            readpH();
            sprintf(tt, "%d.%02d - %d.%02d", (int)tmp, (int)(tmp*100)%100, (int)pHsensor_value, (int)(pHsensor_value*100)%100);
            lcd.print(tt);
            delay(delaytime);
         break;
         case menuMode_pH7:
            display_clr_banner(display_Calibration);  
            lcd.setCursor(0,1);
            lcd.print("Calibrating pH7");
            tmp=pH_cal7();
            delay(delaytime);
            calibrated();
            lcd.setCursor(0,1);
            readpH();
            sprintf(tt, "%d.%02d - %d.%02d", (int)tmp, (int)(tmp*100)%100, (int)pHsensor_value, (int)(pHsensor_value*100)%100);
            lcd.print(tt);
            delay(delaytime);
         break;
         case menuMode_pH10:
            display_clr_banner(display_Calibration); 
            lcd.setCursor(0,1);
            lcd.print("Calibrating pH10");
            tmp=pH_cal10();
            delay(delaytime);
            calibrated();
            lcd.setCursor(0,1);
            readpH();
            sprintf(tt, "%d.%02d - %d.%02d", (int)tmp, (int)(tmp*100)%100, (int)pHsensor_value, (int)(pHsensor_value*100)%100);  
            lcd.print(tt);
            delay(delaytime);
         break;  
         case menuMode_pHDefaults: 
            display_clr_banner(display_Calibration);  
            lcd.setCursor(0,1);
            lcd.print("Set pH defaults");
            pH_clear();
            delay(delaytime);
            lcd.setCursor(0,1);
            lcd.print("pH sensor reset");
         break;  
         case menuMode_GPSon: 
            display_clr_banner(display_Setting); 
            gpsMode=menuMode_GPSon;
            lcd.setCursor(0,1);   
            lcd.print("GPS enabled");
         break;      
         case menuMode_GPSonPlus: 
            display_clr_banner(display_Setting); 
            gpsMode=menuMode_GPSonPlus;
            lcd.setCursor(0,1);   
            lcd.print("GPS+ enabled");
         break;      
         case menuMode_GPSoff: 
            display_clr_banner(display_Setting); 
            gpsMode=menuMode_GPSoff;
            lcd.setCursor(0,1);   
            lcd.print("GPS disabled");
         break;      
      }      
   }

   void displayLoRaTransmit(void)
   {  
      if (menuMode==0) {
         lcd.setCursor(13,0);
         lcd.print(">*<"); // LoRa data send, clear not needed because display is rewritten in seconds
      }  
   }