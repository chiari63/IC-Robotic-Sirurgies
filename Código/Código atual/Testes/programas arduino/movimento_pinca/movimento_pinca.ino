#include <Servo.h>

Servo servo;
int servoPin = 8;
int servoPosition = 90;
int prevAngle = servoPosition;
unsigned long prevTime = 0;
unsigned long delayTime = 100;  // Tempo de atraso entre os movimentos do servo em milissegundos

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(servoPosition);
}

void loop() {
  if (Serial.available() > 0) {
    int distance = Serial.parseInt();
    // Mapear a distância para a faixa de ângulos do servo (0 a 180 graus)
    int angle = map(distance, 0, 50, 60, 180);
    // Limitar o ângulo entre 0 e 180 graus
    angle = constrain(angle, 60, 180);

    // Verificar se houve uma mudança significativa no ângulo
    if (abs(angle - prevAngle) > 2 && millis() - prevTime >= delayTime) {
      servo.write(angle);
      prevAngle = angle;
      prevTime = millis();
    }
  }
}
