
#define BLYNK_PRINT Serial
#include <ThingSpeak.h> 
#include <ESP8266WiFi.h>

#include <SoftwareSerial.h>

char ssid[] = "WiFi";   
char pass[] = "password";          
WiFiClient  client;

unsigned long myChannelNumber = 2633195;
const char * myWriteAPIKey = "WGBHME3D7K385C88";

String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors

void setup() {
  Serial.begin(115200); 
  while (!Serial) {
    ; 
  }
    // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  
      Serial.print("Conncting to wifi.");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  ThingSpeak.begin(client);  
}

void loop(){  
  if(Serial.available() > 0 ){
    rdata = Serial.read();
    myString = myString+ rdata;
    // Serial.print(rdata);
    if( rdata == '\n'){
      Serial.println(myString);
      ThingSpeak.setField(1,myString);
      int x = ThingSpeak.writeField(myChannelNumber,myWriteAPIKey);
      if(x == 200){
        Serial.println("Channel update successful.");
      }
      else{
        Serial.println("Problem updating channel. HTTP error code " + String(x));
      }
      delay(5000);
      myString = "";
    }
  }
}
