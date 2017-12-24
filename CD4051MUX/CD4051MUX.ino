#include <ArduinoJson.h>


#define A0_pin A0

/* 
 *  Set pin used
*/
const byte D0_pin = 16; // ==> CD4051BE A
const byte D1_pin = 5; // ==> CD4051BE B
const byte D2_pin = 4; // ==> CD4051BE C
const byte D3_pin = 0;
const byte D4_pin = 2;
const byte D5_pin = 14;
const byte D6_pin = 12;
const byte D7_pin = 13;
const byte D8_pin = 15; // ==> CD4051BE INH
const byte SD0_pin = 3;
const byte SD1_pin = 1;
const byte SD2_pin = 9;
const byte SD3_pin = 10;

void init_CD4051BE(){
  /* 
   *  Set CD4051BE address pins to low
  */
  pinMode(D0_pin, OUTPUT);
  pinMode(D1_pin, OUTPUT); 
  pinMode(D2_pin, OUTPUT); 
  digitalWrite(D0_pin, LOW);
  digitalWrite(D1_pin, LOW);
  digitalWrite(D2_pin, LOW);
  
  /* 
   *  Disable CD4051BE 
  */
  pinMode(D8_pin, OUTPUT);
  digitalWrite(D8_pin, LOW);
}

int readAnalogMux(byte channel) {
  
  /* 
   *  Select analog by address 
  */
  digitalWrite(D0_pin, bitRead(channel, 0));
  digitalWrite(D1_pin, bitRead(channel, 1));
  digitalWrite(D2_pin, bitRead(channel, 2));
 
  /* 
   *  Read & Return analog value
  */
  return analogRead(A0_pin);
}

void setup() {
  /* 
   *  Start Serial Session
  */
  Serial.begin(115200);
  init_CD4051BE();
}

void loop() {
  // put your main code here, to run repeatedly:
  int moistLvl = 1024 - readAnalogMux(2);
  int lightLvl = readAnalogMux(4);

  StaticJsonBuffer<200> jsonBuffer;
  
  JsonObject& root = jsonBuffer.createObject();
  root["sensor"] = "gps";
  
  JsonObject& data = root.createNestedObject("data");
  data["light"] = lightLvl;
  data["moist"] = moistLvl;
  
  root.printTo(Serial);
  Serial.println();

  delay(5000);
}
