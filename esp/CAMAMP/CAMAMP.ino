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
#define PUBLISH_EVERY    1*1000 // every 15 seconds

#define MQTT_HOST "gb.netpie.io"
#define MQTT_USERNAME "GaBH7sxFDUEX0hl"
#define MQTT_PASSWORD "KAIhFrxuRh6zPubEX8FrgK2HfGc="
#define MQTT_CLIENT_ID "rWUVLB3SFxOVv9fW"
#define MQTT_PREFIX "/NatWeerawan/gearname"

/* SENSOR INFO */
#define DEVICE_NAME "CLAMP.AMP"
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

  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(16, OUTPUT);
  delay(1000);
  digitalWrite(13, HIGH);
  digitalWrite(16, LOW);
  Wire.begin();
}

void setup()
{
  init_hardware();
  init_wifi();
  init_mqtt();
}

void loop()
{
  mqtt->loop(wifi);
}
