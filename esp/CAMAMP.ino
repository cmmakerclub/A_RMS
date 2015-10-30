#include <Wire.h>
#include <WiFiConnector.h>
#include <MqttConnector.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

MqttConnector *mqtt;
WiFiConnector *wifi;

int ReadAmp = 0;

#define MQTT_PORT        1883
#define PUBLISH_EVERY    3*1000 // every 15 seconds

#define MQTT_HOST "gb.netpie.io"
#define MQTT_USERNAME "BQXB0B4zvtJPkCF"
#define MQTT_PASSWORD "ecFhTzYzKI6KVjz93Nm3a9DkUdI="
#define MQTT_CLIENT_ID "CpjOpeR8E0Y2kJOm"
#define MQTT_PREFIX "/CAMAMP/gearname"

/* SENSOR INFO */
#define DEVICE_NAME "PAO-CAMAMP"
#define AUTHOR      "COMPILER EXE"
#define BOARD       "ESP-ROOM"

/* WIFI INFO */
#define WIFI_SSID        ""
#define WIFI_PASSPHARSE  ""

#include "init_wifi.h"
#include "_receive.h"
#include "_publish.h"

void init_hardware()
{
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("BEGIN");  
}

void setup()
{
  init_hardware();
  init_wifi();
  init_mqtt();
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(16, OUTPUT);
  delay(1000);
  digitalWrite(13, HIGH);
  digitalWrite(16, LOW);
}

void loop()
{
  Wire.requestFrom(1, 2);
  ReadAmp = Wire.read() << 8 | Wire.read();
  ReadAmp = ReadAmp / 10;
  Serial.print(ReadAmp);
  mqtt->loop(wifi);
}
