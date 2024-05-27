#include <WiFi.h>
// #include <Firebase_ESP_Client.h>

// #include <MPU6050_tockn.h>
// #include <Wire.h>

#include <TinyGPS++.h>

const char* ssid = "VIETTEL";
const char* password = "lamgicomatkhau";
// #define API_KEY "AIzaSyA1MoE7DWMM637pVisxbkcuRPh-nWva0Tw"
// #define DATABASE_URL "https://iotgt-cbfc2-default-rtdb.asia-southeast1.firebasedatabase.app"

// #define RXD2 16
// #define TXD2 17


// FirebaseData fbdo;
// FirebaseAuth  auth;
// FirebaseConfig config;

// unsigned long sendDataPrevMillis = 0;
// bool signupok = false;

// HardwareSerial neogps(1);
// TinyGPSPlus gps;

// MPU6050 mpu6050(Wire);
// long timer = 0;

// void Taskmpu6050( void *params);
// void TaskGPS(void *params);

void setup() {
  // config.api_key = API_KEY;
  // config.database_url = DATABASE_URL;

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.print("Đang kết nối..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(WiFi.status());
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Kết nối thành công với mạng Wi-Fi");
  Serial.print("Địa chỉ IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  delay(1000);
}

  void loop() {}