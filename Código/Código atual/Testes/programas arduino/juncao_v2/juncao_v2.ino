#include <Servo.h>

Servo servoXRight;  // Servo conectado à porta 6 para movimento horizontal da mão direita
Servo servoYRight;  // Servo conectado à porta 7 para movimento vertical da mão direita
Servo servoXLeft;   // Servo conectado à porta 8 para movimento horizontal da mão esquerda
Servo servoYLeft;   // Servo conectado à porta 9 para movimento vertical da mão esquerda

int targetXPosRight = 90;  // Posição desejada do servo X da mão direita (horizontal)
int targetYPosRight = 90;  // Posição desejada do servo Y da mão direita (vertical)
int targetXPosLeft = 90;   // Posição desejada do servo X da mão esquerda (horizontal)
int targetYPosLeft = 90;   // Posição desejada do servo Y da mão esquerda (vertical)

void setup() {
  // Inicialização da comunicação serial
  Serial.begin(9600);

  // Inicialização dos servos
  servoXRight.attach(6);
  servoYRight.attach(7);
  servoXLeft.attach(3);   // Alterada a porta para 8
  servoYLeft.attach(5);   // Alterada a porta para 9
}

void loop() {
  while (Serial.available()) {
    char receivedChar = Serial.read();
    //int receivedValue = Serial.parseInt();

    // Identificar qual mão e eixo está sendo controlado
    if (receivedChar == 'A') {
      int xr = Serial.parseInt();
      targetXPosRight = map(xr, 0, 255, 0, 180);
    } 
    else if (receivedChar == 'B') {
      int yr = Serial.parseInt();
      targetYPosRight = map(yr, 0, 255, 0, 180);
    } 
    else if (receivedChar == 'C') {
      int xl = Serial.parseInt();
      targetXPosLeft = map(xl, 0, 255, 0, 180);
    } 
    else if (receivedChar == 'D') {
      int yl = Serial.parseInt();
      targetYPosLeft = map(yl, 0, 255, 0, 180);
    }
  }

  // Movimento gradual dos servos
  moveServo(servoXRight, targetXPosRight);
  moveServo(servoYRight, targetYPosRight);
  moveServo(servoXLeft, targetXPosLeft);
  moveServo(servoYLeft, targetYPosLeft);
}

void moveServo(Servo servo, int targetPos) {
  int currentPos = servo.read();
  int increment = (targetPos > currentPos) ? 1 : -1;

  if (currentPos != targetPos) {
    for (int pos = currentPos; pos != targetPos; pos += increment) {
      servo.write(pos);
      delay(10);  // Ajuste a velocidade do movimento conforme necessário
    }

    servo.write(targetPos);
  }
}
