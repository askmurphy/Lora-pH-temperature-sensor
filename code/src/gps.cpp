#include "TinyGPS++.h"
#include "common.h"

#define GPS_SERIAL_NUM  1
#define GPS_BAUDRATE    9600
#define GPS_RX_PIN      34
#define GPS_TX_PIN      12

uint32_t LatitudeBinary;
uint32_t LongitudeBinary;
uint16_t altitudeGps;
uint8_t hdopGps;
uint8_t sats;
char t[32]; // used to sprintf for Serial output

TinyGPSPlus _gps;
HardwareSerial _serial_gps(GPS_SERIAL_NUM);

void gps_time(char * buffer, uint8_t size) {
    snprintf(buffer, size, "%02d:%02d:%02d", _gps.time.hour(), _gps.time.minute(), _gps.time.second());
}

float gps_hdop() {
    return _gps.hdop.hdop();
}

uint8_t gps_sats(void) {
    return _gps.satellites.value();
}

void gps_setup(void) {
    _serial_gps.begin(GPS_BAUDRATE, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
}

void gps_loop(void) {
    while (_serial_gps.available()) {
        _gps.encode(_serial_gps.read());
    }
    hdopGps = _gps.hdop.value() / 10;
    sats = _gps.satellites.value();
    alt_value=_gps.altitude.meters();
    lat_value=_gps.location.lat();
    lng_value=_gps.location.lng();
    hdop_value=hdopGps;
    sats_value=sats;    
    #ifdef USE_SERIAL 
       sprintf(t, "Alt: %f", alt_value);
       Serial.println(t); 
       sprintf(t, "Lat: %f", lat_value);
       Serial.println(t);
       sprintf(t, "Lng: %f", lng_value);
       Serial.println(t);
       sprintf(t, "Hdop: %d", hdopGps);
       Serial.println(t);
       sprintf(t, "Sats: %d", sats);
       Serial.println(t);
    #endif   
}