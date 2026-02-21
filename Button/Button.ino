// Motor A on L298N using your wiring:
// ENA -> D5
// IN1 -> D8
// IN2 -> D9
// Motor A wires on OUT1 / OUT2

const int ENA = 5;   // Enable/speed for Motor A
const int IN1 = 8;   // Direction arduino pin 8 for Motor A
const int IN2 = 9;   // Direction arduino pin 9 for Motor A
const int ENB = 6;
const int IN3 = 10;  //Direction arduino pin 10 for B 
const int IN4 = 11;

// === Button pins ===
const int BUTTON_FWD = 3;  // Forward button
const int BUTTON_REV = 4;  // Reverse button
// === State variables ===
int motorState = 0;        // 0 = off, 1 = forward, -1 = reverse
// last readings to detect edges
int lastFwdReading = HIGH;
int lastRevReading = HIGH;


void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_FWD, INPUT_PULLUP);
  pinMode(BUTTON_REV, INPUT_PULLUP);

  // Start with motor stopped
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENB, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  // Buttons with internal pull‑ups
  pinMode(BUTTON_FWD, INPUT_PULLUP);
  pinMode(BUTTON_REV, INPUT_PULLUP);

}

void loop() {
  int speed = 150; // 0–255
  int readingFwd = digitalRead(BUTTON_FWD); // LOW = pressed
  int readingRev = digitalRead(BUTTON_REV); // LOW = pressed
  
  // Forward button: detect transition HIGH -> LOW
  if (lastFwdReading == HIGH && readingFwd == LOW) {
    if (motorState != 1) {
      motorState = 1;  // go forward
    } else {
      motorState = 0;  // was forward -> off
    }
  }

  // Reverse button: detect transition HIGH -> LOW
  if (lastRevReading == HIGH && readingRev == LOW) {
    if (motorState != -1) {
      motorState = -1; // go reverse
    } else {
      motorState = 0;  // was reverse -> off
    }
  }

  lastFwdReading = readingFwd;
  lastRevReading = readingRev;

  if (motorState == 1) {
    // --- Spin forward ---
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    digitalWrite(LED_BUILTIN, HIGH);  // Motor A on
  } else if (motorState == -1) {
    // --- Spin backward ---
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    digitalWrite(LED_BUILTIN, LOW);  // Motor A on
  } else {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }

  // --- Spin forward ---
  /*digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(LED_BUILTIN, HIGH);  // Motor A on

  delay(5000);              // 3 seconds

  // --- Stop ---
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(2000);              // 2 seconds

  // --- Spin reverse ---
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(LED_BUILTIN, LOW);
  delay(5000);

  // --- Stop ---
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(3000);*/
}