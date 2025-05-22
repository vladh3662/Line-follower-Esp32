#define rmf 26
#define rmb 27
#define lmf 18
#define lmb 19

#define lms 13
#define rms 22

#define D1 32
#define D2 4
#define D3 5
#define D4 25
#define D5 14

#define start_pin 21

#define led 23

bool robotReady = false;

float lpos = 3.0;
float Kp = 30;
float Ki = 0.1;
float Kd = 30;

float error = 0, lastError = 0, integral = 0;

const int baseSpeed = 75;

void setup() {
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);

  pinMode(lms, OUTPUT);
  pinMode(rms, OUTPUT);

  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);

  pinMode(start_pin, INPUT);
  pinMode(led, OUTPUT);

  Serial.begin(9600);

  if (digitalRead(start_pin) == HIGH) {
    while (true) {
      digitalWrite(led, HIGH);
      delay(20);
      digitalWrite(led, LOW);
      delay(20);
    }
  } else if (digitalRead(start_pin) == LOW)
    robotReady = true;
}

void loop() {
  if (robotReady == true) {
    while (digitalRead(start_pin) == LOW) {
      digitalWrite(led, HIGH);
      delay(20);
      digitalWrite(led, LOW);
      delay(20);
    }
    line_pos();
    motor();
    delay(5);

    if (digitalRead(start_pin) == LOW) {
      analogWrite(rms, 0);
      analogWrite(lms, 0);

      while (true) {
        digitalWrite(led, HIGH);
        delay(20);
        digitalWrite(led, LOW);
        delay(20);
      }
    }
  }
}

void line_pos() {
  int s1 = digitalRead(D1);
  int s2 = digitalRead(D2);
  int s3 = digitalRead(D3);
  int s4 = digitalRead(D4);
  int s5 = digitalRead(D5);
  int sum = s1 + s2 + s3 + s4 + s5;

  if (sum != 0) {
    lpos = (1 * s1 + 2 * s2 + 3 * s3 + 4 * s4 + 5 * s5) / (float)sum;
  }
}

void motor() {
  error = lpos - 3.0;
  integral += error;
  float derivative = error - lastError;

  float correction = Kp * error + Ki * integral + Kd * derivative;

  int leftSpeed = constrain(baseSpeed + correction, 0, 255);
  int rightSpeed = constrain(baseSpeed - correction, 0, 255);

  digitalWrite(rmf, HIGH);
  digitalWrite(rmb, LOW);
  digitalWrite(lmf, HIGH);
  digitalWrite(lmb, LOW);

  analogWrite(rms, rightSpeed);
  analogWrite(lms, leftSpeed);

  lastError = error;
}