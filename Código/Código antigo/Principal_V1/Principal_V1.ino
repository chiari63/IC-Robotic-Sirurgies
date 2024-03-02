#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5; 

int angle =90;    
int angleStep =15;

SoftwareSerial bluetooth(0, 1);

void setup() {
   Serial.begin(9600);
   bluetooth.begin(115200);
   
   myservo1.attach(1);
   myservo2.attach(2);
   myservo3.attach(3);
   myservo4.attach(4);
   myservo5.attach(5);

   myservo1.write(0);
   myservo2.write(0);
   myservo3.write(0);
   myservo4.write(0);
   myservo5.write(0);
}

void loop() {
   char serial = Serial.read ();
   switch (serial){
    
  //servo 1 ======================================================
    
    case 'r':
    if (angle > 0 && angle <= 180) {
      angle = angle - angleStep;
       if(angle < 0){
        angle = 0;
       }else{
      myservo1.write(angle); // move the servo to desired angle
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
      myservo1.write(angle); // move the servo to desired angle
       }
    }
    
    delay(100); // waits for the servo to get there
    break;
  
//servo2 ===========================================================
      
    case 'q':
    if (angle > 0 && angle <= 180) {
      angle = angle - angleStep;
       if(angle < 0){
        angle = 0;
       }else{
      myservo2.write(angle); // move the servo to desired angle
       }
    }
    
    delay(100); // waits for the servo to get there
    break;

    case 'w':
    if (angle >= 0 && angle <= 180) {
      angle = angle + angleStep;
      if(angle >180){
        angle =180;
       }else{
          myservo2.write(angle); // move the servo to desired angle
       }
    }
    
    delay(100); // waits for the servo to get there
    break;

  //Servo 3=====================================================
  
    case 'e':
    if (angle > 0 && angle <= 180) {
      angle = angle - angleStep;
       if(angle < 0){
        angle = 0;
       }else{
      myservo3.write(angle); // move the servo to desired angle
       }
    }
    
    delay(100); // waits for the servo to get there
    break;

    case 't':
    if (angle >= 0 && angle <= 180) {
      angle = angle + angleStep;
      if(angle >180){
        angle =180;
       }else{
          myservo3.write(angle); // move the servo to desired angle
       }
    }
    
    delay(100); // waits for the servo to get there
    break;

  //servo 4 ======================================================

  
    case 'y':
    if (angle > 0 && angle <= 180) {
      angle = angle - angleStep;
       if(angle < 0){
        angle = 0;
       }else{
      myservo4.write(angle); // move the servo to desired angle
       }
    }
    
    delay(100); // waits for the servo to get there
    break;

    case 'u':
    if (angle >= 0 && angle <= 180) {
      angle = angle + angleStep;
      if(angle >180){
        angle =180;
       }else{
          myservo4.write(angle); // move the servo to desired angle
       }
    }
    
    delay(100); // waits for the servo to get there
    break;

  //servo 5  =======================================================

  
    case 'i':
    if (angle > 0 && angle <= 180) {
      angle = angle - angleStep;
       if(angle < 0){
        angle = 0;
       }else{
      myservo5.write(angle); // move the servo to desired angle
       }
    }
    
    delay(100); // waits for the servo to get there
    break;

    case 'o':
    if (angle >= 0 && angle <= 180) {
      angle = angle + angleStep;
      if(angle >180){
        angle =180;
       }else{
          myservo5.write(angle); // move the servo to desired angle
       }
    }
    
    delay(100); // waits for the servo to get there
    break;

   }  
}
