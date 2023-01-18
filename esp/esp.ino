#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
SoftwareSerial serial(25,26);


const char* ssid = "Embedded_Web";
const char* password = "123456789";
const char* mqtt_server = "broker.hivemq.com";
String clientID = "SIS_IoT-"; //SIS_IoT-";
int port = 1883;
const char* topic_Subscribe     = "SIS/fromServer/cmd";
const char* topic_Publish_msg0  = "SIS/toServer/Connection";
const char* topic_Publish_msg1  = "SIS/toServer/soilMoisureSensor";
const char* topic_Publish_msg2  = "SIS/toServer/waterLevelSensor";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// for incoming msg for esp
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    // String clientId = "SIS_V4";
    clientID += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientID.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(topic_Publish_msg0, "Connect"); // IN menas => In to server
      // ... and resubscribe
      client.subscribe(topic_Subscribe);
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
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, port);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (Serial.available()) {
        int x=Serial.read();
        //Serial.write(x);

      Serial.println(x);
      //Serial.print('\n');

      String soil_read = String(x);
      char buffer[soil_read.length() + 1];
      soil_read.toCharArray(buffer, soil_read.length() + 1);
      Serial.print("Publish message soil : ");
      Serial.println(soil_read);
      client.publish(topic_Publish_msg1, buffer);

      // String water_read = String(random(255));
      // char buffer2[water_read.length() + 1];
      // water_read.toCharArray(buffer2, water_read.length() + 1);
      // Serial.print("    |   Publish message water : ");
      // Serial.println(water_read);
      // client.publish(topic_Publish_msg2, buffer2);
  }


  

  delay(2000);
}
