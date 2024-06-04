
// include variables
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <Servo.h>

#include "MQTTConnector.h"
#include "Credentials.h"

#define WIFI_TIMEOUT 1000
#define LOOP_TIMEOUT 1000
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "MQTTConnector.h"
#include "Credentials.h"

#define motorPinRightDir  0//D2
#define motorPinRightSpeed 5//D1

// choose what pin the servo is connected to
const int servoPin = 2;
Servo myServo;
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

boolean mqttInitCompleted = false;
String clientId = "IoTPractice-" + String(ESP.getChipId());

/* Incoming data callback. */
void dataCallback(char* topic, byte* payload, unsigned int length)
{
  // variables for speed and diraction
    int speed = 1024;
  int dir = 0;
   
  char payloadStr[length + 1];
  memset(payloadStr, 0, length + 1);
  strncpy(payloadStr, (char*)payload, length);
  Serial.printf("Data    : dataCallback. Topic : [%s]\n", topic);
  Serial.printf("Data    : dataCallback. Payload : %s\n", payloadStr);

// functions that listen to what the monitor sais and then perfomes the wished command
  if (strcmp(payloadStr, "Driving...") == 0) {
    Serial.println("Hey"); // Send "Hey" through serial monitor
      digitalWrite(motorPinRightDir, dir);
      analogWrite(motorPinRightSpeed, speed);
    // Perform additional actions here if the payload is "Driving..."
  }
    if (strcmp(payloadStr, "Driving Backwards") == 0) {
    Serial.println("Bye Bye"); 
      digitalWrite(motorPinRightDir, 1);
      analogWrite(motorPinRightSpeed, speed);
  }
    if (strcmp(payloadStr, "Turning Right") == 0) {
    Serial.println("Right");
    myServo.write(0);
  }
    if (strcmp(payloadStr, "Turning left") == 0) {
    Serial.println("Left");
    myServo.write(180);
  }
      if (strcmp(payloadStr, "Stoping") == 0) {
    Serial.println("Problem PROBLEM!!!"); 
      digitalWrite(motorPinRightDir, dir);
      analogWrite(motorPinRightSpeed, 0);
    // Perform additional actions here if the payload is "Driving..."
  }
        if (strcmp(payloadStr, "Driving Straight") == 0) {
    Serial.println("Driving Forward"); 
        myServo.write(90);
  }
}

// connect to broker
void performConnect()
{
  uint16_t connectionDelay = 500;
  while (!mqttClient.connected())
  {
    Serial.printf("Trace   : Attempting MQTT connection...\n");
    if (mqttClient.connect(clientId.c_str(), MQTT_USERNAME, MQTT_KEY))
    {
      Serial.printf("Trace   : Connected to Broker.\n");

      /* Subscription to your topic after connection was succeeded.*/
      MQTTSubscribe(TOPIC);
    }
    else
    {
      Serial.printf("Error!  : MQTT Connect failed, rc = %d\n", mqttClient.state());
      Serial.printf("Trace   : Trying again in %d msec.\n", connectionDelay);
      delay(connectionDelay);
    }
  }
}

boolean MQTTPublish(const char* topic, char* payload)
{
  boolean retval = false;
  if (mqttClient.connected())
  {
    retval = mqttClient.publish(topic, payload);
  }
  return retval;
}

boolean MQTTSubscribe(const char* topicToSubscribe)
{
  boolean retval = false;
  if (mqttClient.connected())
  {
    retval = mqttClient.subscribe(topicToSubscribe);
  }
  return retval;
}

boolean MQTTIsConnected()
{
  return mqttClient.connected();
}

void MQTTBegin()
{
  mqttClient.setServer(MQTT_BROKER, MQTT_BROKER_PORT);
  mqttClient.setCallback(dataCallback);
  mqttInitCompleted = true;
}

void MQTTLoop()
{
  if(mqttInitCompleted)
  {
    if (!MQTTIsConnected())
    {
      performConnect();
    }
    mqttClient.loop();
  }
}
void WiFiBegin(const char* ssid, const char* pass)
{
  WiFi.begin(ssid, pass);
  Serial.printf("Waiting for AP connection ...\n");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(WIFI_TIMEOUT);
    Serial.printf(".");
  }
  IPAddress ip = WiFi.localIP();
  Serial.printf("\nConnected to AP. IP : %d.%d.%d.%d\n", 
    ip[0],ip[1],ip[2],ip[3]);
}

void setup() 
{
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  WiFiBegin(STA_SSID, STA_PASS);
  MQTTBegin();

  pinMode(motorPinRightDir, OUTPUT);
  pinMode(motorPinRightSpeed, OUTPUT);

  
  // Attach the servo to the pin
  myServo.attach(servoPin);

}

void loop() 
{
  
  MQTTLoop();
  delay(LOOP_TIMEOUT);
}
