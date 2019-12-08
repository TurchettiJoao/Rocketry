#include <Servo.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795

Servo servo_sup;  // create servo object to control a servo
Servo servo_inf;  // create servo object to control a servo

// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int ang = 0;
float senos[360];
float cossenos[360];
float arg_inf;
float arg_sup;

void setup() {
  Serial.begin(9600);

  servo_sup.attach(7);  // attaches the servo on pin 6 to the servo object
  servo_inf.attach(6);  // attaches the servo on pin 5 to the servo object
  pinMode(5, OUTPUT);  // sets the ESC pin as output

  for (int i = 1; i <= 360; i++) {
    senos[i] = sin(i * PI / 180.0);
    cossenos[i] = cos(i * PI / 180.0);
  }
  servo_inf.write(90.0 + 30.0 * senos[1]);
  servo_sup.write(90.0 + 30.0 * cossenos[1]);
  analogWrite(5, 255);
  delay(5000);
  for (int k = 1; k <= 255; k++){
    analogWrite(5, 255-k); 
    Serial.println(255-k);
    delay(5);   
  }
  analogWrite(5, 0);
  delay(5000);
    analogWrite(5, 50);

}

void loop() {

  /* for (pos = 70; pos <=110; pos += 1) { // goes from 0 degrees to 180 degrees
     // in steps of 1 degree
    servo_inf.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15ms for the servo to reach the position
     }
     for (pos = 110; pos >= 70; pos -= 1) { // goes from 180 degrees to 0 degrees
     servo_inf.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15ms for the servo to reach the position
     }*/

  /*    for (pos = 70; pos <=110; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo_sup.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 110; pos >= 70; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo_sup.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    }*/

  for (ang = 0; ang <= 359; ang++) {
    arg_inf = 90.0 + 20.0 * senos[ang + 1];
    arg_sup = 90.0 + 20.0 * cossenos[ang + 1];
    servo_inf.write(arg_inf);
    //  Serial.println(arg_inf);
    servo_sup.write(arg_sup);
    delay(5);
  }
  /* servo_inf.write(90);
     servo_sup.write(90);*/


}
