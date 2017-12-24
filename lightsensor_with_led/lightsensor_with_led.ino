#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#define lightsensor A0

//test
int D0_pin = 16;

/* Wifi Related */
const char* ssid = "ColocBox";//type your ssid
const char* password = "huguloma!1234567890";//type your password
/* MQTT Related */
const char* mqtt_server = "10.0.0.91";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void callback(char* topic, byte* payload, unsigned int length)
{
} //end callback

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      //once connected to MQTT broker, subscribe command if any
      //client.subscribe("OsoyooCommand");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 6 seconds before retrying
      delay(6000);
    }
  }
} //end reconnect()

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // test
  pinMode(D0_pin, OUTPUT);
  digitalWrite(D0_pin, HIGH);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Wait until Wifi is connected");
  }
  Serial.print("WiFi connected; you can browse to : ");
  Serial.println(WiFi.localIP());

  /* MQTT Related */
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    int lightInt = analogRead(lightsensor);
    String LightLvl = String(lightInt);
    
    char message[10];
    LightLvl.toCharArray(message,10);
    Serial.println(message);
  
    //publish sensor data to MQTT broker
    client.publish("SmartPlant01", message);
  }
}
