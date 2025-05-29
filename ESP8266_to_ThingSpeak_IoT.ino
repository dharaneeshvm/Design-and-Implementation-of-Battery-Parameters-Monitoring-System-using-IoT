#include <ESP8266WiFi.h>
#include <DHT.h>

// WiFi Credentials
const char* ssid = "";// Enter Your Wi-Fi Name
const char* password = "";// Enter Your Wi-Fi Password

// ThingSpeak API Key
const char* apiKey = "";//Enter Your API Key
const char* server = "api.thingspeak.com";

// DHT11 Configuration
#define DHTPIN D4  // DHT11 data pin
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Voltage Sensor
#define VOLTAGE_PIN A0
float vRef = 3.3; // ESP8266 ADC Reference Voltage (Can be 3.3V or 1.0V based on configuration)
float voltageDividerRatio = 5.0; // Adjust based on resistor values

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  dht.begin();
}

void loop() {
  // Read DHT11 Data
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read Voltage Sensor
  int rawValue = analogRead(VOLTAGE_PIN);
  float voltage = (rawValue * vRef / 1024.0) * voltageDividerRatio; 

  Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
  Serial.print("Voltage: "); Serial.print(voltage); Serial.println(" V");

  // Send data to ThingSpeak
  if (client.connect(server, 80)) {
    String url = "/update?api_key=" + String(apiKey) + 
                 "&field1=" + String(temperature) + 
                 "&field2=" + String(humidity) + 
                 "&field3=" + String(voltage);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + server + "\r\n" +
                 "Connection: close\r\n\r\n");
    client.stop();
    Serial.println("Data sent to ThingSpeak!");
  } else {
    Serial.println("Failed to connect to ThingSpeak");
  }

  delay(15000); // ThingSpeak allows data every 15 seconds
}
