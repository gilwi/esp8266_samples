#include <ESP8266WiFi.h>
 
const char* ssid = "ColocBox";//type your ssid
const char* password = "huguloma!1234567890";//type your password
 
int ledPin = 5; // GPIO2 of ESP8266
WiFiServer server(80);//Service Port

int D0_pin = 16;//green
int D1_pin = 5;//orange
int D2_pin = 4;//red

int D5_pin = 14;//green
int D6_pin = 12;//orange
int D7_pin = 13;//red

int D3_pin = 0;
int D4_pin = 2;

int value = LOW;
int police = LOW;

void init_fire(int red1, int red2) {
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
}

void fire_cycle(int green, int orange, int red, int police) {
  int i;
  int j;
  
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  if (police == HIGH){
    for (i=0; i<10; i++){
      police_lights(D3_pin, D4_pin);
    }
  }else{
    delay(2000);
  }
  

  digitalWrite(green, LOW);
  digitalWrite(orange, HIGH);
  if (police == HIGH){
    for (i=0; i<4; i++){
      police_lights(D3_pin, D4_pin);
    }
  }else{
    delay(800);
  }

  digitalWrite(orange, LOW);
  digitalWrite(red, HIGH);
  if (police == HIGH){
    for (j=0; j<3; j++){
      police_lights(D3_pin, D4_pin);
    }
  }else{
    delay(600);
  }
}

void emergency_cycle(int green, int orange, int red, int police) {
  int i, j;
  
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(orange, HIGH);
  if (police == HIGH){
    for (i=0; i<2; i++){
      police_lights(D3_pin, D4_pin);
    }
  }else{
    delay(200);
  }
  digitalWrite(orange, LOW);
  if (police == HIGH){
    for (j=0; j<2; j++){
      police_lights(D3_pin, D4_pin);
    }
  }else{
    delay(200);
  }
}

void police_lights(int blue, int red) {
  digitalWrite(red, LOW);
  digitalWrite(blue, HIGH);
  delay(100);
  digitalWrite(blue, LOW);
  digitalWrite(red, HIGH);
  delay(100);

}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //test delay(10);

  pinMode(D0_pin, OUTPUT); //green
  pinMode(D1_pin, OUTPUT); //orange
  pinMode(D2_pin, OUTPUT); //red

  pinMode(D5_pin, OUTPUT); //green
  pinMode(D6_pin, OUTPUT); //orange
  pinMode(D7_pin, OUTPUT); //red

  pinMode(D4_pin, OUTPUT); //red
  pinMode(D3_pin, OUTPUT); //blue

  init_fire(D2_pin, D7_pin);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Wait until Wifi is connected");
  }
  Serial.print("WiFi connected; you can browse to : ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
  Serial.println("Server started");

  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (value == LOW){
    fire_cycle(D0_pin, D1_pin, D2_pin, police);
    fire_cycle(D5_pin, D6_pin, D7_pin, police);
  }else{
    emergency_cycle(D0_pin, D1_pin, D2_pin, police);
    emergency_cycle(D5_pin, D6_pin, D7_pin, police);
  }

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  //test while(!client.available()){
  //test  delay(1);
  //test }
  
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request
  if (request.indexOf("/LED=ON") != -1) {
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF") != -1){
    value = LOW;
    init_fire(D2_pin, D7_pin);
  }

  // Match the request
  if (request.indexOf("/POL=ON") != -1) {
    police = HIGH;
  } 
  if (request.indexOf("/POL=OFF") != -1){
    police = LOW;
    digitalWrite(D3_pin, LOW);
    digitalWrite(D4_pin, LOW);
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Emergency mode is now: ");
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  
  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> to turn on emergency mode<br>");
  client.println("Click <a href=\"/LED=OFF\">here</a> to turn off emergency mode<br>");
  client.println("<br><br>");
  client.println("Click <a href=\"/POL=ON\">here</a> to bring police<br>");
  client.println("Click <a href=\"/POL=OFF\">here</a> to to tell police to go fuck themselves and run<br>");
  client.println("</html>");

  //test delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
