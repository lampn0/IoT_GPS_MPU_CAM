// Interfacing Arduino with NEO-6M GPS module
#include <TinyGPS.h>           // Include TinyGPS++ library
#include <SoftwareSerial.h>      // Include software serial library

#define LED_PIN 2

// TinyGPSPlus gps;
TinyGPS gps;
#define S_RX    17                // Define software serial RX pin
#define S_TX    16                // Define software serial TX pin
SoftwareSerial SerialGPS(S_RX, S_TX);    // Configure SoftSerial library

String Latitude,Longitude;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  SerialGPS.begin(115200);  
}

void loop() {
  // put your main code here, to run repeatedly:
  bool newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (SerialGPS.available()) {
      // Serial.println("GPS checking ...");
      char c = SerialGPS.read();
      // Serial.write(c);
      // if (gps.encode(c)) {
      //   Serial.write(c);
        newData = true;
      // }
      gps.encode(c);
      Serial.write(c);
    }
  }

  // if (newData) {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.println(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.println(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  // }
  // smartDelay(1000);
  // if (gps.location.isUpdated()) {
  //   Latitude = String(gps.location.lat(),6);
  //   Longitude = String(gps.location.lng(), 6);
  //   Serial.print("Latitude= ");
  //   Serial.print(Latitude);
  //   Serial.print(" Longitude= ");
  //   Serial.println(Longitude);
  // }
  // else {
  //   printDateTime(gps.date);
  // }
  // while (SerialGPS.available() > 0) {
  //   if (gps.encode(SerialGPS.read())) {
  //     Serial.print("gps.location.isUpdated()   = ");
  //     Serial.println(gps.location.isUpdated());
  //     if (gps.location.isValid()) {
  //       Serial.print("Latitude   = ");
  //       Serial.println(String(gps.location.lat(), 6));
  //       Serial.print("Longitude  = ");
  //       Serial.println(String(gps.location.lng(), 6));
  //     }
  //     else
  //       Serial.println("Location Invalid");

  //     // if (gps.altitude.isValid()) {
  //     //   Serial.print("Altitude   = ");
  //     //   Serial.print(gps.altitude.meters());
  //     //   Serial.println(" meters");
  //     // }
  //     // else
  //     //   Serial.println("Altitude Invalid");

  //     // if (gps.speed.isValid()) {
  //     //   Serial.print("Speed      = ");
  //     //   Serial.print(gps.speed.kmph());
  //     //   Serial.println(" kmph");
  //     // }
  //     // else
  //     //   Serial.println("Speed Invalid");

  //     // if (gps.time.isValid()) {
  //     //   Serial.print("Time (GMT) : ");
  //     //   if(gps.time.hour() < 10)     Serial.print("0");
  //     //   Serial.print(gps.time.hour());
  //     //   Serial.print(":");
  //     //   if(gps.time.minute() < 10)   Serial.print("0");
  //     //   Serial.print(gps.time.minute());
  //     //   Serial.print(":");
  //     //   if(gps.time.second() < 10)   Serial.print("0");
  //     //   Serial.println(gps.time.second());
  //     // }
  //     // else
  //     //   Serial.println("Time Invalid");

  //     // if (gps.date.isValid()) {
  //     //   Serial.print("Date       : ");
  //     //   if(gps.date.day() < 10)      Serial.print("0");
  //     //   Serial.print(gps.date.day());
  //     //   Serial.print("/");
  //     //   if(gps.date.month() < 10)    Serial.print("0");
  //     //   Serial.print(gps.date.month());
  //     //   Serial.print("/");
  //     //   Serial.println(gps.date.year());
  //     // }
  //     // else
  //     //   Serial.println("Date Invalid");

  //     // if (gps.satellites.isValid()) {
  //     //   Serial.print("Satellites = ");
  //     //   Serial.println(gps.satellites.value());
  //     // }
  //     // else
  //     //   Serial.println("Satellites Invalid");

  //     digitalWrite (LED_PIN, LOW);	// turn off the LED
  //   }
  // }
}

// void smartDelay(unsigned long ms){
//   unsigned long start = millis();
//   do 
//   {
//     while (SerialGPS.available())
//       gps.encode(SerialGPS.read());
//   } while (millis() - start < ms);
// }

// static void printDateTime(TinyGPSDate &d){
//   if (!d.isValid()){
//     Serial.print(F("********** "));
//   }else{
//     char sz[32];
//     sprintf(sz, "%02d/%02d/%02d", d.day(),  d.month(), d.year());
//     Serial.print("\nTimeGPS:");
//     Serial.println(sz);
//   }
// }