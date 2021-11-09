#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;  

int angle =90;    
int angleStep =15;

SoftwareSerial bluetooth(0, 1);

void setup() {
   Serial.begin(9600);
   bluetooth.begin(115200);
   myservo.attach(6);
   myservo.write(angle);
}

void loop() {
   char serial = Serial.read ();
   switch (serial){
    
    case 'r':
    if (angle > 0 && angle <= 180) {
      angle = angle - angleStep;
       if(angle < 0){
        angle = 0;
       }else{
      myservo.write(angle); // move the servo to desired angle
       }
    }
    
  delay(100); // waits for the servo to get there
  break;

  case 'l':

    if (angle >= 0 && angle <= 180) {
      angle = angle + angleStep;
      if(angle >180){
        angle =180;
       }else{
      myservo.write(angle); // move the servo to desired angle
       }
    }
    
  delay(100); // waits for the servo to get there
  break; 
   }   
}
