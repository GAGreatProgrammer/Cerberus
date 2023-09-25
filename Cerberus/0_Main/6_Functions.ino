void systemInfo() {
  String Info = "Cerberus IoT System";
  client.publish(System_Info_Topic, Info.c_str());
}


void systemStatus() {
  String Status = "Cerberus Connected";
  client.publish(System_Status_Topic, Status.c_str());
  client.publish(System_Error_Topic, "No Error");
}


void systemIP() {
  client.publish(System_IP_Topic, IP.c_str());
}


void systemMAC() {
  client.publish(System_MAC_Topic, MAC.c_str());
}


void systemError(String _error) {
  client.publish(System_Error_Topic, _error.c_str());
}


void WifiStatus(){
  if (millis() - lastMillisWiFi >= 30000) {
    switch (WiFi.status()) {
      case WL_NO_SSID_AVAIL:
        Serial.println("Configured SSID cannot be reached");
        break;
      case WL_CONNECT_FAILED:
        Serial.println("Connection failed");
        break;
    }
    lastMillisWiFi = millis();
  }
}


void MQTTStatus(){
    if (millis() - lastMillisMQTT >= 30000) {
    switch (client.connected()) {
      case 0:
        initMQTT();
        break;
    }
    lastMillisMQTT = millis();
  }
}


void pirStatus() {
  if (millis() - lastMillisPirSensor > 1000) {
    lastMillisPirSensor = millis();

    if (PirSecurityState == true) {

      if (digitalRead(PIR_SENSOR) == HIGH) {

        PirSensorState = true;

        client.publish(PIR_Sensor_Topic, "Motion Detected");
        EasyBuzzer.beep(2700, 150, 50, 3, 150, 1);
      }

      else if (digitalRead(PIR_SENSOR) == LOW) {

        PirSensorState = false;

        client.publish(PIR_Sensor_Topic, "No Motion");
        EasyBuzzer.stopBeep();
      }
    }

    else if (PirSecurityState == false) {
      client.publish(PIR_Sensor_Topic, "Security OFF");

    }
  }
}



void dhtValue() {
  if (millis() - lastMillisHumidity >= 5000) {
    lastMillisHumidity = millis();

    float h = dht.readHumidity();

    float t = dht.readTemperature() - Temperature_Offset;

    if (isnan(h) || isnan(t)) {
      systemError("DHT11 Error");
      return;
    }

    float hic = dht.computeHeatIndex(t, h, false);

    client.publish(Humidity_Sensor_Humidity_Topic, String(h).c_str());
    client.publish(Humidity_Sensor_Temperature_Topic, String(t).c_str());
    client.publish(Humidity_Sensor_HeatIndex_Topic, String(hic).c_str());

    if (t >= MaxTemperature) {
      digitalWrite(LED_WARNING, HIGH);
      HighTemperature = true;

    }
    else {
      digitalWrite(LED_WARNING, LOW);
      HighTemperature = false;

      EasyBuzzer.stopBeep();
    }
  }

}


void gasAnalog() {
  if (millis() - lastMillisGasAnalog >= 3000) {
    lastMillisGasAnalog = millis();

    int analogSensor = analogRead(GAS_SENSOR_ANALOG);

    client.publish(Gas_Sensor_Analog_Topic, String(analogSensor).c_str());

    if (analogSensor > GasMaxAllowedValue)
    {
      Gas_Alarm = true;

    }
    else if (analogSensor < GasMaxAllowedValue)
    {
      Gas_Alarm = false;

      EasyBuzzer.stopBeep();

      digitalWrite(LED_ALERT, LOW);
    }
  }
}


void gasDigital() {
  if (millis() - lastMillisGasDigital >= 3000) {
    lastMillisGasDigital = millis();

    int state = digitalRead(GAS_SENSOR_DIGITAL);

    if (state == 0) {
      client.publish(Gas_Sensor_Digital_Topic, "Gas Alarm");

      Gas_Alarm = true;

    }
    else if (state == 1) {
      client.publish(Gas_Sensor_Digital_Topic, "No Gas");

      Gas_Alarm = false;

      EasyBuzzer.stopBeep();

      digitalWrite(LED_ALERT, LOW);
    }
  }
}


void SelfTest_Press() {
  if (SelfTest_Button.isPressed()) {

    SelfTest_State == true;

    digitalWrite(LED_ALERT, HIGH);
    digitalWrite(LED_WHITE, HIGH);
    digitalWrite(LED_WARNING, HIGH);
  }

  else if (SelfTest_Button.wasReleased()) {

    SelfTest_State == false;

    digitalWrite(LED_ALERT, LOW);
    digitalWrite(LED_WHITE, LOW);
    digitalWrite(LED_WARNING, LOW);
  }
}


void PIRButtonActivate() {
  if (Security_Button.wasPressed()) {

    client.publish(PIR_Security_Topic, "ON");
    success();
    PirSecurityState = true;
  }
}
