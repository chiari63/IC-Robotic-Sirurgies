#include <Servo.h>

Servo servoX;  // Servo conectado à porta 3
Servo servoY;  // Servo conectado à porta 4

int targetXPos = 90;  // Posição desejada do servo X
int targetYPos = 90;  // Posição desejada do servo Y

void setup() {
  // Inicialização da comunicação serial
  Serial.begin(9600);

  // Inicialização dos servos
  servoX.attach(3);
  servoY.attach(4);
}

void loop() {
  while (Serial.available()) {
    char receivedChar = Serial.read();

    if (receivedChar == 'X') {
      int x = Serial.parseInt();
      targetXPos = map(x, 0, 255, 0, 180);
    }
    else if (receivedChar == 'Y') {
      int y = Serial.parseInt();
      targetYPos = map(y, 0, 255, 0, 180);
    }
  }

  // Movimento gradual do servo X
  if (servoX.read() != targetXPos) {
    moveServo(servoX, targetXPos);
  }

  // Movimento gradual do servo Y
  if (servoY.read() != targetYPos) {
    moveServo(servoY, targetYPos);
  }
}

void moveServo(Servo servo, int targetPos) {
  int currentPos = servo.read();
  int increment = (targetPos > currentPos) ? 1 : -1;

  if (currentPos != targetPos) {
    for (int pos = currentPos; pos != targetPos; pos += increment) {
      servo.write(pos);
      delay(15);  // Ajuste a velocidade do movimento conforme necessário
    }

    servo.write(targetPos);
  }
}
