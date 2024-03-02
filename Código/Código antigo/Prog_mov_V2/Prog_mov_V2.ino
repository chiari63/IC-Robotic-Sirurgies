
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

void setup(void) {
  Serial.begin(115200);
  servo1.attach(3);
  servo2.attach(4);
  servo3.attach(5);
  servo4.attach(6);
  servo5.attach(7);
  servo6.attach(8);
  Wire.begin();
  mpu.begin();
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  servo5.write(0);
  servo6.write(0);

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);//2_G,4_G,8_G,16_G
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);//250,500,1000,2000
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  int value1 = g.gyro.z;
  int value2 = a.acceleration.x;
  int value3 = a.acceleration.y;

  value1 = map(value1,  -10, 10, 180, 0);
  servo1.write(value1);  
  Serial.println(value1);
  delay(100);

  value2 = map(value2,  -10, 10, 180, 0);
  servo2.write(value2);  
  Serial.println(value2);
  delay(10);

  value2 = map(value2,  -10, 10, 180, 0);
  servo3.write(value2);  
  Serial.println(value2);
  delay(10);
  
  value3 = map(value3,  -10, 10, 180, 0);
  servo4.write(value3);  
  Serial.println(value3);
  delay(10);
}
