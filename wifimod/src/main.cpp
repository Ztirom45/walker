/*
after: https://github.com/smistrydev/ESP32_MQTT_CLIENT/blob/master/src/main.cpp

LICENCE: GPL4
written by Ztirom45

TODO: reconnect
*/
#include "HardwareSerial.h"
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "password.h"

#define mqtt_port 1883
#define MQTT_TOPIC "test"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

//action when client recived a message
void callback(char* topic, byte *payload, unsigned int length) {
    Serial.print("-m");
    Serial.write(payload, length);
    Serial.println("-e");
}

void setup_wifi(){

  // Connecting to WiFi...
  Serial.print("WiFi connecting to ");
  Serial.print(SSID);
  Serial.setTimeout(500);// Set time out for 
  

  WiFi.begin(SSID, PASSWORD);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    Serial.print(WiFi.status());
  }
  Serial.println("");
  Serial.println("connected");
  Serial.println("IP4 addr: ");
  Serial.println(WiFi.localIP());
  randomSeed(micros());
}

//conecting to mqtt
void reconnect(){
  while(!client.connected()){
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32But-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      //Once connected, publish an announcement...
      client.publish(MQTT_TOPIC, "testing...");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  client.subscribe(MQTT_TOPIC);
}
void setup(){
  Serial.begin(115200); 
  pinMode(LED_BUILTIN, OUTPUT);
  
  setup_wifi();
  //setup mqtt
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
}


void loop(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
