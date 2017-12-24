extern "C" {
  #include "user_interface.h"
  #include "wpa2_enterprise.h"
}

#include <ESP8266WiFi.h>

// SSID to connect to
static const char* ssid = "WIFI@YNOV";
// Username for authentification
static const char* username = "louis.delfieux@ynov.com";
// Password for authentification
static const char* password = "Joloal91";

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
    // Setting ESP into STATION mode only (no AP mode or dual mode)
  wifi_set_opmode(STATION_MODE);

  struct station_config wifi_config;

  memset(&wifi_config, 0, sizeof(wifi_config));
  strcpy((char*)wifi_config.ssid, ssid);

  wifi_station_set_config(&wifi_config);

  wifi_station_clear_cert_key();
  wifi_station_clear_enterprise_ca_cert();

  wifi_station_set_wpa2_enterprise_auth(1);
  wifi_station_set_enterprise_username((uint8*)username, strlen(username));
  wifi_station_set_enterprise_password((uint8*)password, strlen(password));

  wifi_station_connect();

  // Wait for connection AND IP address from DHCP
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.println(".");
  }

  // Now we are connected
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
