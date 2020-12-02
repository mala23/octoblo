#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
#include <NewPing.h>

#define SONAR_NUM 1      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(12, 13, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
};

const char* ssid     = "octoblo";
const char* password = "Bluish-Octavo-82";
/*
const char* ssid     = "kali";
const char* password = "hoiduuu<3";
*/

//const char* mqtt_server = "mqtt://3d8f57f8:67f1ba13358e9b30@broker.shiftr.io";
//const char* mqtt_server = "192.168.1.25";
//const char* mqtt_server = "172.20.10.3";
const char* mqtt_server = "192.168.1.42";

const char *ID = "octoeye";
const char *EYE_TOPIC = "octoblo/eye";

bool EYE_STATE = false;

WiFiClient wclient;
PubSubClient client(wclient);

void callback(char* topic, byte* payload, unsigned int length) {
  String response;

  for (int i = 0; i < length; i++) {
    response += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(response);

  /*
  if(response == "blo1")
  {
    BLO1_STATE = !BLO1_STATE;
    client.publish(BLOWERS_TOPIC, "blo1_switched");
    Serial.println("blo1_switched");
    Serial.println(BLO1_STATE);
  }
  */
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
      client.publish("/octoblo/eye", "octoeye connected");
      // ... and resubscribe
      client.subscribe(EYE_TOPIC);
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
  Serial.begin(115200);
    //Connecting to a WiFi network

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
    client.subscribe("EYE_TOPIC");
}

int value = 0;

void loop() {

 ++value;

 if (!client.connected())  // Reconnect if connection is lost
 {
   reconnect();
 }
   client.loop();

  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    char dist = sonar[0].ping_cm();
    Serial.print(i);
    Serial.print("=");
    Serial.print(sonar[i].ping_cm());
    Serial.print("cm ");
    if (dist != 0) {
      client.publish("/octoblo/eye", "eye0_switched");
    }
  }

  Serial.println();

  /*
  //Control Eye
  if (BLO1_STATE == true) {
    digitalWrite(BLO1, LOW);
  } else {
    digitalWrite(BLO1, HIGH);
  }
  */

}
