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
String Shief;

void setup() {
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  pinMode(LED_PIN, OUTPUT);

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}
void loop() {
  if (!client.connected()) {
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      client.subscribe("/ESP/OLED01");
    }
    else {
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
  if (msg != "") {
    if (String(topic) == "/ESP/OLED01") {
      Shief = msg;
      digitalWrite(LED_PIN,HIGH);
      Light(Shief);
       
    }
    return;
  }
}
void Light(String Shief){
    OLED.clearDisplay(); 
    
    OLED.setTextColor(WHITE);
    OLED.setCursor(10,25); 
    OLED.setTextSize(2); 
    OLED.println(Shief); 
    OLED.display();
    delay(5000);
    
    OLED.clearDisplay();
    OLED.display();
    digitalWrite(LED_PIN,LOW);
}

