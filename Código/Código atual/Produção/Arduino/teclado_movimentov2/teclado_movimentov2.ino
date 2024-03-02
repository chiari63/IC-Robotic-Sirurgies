#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int target1Pos = 90;  
int target2Pos = 90;
int target3Pos = 90;  
int target4Pos = 90;
int target5Pos = 90;  

const byte BOTAO1 = 13;
const byte BOTAO2 = 12;
const byte BOTAO3 = 11;
const byte BOTAO4 = 10;
byte valorBotao1;
byte valorBotao2;
byte valorBotao3;
byte valorBotao4;

void setup() {
  Serial.begin(9600);
  
  servo1.attach(3);
  servo2.attach(4);
  servo3.attach(5);
  servo4.attach(6);
  servo5.attach(7);
  servo6.attach(8);

  servo6.write(110);
  
  pinMode (BOTAO1, INPUT);
  pinMode (BOTAO2, INPUT);
  pinMode (BOTAO3, INPUT);
  pinMode (BOTAO4, INPUT);

}

void loop() {
  valorBotao1 = digitalRead (BOTAO1);
  valorBotao2 = digitalRead (BOTAO2);
  valorBotao3 = digitalRead (BOTAO3);
  valorBotao4 = digitalRead (BOTAO4);

  while (Serial.available()) {
    char receivedChar = Serial.read();

    if (valorBotao1 == 1) {
      if (receivedChar == 'X') {
        int x = Serial.parseInt();
        target1Pos = map(x, 0, 255, 0, 180);
      }
      if (receivedChar == 'Y') {
        int y = Serial.parseInt();
        target2Pos = map(y, 0, 255, 0, 180);
      }
    }
    else if (valorBotao2 == 1) {
      if (receivedChar == 'Y') {
        int y = Serial.parseInt();
        target3Pos = map(y, 255, 0, 0, 180);
      }
    }
    else if (valorBotao3 == 1) {
      if (receivedChar == 'Y') {
        int y = Serial.parseInt();
        target5Pos = map(y, 0, 255, 0, 180);
      }
      if (receivedChar == 'X') {
        int x = Serial.parseInt();
        target4Pos = map(x, 255, 0, 0, 180);
      }
    }
    else if (valorBotao4 == 1) {
      servo6.write(0);
    }
    else{
      servo6.write(110);
    }
  }
  // Movimento gradual do servo 1
  if (servo1.read() != target1Pos) {
    moveServo(servo1, target1Pos);
  }
  // Movimento gradual do servo 2
  if (servo2.read() != target2Pos) {
    moveServo(servo2, target2Pos);
  }
  // Movimento gradual do servo 3
  if (servo3.read() != target3Pos) {
    moveServo(servo3, target3Pos);
  }
  // Movimento gradual do servo 4
  if (servo4.read() != target4Pos) {
    moveServo(servo4, target4Pos);
  }
  // Movimento gradual do servo 5
  if (servo5.read() != target5Pos) {
    moveServo(servo5, target5Pos);
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
