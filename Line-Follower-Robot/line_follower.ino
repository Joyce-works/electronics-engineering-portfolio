// -------- MOTOR A (LEFT) --------
#define AIN1 4
#define AIN2 5
#define PWMA 9

// -------- MOTOR B (RIGHT) --------
#define BIN1 6
#define BIN2 7
#define PWMB 10

#define STBY 8

// -------- IR SENSOR PINS --------
int sensorPins[8] = {A0, A1, A2, A3, A4, A5, 2, 3};
int sensorValue[8];

// -------- PID CONSTANTS --------
float Kp = 18;
float Kd = 8;

int error = 0;
int previousError = 0;

int baseSpeed = 95;
int maxSpeed = 170;

// Motor balance (adjust if needed)
int leftOffset  = -8;   // decrease left motor slightly
int rightOffset = -8;

void setup() {

  Serial.begin(9600);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);

  for (int i = 0; i < 8; i++) {
    pinMode(sensorPins[i], INPUT);
  }
}

void loop() {

  readSensors();
  calculateError();
  pidControl();
}

void readSensors() {
  for (int i = 0; i < 8; i++) {
    sensorValue[i] = digitalRead(sensorPins[i]);
  }
}

void calculateError() {

  int weights[8] = {-4, -3, -2, -1, 1, 2, 3, 4};
  int sum = 0;
  int count = 0;

  for (int i = 0; i < 8; i++) {
    if (sensorValue[i] == LOW) {   // BLACK detected
      sum += weights[i];
      count++;
    }
  }

  if (count != 0) {
    error = sum / count;
  }
}

void pidControl() {

  int derivative = error - previousError;

  int correction = (Kp * error) + (Kd * derivative);

  correction = constrain(correction, -70, 70);

  int leftSpeed  = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  leftSpeed  += leftOffset;
  rightSpeed += rightOffset;

  leftSpeed  = constrain(leftSpeed, 60, maxSpeed);
  rightSpeed = constrain(rightSpeed, 60, maxSpeed);

  setMotor(leftSpeed, rightSpeed);

  previousError = error;
}

void setMotor(int leftSpeed, int rightSpeed) {

  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, leftSpeed);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, rightSpeed);
}
