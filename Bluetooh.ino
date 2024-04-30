#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>

#define DHTPin 3 //pin del arudino y sensor 
#define DHTTYPE DHT22

DHT dht(DHTPin, DHTTYPE);

SoftwareSerial BT(10,11); 

bool ejecucion = false;
const int sensorHumedadS = A0;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  delay(000);
  dht.begin();
}

void loop() {
  if(!ejecucion){
    float h = dht.readHumidity();
    float tC = dht.readTemperature();
    float tF = dht.readTemperature(true);
    int hS = analogRead(sensorHumedadS);

    String jsonString = createJsonString(h, tC, tF, hS);
    Serial.println(jsonString);

    if(BT.available()){
      BT.println(jsonString);
    }
    ejecucion = true;
  }
  // if(Serial.available()){
  //   BT.write(Serial.read())
  // }
}
String createJsonString(float h, float tC, float tF, int hS) {
  return "{\"humedad\":" + String(h) + ",\"temperaturaC\":" + String(tC) + ",\"temperaturaF\":" + String(tF) + ",\"humedadSuelo\":" + String(hS) + "}";
}
