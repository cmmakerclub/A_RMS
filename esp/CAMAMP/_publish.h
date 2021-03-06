MqttConnector::prepare_data_hook_t on_prepare_data =
[&](JsonObject * root) -> void {

  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);
  JsonObject& data = (*root)["d"];
  JsonObject& info = (*root)["info"];
  data["myName"] = DEVICE_NAME;
  info["author"] = AUTHOR;
  info["board"]  = BOARD;
  Wire.requestFrom(1, 2);
  ReadAmp = Wire.read() << 8 | Wire.read();
  ReadAmp = ReadAmp / 10.0;
  Serial.print(ReadAmp);

  data["ReadAmp"] = ReadAmp;
  //  data["temp"] = ReadAmp;
  //  delay(50);
  //  ReadAmp = Wire.read() << 8 | Wire.read();
  //  ReadAmp = ReadAmp;
  Serial.print(ReadAmp);
};

// MQTT INITIALIZER
void init_mqtt()
{
  mqtt = new MqttConnector(MQTT_HOST, MQTT_PORT);
  mqtt->prepare_configuration([&](MqttConnector::Config * config) -> void {
    config->clientId  = String(MQTT_CLIENT_ID);
    config->channelPrefix = String(MQTT_PREFIX);
    config->enableLastWill = true;
    config->retainPublishMessage = true;
    config->publishOnly = true;

    config->username = String(MQTT_USERNAME);
    config->password = String(MQTT_PASSWORD);


    uint8_t mac[6];
    WiFi.macAddress(mac);

    // device id
    String macAddr;
    for (int i = 0; i < 6; ++i)
    {
      macAddr += String(mac[i], 16);
    }

    // FORMAT
    // d:quickstart:<type-id>:<device-id>
    // config->clientId += macAddr;

    //   config->topicPub  = String("/HelloChiangMaiMakerClub/gearname/") + config->clientId;


  });

  mqtt->after_prepare_configuration([&](MqttConnector::Config config) -> void {
    Serial.print(String("HOST: ") + config.mqttHost);
    Serial.println(String(" PORT: ") + config.mqttPort);
    Serial.println(String("__PUBLICATION TOPIC .. ") + config.topicPub);
    Serial.println(String("__SUBSCRIPTION TOPIC .. ") + config.topicPub);
    Serial.println(String("_PUBLISH ONLY ..") + config.publishOnly);
    Serial.println(String("_SUBSCRIBE ONLY ..") + config.subscribeOnly);
  });

  mqtt->prepare_data(on_prepare_data, PUBLISH_EVERY);
  mqtt->prepare_subscribe([&](MQTT::Subscribe * sub) -> void { });
  mqtt->after_prepare_data([&](JsonObject * root) -> void {
    //    root->remove("info");
    JsonObject& data = (*root)["d"];

    //    data.remove("version");
    //    data.remove("subscription");
  });

  // on_message_arrived located in _receive.h
  mqtt->on_message(on_message_arrived);

  mqtt->on_connecting([&](int count, bool * flag) {
    Serial.print("MQTT CONNECTING.. ");
    Serial.println(count);
  });

  mqtt->on_published([&](const MQTT::Publish & pub) -> void {
    Serial.print("PUBLISHED: ");
    Serial.println(pub.payload_string());
    digitalWrite(16, LOW);
  });

  mqtt->connect();
}
