#include <SoftwareSerial.h>      // Include software serial library
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "VIETTEL";
const char* password = "lamgicomatkhau";

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.1.3:1880/update-sensor";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

#define LED_PIN 2
#define WIFI_TIMEOUT_MS 10000

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  unsigned long startAttemptTime = millis();
  int i = 0;

  Serial.print("Connecting to WiFi");
  while ((WiFi.status() != WL_CONNECTED) && ((millis() - startAttemptTime) < WIFI_TIMEOUT_MS)) {
    delay(1000);
    if (i%2 == 0) {
      digitalWrite (LED_PIN, HIGH);
    }
    else {
      digitalWrite (LED_PIN, LOW);
    }
    Serial.print(i++);
    Serial.println("s");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed!");
  }
  else {
    Serial.println("Connected!");
    Serial.println(WiFi.localIP());
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  connectToWiFi();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName + "?temperature=24.37";
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      Serial.print(serverPath);
      Serial.print(serverPath.c_str());
      
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
