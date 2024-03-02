#include<Wire.h>
#include <Servo.h>

//Endereço em hexadecimal do sensor MPU 6050
const int ENDERECO_SENSOR=0x68;  
int girX, girY, girZ, acelX, acelY, acelZ, temperatura;

Servo myservo1;

int angle =90;    
int angleStep =15;

void setup() {
  Serial.begin(1200);
  Wire.begin();
  Wire.beginTransmission(ENDERECO_SENSOR);
  Wire.write(0x6B);
  Wire.write(0); 
  Wire.endTransmission(true);

  myservo1.attach(2);
  myservo1.write(0);

}

void loop() {
  Wire.beginTransmission(ENDERECO_SENSOR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(ENDERECO_SENSOR, 14, true);

  acelX = Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)  
  acelY = Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)  
  acelZ = Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L) 

  girX = Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)     
  girY = Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  girZ = Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)


  Serial.print("Acelerômetro X = "); 
  Serial.print(acelX);
 
  //Printa o valor Y do acelerômetro na serial
  Serial.print(" \tY = "); 
  Serial.print(acelY);
   
  //Printa o valor Z do acelerômetro na serial
  Serial.print(" \tZ = "); 
  Serial.println(acelZ);

  if(acelX >= 3800){
        angle = angle - angleStep;
       if(angle < 0){
        angle = 0;
       }else{
      myservo1.write(angle);
  }
 }
  delay(100);
  
   if(acelX <= 2700){
        angle = angle + angleStep;
      if(angle >180){
        angle =180;
       }else{
      myservo1.write(angle);
    }
   }
}
