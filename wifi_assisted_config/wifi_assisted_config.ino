/*
 * Hello world web server
 * circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
 
//SSID and Password of your WiFi router
String ssid, passwd;
String response;
 
//ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
// String s = MAIN_page; //Read HTML contents
  if ( server.hasArg("ssid") ) {
    String ssid;
    String passwd;
    ssid = server.arg("ssid");
    passwd = server.arg("passwd");
    server.send(200, "text/html", response); //Send web page
  } else {
     server.send(200, "text/html", response); //Send web page
  }
}

//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  SPIFFS.begin();
  bool ok = SPIFFS.begin();
  if (ok) {
    Serial.println("ok");
    bool exist = SPIFFS.exists("/webconfig.html");

    if (exist) {
      Serial.println("The file exists!");

      File f = SPIFFS.open("/webconfig.html", "r");
      if (server.hasArg("ssid")){
        Serial.println(server.arg("ssid"));
        Serial.println(server.arg("passwd"));
      }
      if (!f) {
        Serial.println("Some thing went wrong trying to open the file...");
      }
      else {
        int s = f.size();
        Serial.printf("Size=%d\r\n", s);


  // USE THIS DATA VARIABLE

        String data = f.readString();
        Serial.println(data);
        response = data;

        f.close();
      }
    }
    else {
      Serial.println("No such file found.");
    }
  } 
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}


//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
