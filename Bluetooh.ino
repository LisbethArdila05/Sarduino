#include <DHT.h>
#include <SoftwareSerial.h>

#define DHTPin 3 // Pin del Arduino y del sensor
#define DHTTYPE DHT22

DHT dht(DHTPin, DHTTYPE);
SoftwareSerial BT(10, 11); // RX, TX para el módulo Bluetooth

bool ejecucion = false;
const int sensorHumedadS = A0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  BT.begin(9600); // Inicializa la comunicación serie con el módulo Bluetooth
}

void loop() {
  if (!ejecucion) {
    float h = dht.readHumidity();
    float tC = dht.readTemperature();
    float tF = dht.readTemperature(true);
    int hS = analogRead(sensorHumedadS);

    // Envío de datos al dispositivo conectado a través de Bluetooth
    String jsonPayload = createJsonString(h, tC, tF, hS);
    BT.println(jsonPayload);

    ejecucion = true;
  }
}

String createJsonString(float h, float tC, float tF, int hS) {
  return "{\"humedad\":" + String(h) + ",\"temperaturaC\":" + String(tC) + ",\"temperaturaF\":" + String(tF) + ",\"humedadS\":" + String(hS) + "}";
}
