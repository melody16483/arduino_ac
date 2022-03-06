#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Panasonic.h>
#include <SoftwareSerial.h>

//wifi data
const char ssid[] = "ASUS4F";  // your network name
const char pass[] = "internet01";   // your network password       
WiFiClient  client;

//ac data
const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRPanasonicAc ac(kIrLed);

//---------Channel Details---------//
unsigned long channelID = 1467821;            // Channel ID
const char * readKey = "IOQU4ZHV8H7RDSHU"; // Read API Key
const char * writeKey = "2BG7NSL1HYBXHD1K"; //Write API Key
const int TempField = 1;  // Temp database
const int PycontrolField = 2; // pyControl database
//-------------------------------//
const  long pyControl = 100;

void setup()
{ ac.begin();
  Serial.begin(115200);
  delay(200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  pinMode(LED_BUILTIN, OUTPUT); //test working
  
  
}

void loop()
{
  // test working//
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(1000);                      // Wait for two seconds (to demonstrate the active low LED)
  
  //---------------------------------------------------//
  //--------------- Connect Network -----------------//
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ....");
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
    Serial.println("Connected to Wi-Fi Succesfully.");
  }
  //--------- End of Network connection--------//
  ThingSpeak.writeField(channelID, PycontrolField, pyControl, writeKey);
  delay(2000);

  //---------------- Read Last Data ----------------//
  long temp = ThingSpeak.readLongField(channelID, TempField, readKey);
  long statusCode = ThingSpeak.getLastReadStatus();
  
  if (statusCode == 200)
  {
    Serial.print("Temperature: ");
    Serial.println(temp);
    if (temp>34){
      ac.on();
      ac.setTemp(27);
      Serial.println("set temp:27");
    }
    else if (temp>30 && temp<35){
      ac.on();
      ac.setTemp(28);
      Serial.println("set temp:28");
    }
    else if (temp>28 && temp<31){
      ac.on();
      ac.setTemp(29);
      Serial.println("set temp:29");
    }
    else{
      ac.off();
      Serial.println("turn off ac");
    }
  }
  else
  {
    Serial.println("Data reading failed.");
  }
  delay(180000);
  Serial.println("sleep");
  //power saving//
  //ESP.deepSleep(180e6);
  
  //-------------- End of Data Reading -------------//
}
