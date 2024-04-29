#include <DHT.h>
#include <ArduinoHttpClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Ethernet.h>


#define DHTPin 3 //pin del arudino y sensor 

#define DHTTYPE DHT22

DHT dht(DHTPin, DHTTYPE);

const char *host = "localhost";
const int port = 3000;
bool ejecucion = false;

EthernetClient ethernetClient;
HttpClient client = HttpClient(ethernetClient, host, port);

String createJsonString(float h, float tC, float tF);

void setup(){
  Serial.begin(9600);
  //delay(2000);
  dht.begin();
}
void loop(){
  if(!ejecucion){
  //delay(2000);
    float h = dht.readHumidity();
    float tC = dht.readTemperature();
    float tF = dht.readTemperature(true);

  //envio de variables
    String jsonPayload = createJsonString(h, tC, tF);
    Serial.println(jsonPayload);
    client.post("/datos-sensor", "application/json", jsonPayload);

    if (client.post("/datos-sensor", "application/json", jsonPayload) == 0) {
      Serial.println("Error al enviar datos al servidor.");
    }
    ejecucion = true;
  }

}

String createJsonString(float h, float tC, float tF){
  return "{\"humedad\":"+ String(h) + ",\"temperaturaC\":" + String(tC) + ",\"temperaturaF\":" + String(tF) + "}";
}
//exit(0);


