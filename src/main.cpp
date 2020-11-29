#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

/*
const char* ssid     = "octoblo";
const char* password = "Bluish-Octavo-82";
*/
const char* ssid     = "kali";
const char* password = "hoiduuu<3";

//const char* mqtt_server = "mqtt://3d8f57f8:67f1ba13358e9b30@broker.shiftr.io";
//const char* mqtt_server = "192.168.1.25";
const char* mqtt_server = "172.20.10.3";

//const char *ID = "octoswitch01";
const char *ID = "octoswitch02";
const char *BLOWERS_TOPIC = "octoblo/blowers";

const int BLO1 = 15;
const int BLO2 = 2;
const int BLO3 = 4;
const int BLO4 = 5;

const int BLO5 = 26;
const int BLO6 = 25;
const int BLO7 = 33;
const int BLO8 = 32;

bool BLO1_STATE = false;
bool BLO2_STATE = false;
bool BLO3_STATE = false;
bool BLO4_STATE = false;

bool BLO5_STATE = false;
bool BLO6_STATE = false;
bool BLO7_STATE = false;
bool BLO8_STATE = false;

WiFiClient wclient;
PubSubClient client(wclient);

/*
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE(50)
char msg[MSG_ BUFFER_SIZE];
int value = 0;
*/

void callback(char* topic, byte* payload, unsigned int length) {
  String response;

  for (int i = 0; i < length; i++) {
    response += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(response);

  if(response == "blo1")
  {
    BLO1_STATE = !BLO1_STATE;
    client.publish(BLOWERS_TOPIC, "blo1_switched");
    Serial.println("blo1_switched");
    Serial.println(BLO1_STATE);
  }

  if(response == "blo2")
  {
    BLO2_STATE = !BLO2_STATE;
    client.publish(BLOWERS_TOPIC, "blo2_switched");
    Serial.println("blo2_switched");
    Serial.println(BLO2_STATE);
  }

  if(response == "blo3")
  {
    BLO3_STATE = !BLO3_STATE;
    client.publish(BLOWERS_TOPIC, "blo3_switched");
    Serial.println("blo3_switched");
    Serial.println(BLO3_STATE);
  }

  if(response == "blo4")
  {
    BLO4_STATE = !BLO4_STATE;
    client.publish(BLOWERS_TOPIC, "blo4_switched");
    Serial.println("blo4_switched");
    Serial.println(BLO4_STATE);
  }

  if(response == "blo5")
  {
    BLO5_STATE = !BLO5_STATE;
    client.publish(BLOWERS_TOPIC, "blo5_switched");
    Serial.println("blo5_switched");
    Serial.println(BLO5_STATE);
  }

  if(response == "blo6")
  {
    BLO6_STATE = !BLO6_STATE;
    client.publish(BLOWERS_TOPIC, "blo6_switched");
    Serial.println("blo6_switched");
    Serial.println(BLO6_STATE);
  }

  if(response == "blo7")
  {
    BLO7_STATE = !BLO7_STATE;
    client.publish(BLOWERS_TOPIC, "blo7_switched");
    Serial.println("blo7_switched");
    Serial.println(BLO7_STATE);
  }

  if(response == "blo8")
  {
    BLO8_STATE = !BLO8_STATE;
    client.publish(BLOWERS_TOPIC, "blo8_switched");
    Serial.println("blo8_switched");
    Serial.println(BLO8_STATE);
  }
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = ID;
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an annou2cement...
      client.publish("/octoblo", "switch01 connected");
      // ... and resubscribe
      client.subscribe("/octoblo/blowers");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
    pinMode(BLO1, OUTPUT);
    pinMode(BLO2, OUTPUT);
    pinMode(BLO3, OUTPUT);
    pinMode(BLO4, OUTPUT);

    pinMode(BLO5, OUTPUT);
    pinMode(BLO6, OUTPUT);
    pinMode(BLO7, OUTPUT);
    pinMode(BLO8, OUTPUT);

    digitalWrite(BLO1, HIGH);
    digitalWrite(BLO2, HIGH);
    digitalWrite(BLO3, HIGH);
    digitalWrite(BLO4, HIGH);

    digitalWrite(BLO5, HIGH);
    digitalWrite(BLO6, HIGH);
    digitalWrite(BLO7, HIGH);
    digitalWrite(BLO8, HIGH);

    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

		randomSeed(micros());
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    client.subscribe("/octoblo/blowers");
}

int value = 0;

void loop() {

  ++value;

   if (!client.connected())  // Reconnect if connection is lost
   {
     reconnect();
   }
     client.loop();
/*
  digitalWrite(BLO1, LOW);
  delay(1000);
  digitalWrite(BLO1, HIGH);
  delay(1000);
*/

  // Control Blowers
  if (BLO1_STATE == true) {
    digitalWrite(BLO1, LOW);
  } else {
    digitalWrite(BLO1, HIGH);
  }

  if (BLO2_STATE == true) {
    digitalWrite(BLO2, LOW);
  } else {
    digitalWrite(BLO2, HIGH);
  }

  if (BLO3_STATE == true) {
    digitalWrite(BLO3, LOW);
  } else {
    digitalWrite(BLO3, HIGH);
  }

  if (BLO4_STATE == true) {
    digitalWrite(BLO4, LOW);
  } else {
    digitalWrite(BLO4, HIGH);
  }

  if (BLO5_STATE == true) {
    digitalWrite(BLO5, LOW);
  } else {
    digitalWrite(BLO5, HIGH);
  }

  if (BLO6_STATE == true) {
    digitalWrite(BLO6, LOW);
  } else {
    digitalWrite(BLO6, HIGH);
  }

  if (BLO7_STATE == true) {
    digitalWrite(BLO7, LOW);
  } else {
    digitalWrite(BLO7, HIGH);
  }

  if (BLO8_STATE == true) {
    digitalWrite(BLO8, LOW);
  } else {
    digitalWrite(BLO8, HIGH);
  }

}
