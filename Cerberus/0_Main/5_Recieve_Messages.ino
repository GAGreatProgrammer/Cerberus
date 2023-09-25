void Security(char *_topic, String _message) {
  if (strcmp(_topic, PIR_Security_Topic) == 0) {
    if (_message == "ON") {
      PirSecurityState = true;
    }

    else if (_message == "OFF") {
      PirSecurityState = false;
    }
  }
}


void AlarmStatus(char *_topic, String _message) {
  if (strcmp(_topic, Buzzer_State_Topic) == 0) {
    if (_message == "ON") {
      client.publish(Buzzer_Status_Topic, "Alarm ON");
      Alarm = true;
    }

    else if (_message == "OFF") {
      client.publish(Buzzer_Status_Topic, "Alarm OFF");
      Alarm = false;
      EasyBuzzer.stopBeep();
    }
  }
}
