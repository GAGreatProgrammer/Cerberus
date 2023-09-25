#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <EasyBuzzer.h>
#include <JC_Button.h>



#define LED_ALERT D0              
#define PIR_SENSOR D1             
#define GAS_SENSOR_DIGITAL D2     
#define LED_WHITE D3              
#define LED_WARNING D4            
#define HUMIDITY_SENSOR D5        
#define BUZZER D6                 
#define SECURITY_BUTTON D7        
#define SELF_TEST_BUTTON D8       
#define GAS_SENSOR_ANALOG A0      


#define DHTTYPE DHT11


Button Security_Button(SECURITY_BUTTON, 25, false, false);
Button SelfTest_Button(SELF_TEST_BUTTON, 25, false, false);


bool Initialize = false;

unsigned long lastMillisWiFi = 0;
unsigned long lastMillisMQTT = 0;

unsigned long lastMillisBuzzer = 0;

unsigned long lastMillisPirSensor = 0;

unsigned long lastMillisGasDigital = 0;
unsigned long lastMillisGasAnalog = 0;

unsigned long lastMillisHumidity = 0;

unsigned long lastMillisSelfTestButton = 0;
unsigned long lastMillisSystemButton = 0;

unsigned long lastMillisMotionLed = 0;
unsigned long lastMillisAlertLed = 0;
unsigned long lastMillisWarningLed = 0;

unsigned long lastMillisSelfTest = 0;
