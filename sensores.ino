#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

#define DHTPin 3 //pin del arudino y sensor 

#define DHTTYPE DHT22

DHT dht(DHTPin, DHTTYPE);

const int sensorHumedadS = A0;

void setup() {
   Serial.begin(9600);
    delay(000);
   dht.begin();

}

void loop() {
    float h = dht.readHumidity();
    float tC = dht.readTemperature();
    float tF = dht.readTemperature(true);
    int hS = analogRead(sensorHumedadS);

    Serial.println(h);
    Serial.println(tC);
    Serial.println(tF);
    Serial.println(hS);

}
