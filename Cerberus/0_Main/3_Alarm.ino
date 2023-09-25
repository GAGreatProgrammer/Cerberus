void success() {
  EasyBuzzer.beep(2700, 100, 50, 2, 150, 1);
}


void error() {
  EasyBuzzer.beep(350, 100, 50, 3, 150, 1);
}


void AlarmSignal() {
  if (Alarm == true) {
    if (millis() - lastMillisBuzzer >= 500) {
      lastMillisBuzzer = millis();
      EasyBuzzer.beep(2700, 300, 300, 1, 150, 1);
    }

    else if (Alarm == false) {
      EasyBuzzer.stopBeep();
    }
  }
}


void MotionDetected_Blink() {
  if (PirSecurityState == true && PirSensorState == true) {
    if (millis() - lastMillisMotionLed >= 50) {
      lastMillisMotionLed = millis();
      digitalWrite(LED_WHITE, !digitalRead(LED_WHITE));
    }
  }

  else {
    digitalWrite(LED_WHITE, LOW);
    return;
  }
}


void MotionDetected_Beeps() {
  if (PirSecurityState == true && PirSensorState == true) {
    if (millis() - lastMillisBuzzer >= 2000) {
      lastMillisBuzzer = millis();
      EasyBuzzer.beep(2700, 150, 50, 3, 150, 1);
    }
  }
}


void High_Tempetarure_Beeps() {
  if (HighTemperature == true) {
    if (millis() - lastMillisBuzzer >= 2000) {
      lastMillisBuzzer = millis();
      EasyBuzzer.beep(2700, 200, 100, 2, 150, 1);
    }
  }
}


void High_Tempetarure_Led() {
  if (HighTemperature == true) {
    if (millis() - lastMillisWarningLed >= 300) {
      lastMillisWarningLed = millis();
      digitalWrite(LED_WARNING, !digitalRead(LED_WARNING));
    }
  }
}


void Gas_Alarm_Beeps() {
  if (Gas_Alarm == true) {
    if (millis() - lastMillisBuzzer >= 500) {
      lastMillisBuzzer = millis();
      EasyBuzzer.beep(2700, 200, 100, 1, 150, 1);
    }
  }
}


void Gas_Alarm_Led() {
  if (Gas_Alarm == true) {
    if (millis() - lastMillisAlertLed >= 300) {
      lastMillisAlertLed = millis();
      digitalWrite(LED_ALERT, !digitalRead(LED_ALERT));
    }
  }
}
