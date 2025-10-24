#include <Arduino.h>
#define DHTPIN 15
#define DHTTYPE DHT22
#define LEDPIN 2
#define BLYNK_TEMPLATE_ID "TMPL68Oc4qv4Z"
#define BLYNK_TEMPLATE_NAME "DHT22Assignment"
#define BLYNK_AUTH_TOKEN "kmUnhEKYKIdCw7UPh54wE4gcntoLSwUy"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>


char ssid[] = "Wokwi-GUEST";
char pass[] = "";

DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

void sendSensorData() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (!isnan(temp)) {
    Blynk.virtualWrite(V1, temp);
  }

  if (!isnan(hum)) {
    Blynk.virtualWrite(V0, hum);
  }
}


BLYNK_WRITE(V2) {
  int ledState = param.asInt();
  digitalWrite(LEDPIN, ledState);
}

void setup() {
  pinMode(LEDPIN, OUTPUT);
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}

