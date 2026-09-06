#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

const char* server = "http://api.thingspeak.com/update";
String apiKey = "YOUR_THINGSPEAK_API_KEY";

#define DHTPIN 4
#define DHTTYPE DHT11

#define MQ135_PIN 34
#define RAIN_PIN 35

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);

  dht.begin();
  Wire.begin();

  if (!bmp.begin(0x76)) {
    if (!bmp.begin(0x77)) {
      Serial.println("BMP280 not detected!");
    }
  }

  pinMode(MQ135_PIN, INPUT);
  pinMode(RAIN_PIN, INPUT);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT sensor read failed!");
  }

  float pressure = bmp.readPressure() / 100.0F;
  float altitude = bmp.readAltitude(1013.25);

  int airQuality = analogRead(MQ135_PIN);
  int rainValue = analogRead(RAIN_PIN);

  String rainStatus;

  if (rainValue < 1500) {
    rainStatus = "Rain Detected";
  } else {
    rainStatus = "No Rain";
  }

  Serial.println();
  Serial.println("================================");
  Serial.println("       IoT WEATHER STATION");
  Serial.println("================================");

  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity    : ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pressure    : ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Altitude    : ");
  Serial.print(altitude);
  Serial.println(" m");

  Serial.print("Air Quality : ");
  Serial.println(airQuality);

  Serial.print("Rain Sensor : ");
  Serial.println(rainValue);

  Serial.print("Rain Status : ");
  Serial.println(rainStatus);

  Serial.println("================================");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = String(server) +
                 "?api_key=" + apiKey +
                 "&field1=" + String(temperature) +
                 "&field2=" + String(humidity) +
                 "&field3=" + String(pressure) +
                 "&field4=" + String(airQuality) +
                 "&field5=" + String(rainValue);

    http.begin(url);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("ThingSpeak Response: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("ThingSpeak Error: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }

  delay(20000);
}
