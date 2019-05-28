#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <Wire.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
Adafruit_SSD1306 OLED(OLED_RESET);
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "ECE-Wifi";
const char* password = "1234567890";

#define mqtt_server "m10.cloudmqtt.com"
#define mqtt_port 10634
#define mqtt_user "kzivuvbu"
#define mqtt_password "_PHQSuLOoxYO"

WiFiClient espClient;
PubSubClient client(espClient);
void setup() {

  Serial.begin(115200);
  delay(10);
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

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  dht.begin();
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setTextSize(2);
  
}
void loop() {
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if(client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("/GROUP123/TEMP/#");
    } else {
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
  int i = 0;
  while (i < length) msg += (char)payload[i++];
  if (msg == "GET") {
    const char t = dht.readTemperature();
    client.publish("/GROUP123/TEMP/1/",t);
    Serial.println("Send !");
    return;
  }
  Serial.println(msg);
}
