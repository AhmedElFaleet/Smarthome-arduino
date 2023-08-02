#define REMOTEXY_MODE__ESP8266_HARDSERIAL_CLOUD

#include <RemoteXY.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTTYPE DHT11
#define DHTPIN A0
#define trigPin 7
#define echoPin 6
#define buzzerPin 13
const int dryRunPin = 12;
DHT dht(DHTPIN, DHTTYPE);

// RemoteXY connection settings
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "AHMED"
#define REMOTEXY_WIFI_PASSWORD "10101010**"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "e35111c2515f80f22f5019c9655c1a3f"


// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =  // 355 bytes
{ 255, 7, 0, 34, 0, 92, 1, 16, 124, 1, 2, 1, 35, 14, 14, 6, 94, 26, 31, 31,
  79, 78, 0, 79, 70, 70, 0, 129, 0, 9, 14, 20, 6, 24, 82, 111, 111, 109, 49, 0,
  130, 3, 250, 49, 73, 26, 31, 129, 0, 2, 52, 30, 4, 24, 84, 101, 109, 112, 101, 114,
  97, 116, 117, 114, 101, 32, 40, 67, 41, 0, 129, 0, 6, 59, 23, 4, 24, 72, 117, 109,
  105, 100, 105, 116, 121, 32, 40, 37, 41, 0, 67, 4, 36, 52, 20, 5, 1, 26, 11, 67,
  4, 36, 59, 20, 5, 2, 26, 11, 67, 4, 36, 77, 21, 6, 163, 26, 11, 129, 0, 58,
  78, 3, 4, 8, 37, 0, 2, 1, 35, 21, 14, 6, 94, 26, 31, 31, 79, 78, 0, 79,
  70, 70, 0, 129, 0, 9, 21, 20, 6, 24, 82, 111, 111, 109, 50, 0, 129, 0, 9, 43,
  20, 6, 24, 82, 111, 111, 109, 53, 0, 129, 0, 9, 28, 20, 6, 24, 82, 111, 111, 109,
  51, 0, 129, 0, 9, 35, 20, 6, 24, 82, 111, 111, 109, 52, 0, 130, 0, 255, 255, 64,
  12, 111, 129, 0, 17, 3, 30, 7, 8, 77, 121, 32, 72, 111, 109, 101, 0, 2, 1, 36,
  67, 14, 6, 94, 26, 31, 31, 79, 78, 0, 79, 70, 70, 0, 2, 1, 37, 86, 14, 6,
  94, 26, 31, 31, 79, 78, 0, 79, 70, 70, 0, 2, 1, 35, 42, 14, 6, 94, 26, 31,
  31, 79, 78, 0, 79, 70, 70, 0, 2, 1, 35, 35, 14, 6, 94, 26, 31, 31, 79, 78,
  0, 79, 70, 70, 0, 2, 1, 35, 28, 14, 6, 94, 26, 31, 31, 79, 78, 0, 79, 70,
  70, 0, 129, 0, 12, 67, 10, 6, 24, 70, 97, 110, 0, 129, 0, 10, 78, 22, 4, 24,
  87, 97, 116, 101, 114, 32, 76, 101, 118, 101, 108, 32, 0, 129, 0, 16, 87, 11, 4, 24,
  80, 117, 109, 112, 32, 0, 70, 16, 57, 52, 5, 5, 26, 37, 8
};

// this structure defines all the variables and events of your control interface
struct {

  // input variables
  uint8_t switch_1;  // =1 if switch ON and =0 if OFF
  uint8_t switch_2;  // =1 if switch ON and =0 if OFF
  uint8_t switch_6;  // =1 if switch ON and =0 if OFF
  uint8_t switch_7;  // =1 if switch ON and =0 if OFF
  uint8_t switch_5;  // =1 if switch ON and =0 if OFF
  uint8_t switch_4;  // =1 if switch ON and =0 if OFF
  uint8_t switch_3;  // =1 if switch ON and =0 if OFF

  // output variables
  char text_temp[11];      // string UTF8 end zero
  char text_humidity[11];  // string UTF8 end zero
  char text_ultra[11];     // string UTF8 end zero

  // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

#define PIN_SWITCH_1 4
#define PIN_SWITCH_2 3
#define PIN_SWITCH_6 9
#define PIN_SWITCH_7 10
#define PIN_SWITCH_5 8
#define PIN_SWITCH_4 2
#define PIN_SWITCH_3 5


void setup() {
  RemoteXY_Init();

  pinMode(PIN_SWITCH_1, OUTPUT);
  pinMode(PIN_SWITCH_2, OUTPUT);
  pinMode(PIN_SWITCH_6, OUTPUT);
  pinMode(PIN_SWITCH_7, OUTPUT);
  pinMode(PIN_SWITCH_5, OUTPUT);
  pinMode(PIN_SWITCH_4, OUTPUT);
  pinMode(PIN_SWITCH_3, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(dryRunPin, INPUT);
  dht.begin();
}

void loop() {
  RemoteXY_Handler();

  digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1 == 0) ? LOW : HIGH);
  digitalWrite(PIN_SWITCH_2, (RemoteXY.switch_2 == 0) ? LOW : HIGH);
  digitalWrite(PIN_SWITCH_6, (RemoteXY.switch_6 == 0) ? LOW : HIGH);
  digitalWrite(PIN_SWITCH_7, (RemoteXY.switch_7 == 0) ? LOW : HIGH);
  digitalWrite(PIN_SWITCH_5, (RemoteXY.switch_5 == 0) ? LOW : HIGH);
  digitalWrite(PIN_SWITCH_4, (RemoteXY.switch_4 == 0) ? LOW : HIGH);
  digitalWrite(PIN_SWITCH_3, (RemoteXY.switch_3 == 0) ? LOW : HIGH);

  long duration ,cm;
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  dtostrf(temperature, 0, 1, RemoteXY.text_temp);
  dtostrf(humidity, 0, 1, RemoteXY.text_humidity);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  cm = (duration / 2) / 29.1;

  if (digitalRead(dryRunPin) == 0) {
    if (cm >= 17) {
      dtostrf(0, 0, 1, RemoteXY.text_ultra);
      digitalWrite(10, HIGH);
      RemoteXY.switch_7 = 1;
    }
    else if (cm >= 16) {
      dtostrf(0, 0, 1, RemoteXY.text_ultra);
      digitalWrite(10, HIGH);
      RemoteXY.switch_7 = 1;
    }
    else if (cm >= 15) {
      dtostrf(10, 0, 1, RemoteXY.text_ultra);
      digitalWrite(10, HIGH);
      RemoteXY.switch_7 = 1;
    }
    else if (cm >= 14) {
      dtostrf(20, 0, 1, RemoteXY.text_ultra);
      digitalWrite(10, HIGH);
      RemoteXY.switch_7 = 1;
    }
    else if (cm >= 13) {
      dtostrf(30, 0, 1, RemoteXY.text_ultra);
      digitalWrite(10, HIGH);
      RemoteXY.switch_7 = 1;
    }
    else if (cm >= 12) {
      dtostrf(40, 0, 1, RemoteXY.text_ultra);
      digitalWrite(10, HIGH);
      RemoteXY.switch_7 = 1;
    }
    else if (cm >= 11) {
      dtostrf(50, 0, 1, RemoteXY.text_ultra);
      digitalWrite(10, HIGH);
      RemoteXY.switch_7 = 1;
    }
    else if (cm >= 10) {
      dtostrf(60, 0, 1, RemoteXY.text_ultra);
      
    }
    else if (cm >= 9) {
      dtostrf(70, 0, 1, RemoteXY.text_ultra);
     
    }
    else if (cm >= 8) {
      dtostrf(80, 0, 1, RemoteXY.text_ultra);
     
    }
    else if (cm >= 7) {
      dtostrf(90, 0, 1, RemoteXY.text_ultra);
      
    }
    else if (cm >= 5) {
      dtostrf(100, 0, 1, RemoteXY.text_ultra);
      digitalWrite(10, LOW);
      RemoteXY.switch_7 = 0;
    }
    else {
      digitalWrite(10, LOW);
      RemoteXY.switch_7 = 0;
    }
  }
  else {
    digitalWrite(10, LOW);
    RemoteXY.switch_7 = 0;
  }



  if (temperature >= 30) {
    digitalWrite(buzzerPin, HIGH);
    RemoteXY.switch_6 = 1;
    delay(1000);
    digitalWrite(buzzerPin, LOW);
    delay(2000);
  } else {
    RemoteXY.switch_6 = 0;
    digitalWrite(buzzerPin, LOW);
  }}
