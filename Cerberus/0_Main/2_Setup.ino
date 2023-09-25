void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(PIR_SENSOR, INPUT);
  pinMode(GAS_SENSOR_DIGITAL, INPUT);
  pinMode(GAS_SENSOR_ANALOG, INPUT);
  pinMode(HUMIDITY_SENSOR, INPUT);
  pinMode(SELF_TEST_BUTTON, INPUT);
  pinMode(SECURITY_BUTTON, INPUT);
  pinMode(LED_ALERT, OUTPUT);
  pinMode(LED_WARNING, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);

  EasyBuzzer.setPin(BUZZER);

  Security_Button.begin();
  SelfTest_Button.begin();

  dht.begin();

  Serial.begin(115200);

  initWiFi();
  initMQTT();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "Cerberus");
  });

  AsyncElegantOTA.begin(&server);
  server.begin();
}
