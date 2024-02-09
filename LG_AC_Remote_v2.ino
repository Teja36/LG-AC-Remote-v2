#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ArduinoJson.h>
#import "index.h"

IRsend irsend(14);  // An IR LED is controlled by GPIO pin 14 (D5)


// temperature : 18 ~ 30
unsigned int ac_temperature = 24;

uint32_t ac_code_to_sent;

bool power = false;
bool swing = false;
bool jetcool = false;
bool fan = false;

int timerIndex = -1;

String timerTime = "";

const uint32_t kAc_Timer[8] = {0x88903C8, 0x8890788, 0x8890B37, 0x8890EF6, 0x88910C6, 0x88912A6, 0x88914A8, 0x8891677};

StaticJsonDocument<150> doc;

/*Put your SSID & Password*/
const char* ssid = "Hi5Wi5";  // Enter SSID here
const char* password = "babuji999";  //Enter Password here

ESP8266WebServer server(80);

void setup() {
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/power", handle_power);
  server.on("/data", handle_getData);
  server.on("/increment", handle_increment);
  server.on("/decrement", handle_decrement);
  server.on("/swing", handle_swing);
  server.on("/jetcool", handle_jetcool);
  server.on("/fan", handle_fan);
  server.on("/setTimer", handle_setTimer);
  server.on("/cancelTimer", handle_cancelTimer);



  server.begin();
  Serial.println("HTTP server started");
  irsend.begin();
}

void loop() {
  server.handleClient();
}

void Ac_Send_Code(uint32_t code) {
  Serial.print("code to send : ");
  Serial.print(code, BIN);
  Serial.print(" : ");
  Serial.println(code, HEX);

#if SEND_LG
  irsend.sendLG(code, 28);
#else  // SEND_LG
  Serial.println("Can't send because SEND_LG has been disabled.");
#endif  // SEND_LG
}

void Ac_Activate(unsigned int temperature) {

  unsigned int ac_msbits1 = 8;
  unsigned int ac_msbits2 = 8;
  unsigned int ac_msbits3 = 0;
  unsigned int ac_msbits4 = 0;  // cooling
  unsigned int ac_msbits5 =  (temperature < 15) ? 0 : temperature - 15;
  unsigned int ac_msbits6 = 0;


  // calculating using other values
  unsigned int ac_msbits7 = (ac_msbits3 + ac_msbits4 + ac_msbits5 +
                             ac_msbits6) & B00001111;
  ac_code_to_sent = ac_msbits1 << 4;
  ac_code_to_sent = (ac_code_to_sent + ac_msbits2) << 4;
  ac_code_to_sent = (ac_code_to_sent + ac_msbits3) << 4;
  ac_code_to_sent = (ac_code_to_sent + ac_msbits4) << 4;
  ac_code_to_sent = (ac_code_to_sent + ac_msbits5) << 4;
  ac_code_to_sent = (ac_code_to_sent + ac_msbits6) << 4;
  ac_code_to_sent = (ac_code_to_sent + ac_msbits7);

  Ac_Send_Code(ac_code_to_sent);
}

void handle_OnConnect() {
  Serial.println("Client connected!");
  server.send(200, "text/html", MAIN_page);
}

void handle_power() {
  if (!power) {
    power = true;
    Serial.println("Power ON");

    Ac_Activate(ac_temperature);

    server.send(200, "text/plain", "ON");
  }
  else {
    power = false;
    Serial.println("Power OFF");

    ac_code_to_sent = 0x88C0051;
    Ac_Send_Code(ac_code_to_sent);

    server.send(200, "text/plain", "OFF");
  }
}

void handle_getData() {

  String s;

  doc["temp"] = jetcool ? "Po" : String(ac_temperature) + "°C";;
  doc["power"] = power;
  doc["fan"] = fan;
  doc["swing"] = swing;
  doc["jetcool"] = jetcool;
  doc["timer"] = timerTime;

  serializeJson(doc, s);
  Serial.println(s);

  server.send(200, "application/json", s);
}

void handle_increment() {
  if (ac_temperature >= 30) {
    server.send(403);
    return;
  }
  ac_temperature++;
  jetcool = false;
  Serial.print("Incrementing temp to ");
  Serial.println(ac_temperature);
  Ac_Activate(ac_temperature);
  server.send(200, "text/plain", String(ac_temperature) + "°C");
}

void handle_decrement() {
  if (ac_temperature <= 18) {
    server.send(403);
    return;
  }
  ac_temperature--;
  jetcool = false;
  Serial.print("Decrementing temp to ");
  Serial.println(ac_temperature);

  Ac_Activate(ac_temperature);

  server.send(200, "text/plain", String(ac_temperature) + "°C");
}

void handle_swing() {

  swing = !swing;
  Serial.print("Swing: ");
  Serial.print(swing);

  ac_code_to_sent = 0x8810001;
  Ac_Send_Code(ac_code_to_sent);

  String res = swing ? "ON" : "OFF";
  server.send(200, "text/plain", res);
}

void handle_jetcool() {

  String res;

  if (!jetcool) {
    ac_code_to_sent = 0x8810089;
    res = "Po";
    Ac_Send_Code(ac_code_to_sent);
  }
  else {
    res = String(ac_temperature) + "°C";
    Ac_Activate(ac_temperature);
  }

  jetcool = !jetcool;
  Serial.println("Jet Cool!");

  server.send(200, "text/plain", res);
}

void handle_fan() {

  String res;

  if (!fan) {
    res = "Fan";
    Ac_Activate(30);
  }
  else {
    res = String(ac_temperature) + "°C";
    Ac_Activate(ac_temperature);
  }

  fan = !fan;
  Serial.println("Fan!");

  server.send(200, "text/plain", res);
}

void handle_setTimer() {

  timerIndex = server.arg("value").toInt();
  timerTime = server.arg("time");
  Serial.print("Timer set to: ");
  Serial.println(timerIndex);
  Serial.println(timerTime);

  ac_code_to_sent = kAc_Timer[timerIndex];
  Ac_Send_Code(ac_code_to_sent);

  server.send(200, "text/plain", timerTime);
}

void handle_cancelTimer() {

  timerIndex = -1;
  timerTime = "";

  ac_code_to_sent = 0x88B000B;
  Ac_Send_Code(ac_code_to_sent);

  Serial.println("Timer canceled!");
  server.send(200, "text/plain", ".");
}
