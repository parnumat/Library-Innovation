#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1

Adafruit_SSD1306 OLED(OLED_RESET);

const char* ssid = "iPhone ของ Administrator";
const char* password = "555555555";
// Config MQTT Server
#define mqtt_server "test.mosquitto.org"
#define mqtt_port 1883
#define mqtt_user ""
#define mqtt_password ""
//#define LED_PIN BUILTIN_LED
WiFiClient espClient;
PubSubClient client(espClient);
String room1;
String room2;

void setup() {
  pinMode(D0, OUTPUT);
  Serial.begin(115200);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}
void loop() {
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("SOSScreen")) {
      Serial.println("connected");
      client.subscribe("/SOS/#");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000); return;
    }
  }
  client.loop();
}
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String msg = "";
  int i = 0;
  while (i < length) msg += (char)payload[i++];
  if (msg != "") {
    if (String(topic) == "/SOS/for/WC1") {
      room1 = msg;
      printOLED(room1, room2);
      Serial.println(room1);
    }
    if (String(topic) == "/SOS/for/WC2") {
      room2 = msg;
      printOLED(room1, room2);
      Serial.println(room2);
    }
    return;
  }
  Serial.println(msg);
}
void printOLED(String room1, String room2)
{
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setCursor(5, 0);
  OLED.setTextSize(1.95);
  OLED.println("room1:"+room1);
  OLED.setCursor(5, 35);
  OLED.println("room2:"+room2);
  OLED.display();
}
