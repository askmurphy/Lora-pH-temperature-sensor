extern float lat_value, lng_value, alt_value, tempsensor_value, pHsensor_value;
extern int hdop_value,sats_value,delaytime,delaytimeShort;
extern int buttonUser_status,menuMode;

extern int gpsMode;
extern int ButtonMenu;
extern int ButtonSet;
extern int ButtonUser;

#define menuMode_pH4 1
#define menuMode_pH7 2
#define menuMode_pH10 3
#define menuMode_pHDefaults 4
#define menuMode_GPSon 5 
#define menuMode_GPSonPlus 6
#define menuMode_GPSoff 7
#define menuMax 7

#define display_LoRa 1
#define display_Calibration 2
#define display_Setting 3