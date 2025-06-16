#include <Servo.h>

Servo servo;

int servoPin = 9;
int ledR = 3;
int ledG = 5;
int ledB = 6;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  servo.write(90); // posição inicial
  analogWrite(ledR, 0);
  analogWrite(ledG, 0);
  analogWrite(ledB, 0);
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();

    if (line.length() > 0) {
      if (line.charAt(0) == 'S') { // Comando servo
        int angle = line.substring(1).toInt();
        if (angle >= 0 && angle <= 180) {
          servo.write(angle);
          Serial.print("Servo: ");
          Serial.println(angle);
        }
      }
      else if (line.charAt(0) == 'L') { // Comando led RGB
        String rgb = line.substring(1);
        int firstComma = rgb.indexOf(',');
        int secondComma = rgb.indexOf(',', firstComma + 1);
        if (firstComma > 0 && secondComma > firstComma) {
          int r = rgb.substring(0, firstComma).toInt();
          int g = rgb.substring(firstComma + 1, secondComma).toInt();
          int b = rgb.substring(secondComma + 1).toInt();

          analogWrite(ledR, r);
          analogWrite(ledG, g);
          analogWrite(ledB, b);

          Serial.print("LED RGB: ");
          Serial.print(r);
          Serial.print(", ");
          Serial.print(g);
          Serial.print(", ");
          Serial.println(b);
        }
      }
    }
  }
}
