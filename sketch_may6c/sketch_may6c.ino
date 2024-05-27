#include <Wire.h>
#include <TinyGPS++.h>
#define RXD2 16
#define TXD2 17
HardwareSerial neogps(1);

TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Dang cho tin hieu GPS");
  delay(2000);
}

void loop() {
    
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (neogps.available())
    {
      if (gps.encode(neogps.read()))
      {
        newData = true;
      }
    }
  }

  //If newData is true
  if(newData == true)
  {
    newData = false;
    Serial.println(gps.satellites.value());
    print_speed();
  }
  else
  {
    Serial.println("No Data");
  }  
  
}

void print_speed()
{
  if (gps.location.isValid() == 1)
  {
   //String gps_speed = String(gps.speed.kmph());
    Serial.print("lat: ");
    Serial.println(gps.location.lat(),6);

    Serial.print("lng: ");
    Serial.println(gps.location.lng(),6);

    Serial.print("speed: ");
    Serial.println(gps.speed.kmph());
    
    Serial.print("sat:");
    Serial.println(gps.satellites.value());

    Serial.print("alt:");
    Serial.println(gps.altitude.meters(), 0);
    
  }
  else
  {
    Serial.println("No Data");
  }  

}