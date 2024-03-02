#include <Servo.h>

Servo servoX;  // Servo conectado à porta 3 para movimento horizontal (eixo X)
Servo servoY;  // Servo conectado à porta 4 para movimento vertical (eixo Y)

int targetXPos = 90;  // Posição desejada do servo X (horizontal)
int targetYPos = 90;  // Posição desejada do servo Y (vertical)

void setup() {
  // Inicialização da comunicação serial
  Serial.begin(9600);

  // Inicialização dos servos
  servoX.attach(6);
  servoY.attach(7);
}

void loop() {
  while (Serial.available()) {
    char receivedChar = Serial.read();

    if (receivedChar == 'X') {
      int x = Serial.parseInt();
      targetXPos = map(x, -255, 255, 0, 180);  // Mapeia o intervalo -255 a 255 para 0-180
    }
    else if (receivedChar == 'Y') {
      int y = Serial.parseInt();
      targetYPos = map(y, -255, 255, 0, 180);  // Mapeia o intervalo -255 a 255 para 0-180
    }
  }

  // Movimento gradual do servo X (horizontal)
  if (servoX.read() != targetXPos) {
    moveServo(servoX, targetXPos);
  }

  // Movimento gradual do servo Y (vertical)
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
