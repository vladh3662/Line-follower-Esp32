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

float lpos;

void setup() {
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);

  pinMode(lms, OUTPUT);
  pinMode(rms, OUTPUT);

  Serial.begin(9600);
}

void forward() {
  digitalWrite(rmf, HIGH);
  digitalWrite(rmb, LOW);
  digitalWrite(lmf, HIGH);
  digitalWrite(lmb, LOW);

  analogWrite(rms, 150);
  analogWrite(lms, 150);
}

void turnRight() {
  analogWrite(rms, 50);
  analogWrite(lms, 150);
  digitalWrite(rmf, HIGH);
  digitalWrite(rmb, LOW);
  digitalWrite(lmf, HIGH);
  digitalWrite(lmb, LOW);
}

void turnLeft() {
  analogWrite(rms, 150);
  analogWrite(lms, 50);
  digitalWrite(rmf, HIGH);
  digitalWrite(rmb, LOW);
  digitalWrite(lmf, HIGH);
  digitalWrite(lmb, LOW);
}

void loop() {
  line_pos();
  delay(10);
  motor();
  delay(5);
}

void line_pos() {
  int s1 = digitalRead(D1);
  int s2 = digitalRead(D2);
  int s3 = digitalRead(D3);
  int s4 = digitalRead(D4);
  int s5 = digitalRead(D5);
  if (s1 + s2 + s3 + s4 + s5 != 0)
    lpos = (1 * s1 + 2 * s2 + 3 * s3 + 4 * s4 + 5 * s5) / (float)(s1 + s2 + s3 + s4 + s5);
}

void motor() {
  if (lpos <= 3.5 && lpos >= 2.5)
    forward();
  else if (lpos <= 5 && lpos >= 4)
    turnRight();
  else
    turnLeft();
}
