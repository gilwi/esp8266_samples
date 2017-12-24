#include <Arduino.h>
#include <ESP8266WiFi.h>
#ifdef ESP8266
extern "C" {
#include "user_interface.h"
#include "wpa2_enterprise.h"
}
#endif

static u8 ent_username[] = "louis.delfieux@ynov.com";
static u8 ent_password[] = "test";

void setup(){
  char a[100];
  ip_info info;
  wifi_get_ip_info(0, &info);

  Serial.begin(115200);

  wifi_station_disconnect();
  wifi_set_opmode(STATION_MODE);

  char ssid[32] = "my_enterprise_ap";
  char password[64] = {0x00};
  struct station_config stationConf;
  stationConf.bssid_set = 0;  //need not check MAC address of AP
  memcpy(&stationConf.ssid, ssid, 32);
  memcpy(&stationConf.password, password, 64);

  if(!wifi_station_set_config(&stationConf)){
    Serial.print("\r\nset config fail\r\n");
  }

  // switch to WPA2 Enterprise 
  wifi_station_set_wpa2_enterprise_auth(1); 

  if(wifi_station_set_enterprise_username (ent_username, sizeof(ent_username))){
    Serial.print("\r\nusername set fail\r\n");
  }
  if(wifi_station_set_enterprise_password (ent_password, sizeof(ent_password))){
    Serial.print("\r\npassword set fail\r\n");
  }

  if(!wifi_station_connect()){
    Serial.print("\r\nconnect fail\r\n");
  }

  Serial.print("\r\ntrying to connect...");

  while(info.ip.addr == 0){
    ESP.wdtFeed();
    Serial.print(".");
    delay(1000);
    wifi_get_ip_info(0, &info);
  }

  sprintf(a, "%"PRIu32,info.ip.addr);
  Serial.print("\r\nip addr: ");
  Serial.print(a);
  Serial.print("\r\n");
}


void loop()
{ 
}
