#include <Wire.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "Dogin?";
const char* password = "594020xxxx";
#define OLED_RESET -1
Adafruit_SSD1306 OLED(OLED_RESET);
#define mqtt_server "m11.cloudmqtt.com"
#define mqtt_port 15714
#define mqtt_user "hapoinwt"
#define mqtt_password "2LwT2ZsXo8Tq"
#define LED_PIN 16
WiFiClient espClient;
PubSubClient client(espClient); 
void setup() {
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C); 

  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  delay(10);
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.println(WiFi.status());
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
  Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
    Serial.println("connected");
    light("LED Ready");
    client.subscribe("/ESP/LED");
    }  
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
      return;
    }
 }
 client.loop();
}
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String msg = "";
  int i=0;
  while (i<length) msg += (char)payload[i++];
  if (msg == "OFF") {
  digitalWrite(LED_PIN, LOW);
  client.publish("/ESP/LED", (digitalRead(LED_PIN) ? "LEDON" : "LEDOFF"));
  Serial.println("Send !");
  light("LED OFF");
  return;
  }
  else if(msg == "ON") {
  digitalWrite(LED_PIN, HIGH);
  client.publish("/ESP/LED", (digitalRead(LED_PIN) ? "LEDON" : "LEDOFF"));
  Serial.println("Send !");
  light("LED ON");
  }
  Serial.println(msg);
}
void light(char ant[10]){
    OLED.clearDisplay(); 
    OLED.setTextColor(WHITE);
    OLED.setCursor(15,20); 
    OLED.setTextSize(2); 
    OLED.println(ant); 
    OLED.display();
}

