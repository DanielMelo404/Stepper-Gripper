/*
 Basic ESP8266 MQTT example
 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off
 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"
*/
#include <stdlib.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <AccelStepper.h>
#define BUILTIN_LED 2


const int dirPin = 1;
const int stepPin = 3;
//const int en = 3;
const int ms1 = 21;
const int ms2 = 19;
const int ms3 = 18;
const int reset = 5;
const int sleepPin = 17;


void setupPins(){
//  digitalWrite(en, LOW);
  digitalWrite(ms1, LOW);
  digitalWrite(ms2, LOW);
  digitalWrite(ms3, LOW);
  digitalWrite(reset, HIGH);
  digitalWrite(sleepPin, HIGH);
//  digitalWrite(en, LOW);
}

int requestedPosition =0;
int reachingPosition = 0;

// Define motor interface type
#define motorInterfaceType 1

AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

// Update these with values suitable for your network.

const char* ssid = "wifiName";
const char* password = "wifiPassword";

const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");
  }

  randomSeed(micros());

//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
//  Serial.print("Message arrived [");
//  Serial.print(topic);
//  Serial.print("] ");
  char pos[length];
  for (int i = 0; i < length; i++) {
    pos[i] = (char)payload[i];
//    Serial.print((char)payload[i]);
  }
  Serial.println(pos);
char *output;
    long result = strtol(pos, &output, 10) + 1;
//Serial.println((int)result);
//  requestedPosition = ((char)payload[0]-'0')*100;
requestedPosition = -1*(int)result;

//  Serial.println("requestedPosition"+(String)requestedPosition);
//Serial.println((char)payload[0]);

  
//  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopicDMA", "hello world");
      // ... and resubscribe
      client.subscribe("stepperDMAtopic");
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
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
//  Serial.begin(115200);
  setup_wifi();

setupPins();
//  Setup stepper
  myStepper.setMaxSpeed(500);
//  myStepper.setAcceleration(20);

    myStepper.setMinPulseWidth(55); 
//  Serial.begin(9600);

myStepper.setSpeed(500);
myStepper.moveTo(requestedPosition);
myStepper.setSpeed(500);

pinMode(18,OUTPUT);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
//  Serial.println(requestedPosition);
//  Serial.println("hi");
    if (requestedPosition != reachingPosition){
    reachingPosition = requestedPosition;
    myStepper.moveTo(requestedPosition);
    if(requestedPosition <myStepper.currentPosition() ){
        myStepper.setSpeed(-500);
    
    }else{
       myStepper.setSpeed(500);
    }
//    Serial.println((String)myStepper.currentPosition());
    
  }
  if (myStepper.currentPosition() == requestedPosition){
    myStepper.stop();
//    Serial.print("stop" + (String)myStepper.currentPosition());
  }
  else{
    myStepper.runSpeed();
  }

  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

//  unsigned long now = millis();
//  if (now - lastMsg > 20000) {
//    lastMsg = now;
//    ++value;
////    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
////    Serial.print("Publish message: ");
////    Serial.println(msg);
//    client.publish("outTopicDMA", msg);
//  }
}
