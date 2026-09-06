#define TEMP_SENSOR A0
#define FAN_PIN 9

int threshold = 30;

void setup() {
  Serial.begin(9600);
  pinMode(FAN_PIN, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(TEMP_SENSOR);

  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = voltage * 100.0;

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  if (temperature >= threshold) {
    digitalWrite(FAN_PIN, HIGH);
    Serial.println("Fan: ON");
  } else {
    digitalWrite(FAN_PIN, LOW);
    Serial.println("Fan: OFF");
  }

  delay(1000);
}
