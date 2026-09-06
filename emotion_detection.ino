#include <LiquidCrystal.h>

#define SOUND_SENSOR A0

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Emotion");
  lcd.setCursor(0, 1);
  lcd.print("Detection");
  delay(2000);
  lcd.clear();
}

void loop() {
  int soundValue = analogRead(SOUND_SENSOR);

  Serial.print("Sound Level: ");
  Serial.println(soundValue);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sound: ");
  lcd.print(soundValue);

  lcd.setCursor(0, 1);

  if (soundValue < 300) {
    lcd.print("Calm");
  }
  else if (soundValue < 600) {
    lcd.print("Normal");
  }
  else {
    lcd.print("Excited");
  }

  delay(500);
}
