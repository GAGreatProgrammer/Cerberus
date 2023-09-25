// WiFi
const char *ssid = "";
const char *password = "";

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int   mqtt_port = 1883;

byte willQoS = 0;
const char* willTopic =   "ApKeqBgnZbylGec/Main/SYS/Status";
const char* willMessage = "Cerberus Disconnected";
boolean willRetain = false;

const char *MainTopicID = "ApKeqBgnZbylGec";

const char *System_Info_Topic =   "ApKeqBgnZbylGec/Main/SYS/Info";
const char *System_Status_Topic = "ApKeqBgnZbylGec/Main/SYS/Status";
const char *System_IP_Topic =     "ApKeqBgnZbylGec/Main/SYS/IP";
const char *System_MAC_Topic =    "ApKeqBgnZbylGec/Main/SYS/MAC";
const char *System_Error_Topic =  "ApKeqBgnZbylGec/Main/SYS/Error";

const char *PIR_Sensor_Topic =     "ApKeqBgnZbylGec/Main/Sensors/PIR";
const char *PIR_Security_Topic =   "ApKeqBgnZbylGec/Main/Sensors/PIR/Security";

const char *Gas_Sensor_Digital_Topic = "ApKeqBgnZbylGec/Main/Sensors/Gas/Digital";
const char *Gas_Sensor_Analog_Topic =  "ApKeqBgnZbylGec/Main/Sensors/Gas/Analog";

const char *Humidity_Sensor_Humidity_Topic =    "ApKeqBgnZbylGec/Main/Sensors/Humidity/Humidity";
const char *Humidity_Sensor_Temperature_Topic = "ApKeqBgnZbylGec/Main/Sensors/Humidity/Temperature";
const char *Humidity_Sensor_HeatIndex_Topic =   "ApKeqBgnZbylGec/Main/Sensors/Humidity/HeatIndex";

const char *Buzzer_Status_Topic = "ApKeqBgnZbylGec/Main/Buzzer/Status";
const char *Buzzer_State_Topic =  "ApKeqBgnZbylGec/Main/Buzzer/State";

String MAC;
String IP;


float Temperature_Offset = 0;
float Humidity_Offset = 0;
bool HighTemperature = false;


bool Gas_Alarm = false;


bool PirSensorState = LOW;
bool PirSecurityState = false;


bool BacklightOn = false;


bool Alarm = false;


bool SelfTest_State = false;


int GasMaxAllowedValue = 120;

float MaxTemperature = 45;

AsyncWebServer server(80);

WiFiClient espClient;

PubSubClient client(espClient);

DHT dht(HUMIDITY_SENSOR, DHTTYPE);


void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  MAC = WiFi.macAddress();
  IP = WiFi.localIP().toString();

  delay(100);
  Serial.println("Connected to the WiFi Network!");

  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
}


void initMQTT() {
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

  while (!client.connected()) {
    String client_id = "Cerberus-";

    client_id += String(WiFi.macAddress());

    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password, willTopic, willQoS, willRetain, willMessage)) {
      Serial.println("Broker connected!");
      
      Initialize = true;

      tone(BUZZER, 2700, 1000);

      delay(1000);

      client.subscribe(System_Info_Topic);
      client.subscribe(System_Status_Topic);
      client.subscribe(System_IP_Topic);
      client.subscribe(System_MAC_Topic);
      client.subscribe(System_Error_Topic);

      client.subscribe(PIR_Sensor_Topic);
      client.subscribe(PIR_Security_Topic);

      client.subscribe(Gas_Sensor_Digital_Topic);
      client.subscribe(Gas_Sensor_Analog_Topic);

      client.subscribe(Humidity_Sensor_Humidity_Topic);
      client.subscribe(Humidity_Sensor_Temperature_Topic);
      client.subscribe(Humidity_Sensor_HeatIndex_Topic);

      client.subscribe(Buzzer_Status_Topic);
      client.subscribe(Buzzer_State_Topic);

    }

    else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      return;
    }
  }

  systemInfo();
  systemStatus();
  systemIP();
  systemMAC();
}
