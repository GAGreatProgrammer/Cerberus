void loop() {
  
  WifiStatus();
  MQTTStatus();

  client.loop();

  EasyBuzzer.update();

  Security_Button.read();
  SelfTest_Button.read();


  pirStatus();
  dhtValue();
  gasAnalog();
  gasDigital();


  MotionDetected_Blink();

  High_Tempetarure_Led();
  High_Tempetarure_Beeps();

  Gas_Alarm_Led();
  Gas_Alarm_Beeps();

  AlarmSignal();

  SelfTest_Press();
  PIRButtonActivate();
}
