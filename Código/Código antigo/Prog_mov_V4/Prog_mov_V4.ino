#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Adafruit_MPU6050 mpu;

const byte BOTAO1 = 13;
const byte BOTAO2 = 12;
const byte BOTAO3 = 11;
const byte BOTAO4 = 10;
byte valorBotao1;
byte valorBotao2;
byte valorBotao3;
byte valorBotao4;

void setup() {
  Serial.begin(115200);
  servo1.attach(3);
  servo2.attach(4);
  servo3.attach(5);
  servo4.attach(6);
  servo5.attach(7);
  servo6.attach(8);
  Wire.begin();
  mpu.begin();
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(90);
  servo6.write(110);
  pinMode (BOTAO1, INPUT);
  pinMode (BOTAO2, INPUT);
  pinMode (BOTAO3, INPUT);
  pinMode (BOTAO4, INPUT);

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);//2_G,4_G,8_G,16_G
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);//250,500,1000,2000
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  int value1 = a.acceleration.x;
  int value2 = a.acceleration.y;
  valorBotao1 = digitalRead (BOTAO1);
  valorBotao2 = digitalRead (BOTAO2);
  valorBotao3 = digitalRead (BOTAO3);
  valorBotao4 = digitalRead (BOTAO4);
  
  if(valorBotao1 == 1){
    value2 = map(value2,  -18 ,18, 180, 0);
    servo1.write(value2);  
    delay(100);
  } 
  if(valorBotao2 == 1){
    value1 = map(value1,  -25, 25, 180, 0);
    servo2.write(value1);
    value2 = map(value2,  25, -25, 180, 0);
    servo3.write(value2);     
    delay(100);
  }
  if(valorBotao3 == 1){
    value2 = map(value2,  10, -10, 180, 0);
    servo4.write(value2);  
    delay(100);
    value1 = map(value1,  -10, 10, 180, 0);
    servo5.write(value1);  
    delay(100);
  }
  if(valorBotao4 == 1){
    servo6.write(0);
  }
  else{
    servo6.write(110);
  }

}
