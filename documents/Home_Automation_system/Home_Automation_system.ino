/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "85277e2424874235b45d4b3f9c75c57b";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "JioFi4_1E1A8F";
char pass[] = "n9e1h3gwmu";

#define DHTPIN 2 //Digital pin 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;
int LDRPin = A0;  //define a pin for Photo resistor
int ledPin=5; //D1     //define a pin for LED
int sensorValue=0;
int tPin = D2 ;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);


  if(t>30)
    {
      digitalWrite(tPin, HIGH);
      Serial.println("Light On");
    }
    else
    {
      digitalWrite(tPin, LOW);
      Serial.println("Light Off");
    }
  
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  dht.begin();

  timer.setInterval(1000L, sendSensor);
    
    pinMode( ledPin, OUTPUT );
}

void loop()
{
  Blynk.run();
  timer.run();
  sensorValue=analogRead(LDRPin);   //read  the value of the photoresistor.
    Serial.println(sensorValue);  // value of the photoresistor to the serial monitor.
    
      if(sensorValue>100)   // it means darkness detected
    {
    digitalWrite(ledPin, HIGH);  //on the ledPin. 
    Serial.println("Light On");
    }  
    else
    {
          digitalWrite(ledPin, LOW);  //off the ledPin. 
         Serial.println("Light Off");                                           
    }
    
   delay(500); //short delay for faster response to light.
}
