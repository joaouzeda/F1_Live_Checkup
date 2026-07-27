#include "WiFi.h"
#include "HTTPClient.h"
#include <UrlEncode.h>
#include "ArduinoJson.h"
#include "esp_system.h"
#include "defs.h"

const char* ssid  = SSID;
const char* pass  = PASS;

HTTPClient http;

String Payload    = "";
String Phone      = PhoneNumber;
String CallMeApi  = CallMeBotApiKey;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {  // connect to wifi
    Serial.println(WiFi.status());
    delay(5);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  Send_Message("Teste de conexão");
  delay(1000);
}



void Send_Message(String message){
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + Phone + "&apikey=" + CallMeApi + "&text=" + urlEncode(message);
  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httResponseCode = http.POST(url);
  
  if (httResponseCode == 200){
    Serial.println("Message sent successfully");
  }else {
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httResponseCode);
  }
  http.end();
}