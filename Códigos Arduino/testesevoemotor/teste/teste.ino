#include <Servo.h>
#include <math.h>

#include "ESC.h"
#define LED_PIN (13)              // Pin for the LED 
#define PI 3.1415926535897932384626433832795
#define SPEED_MIN (1300)                                  // Set the Minimum Speed in microseconds
#define SPEED_MAX (1800)                                  // Set the Minimum Speed in microseconds

ESC myESC (5, 1000, 2000, 1500);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)
int oESC;                                                 // Variable for the speed sent to the ESC
char dado;
int velocidade;

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

  for (int i = 1; i <= 360; i++) {
    senos[i] = sin(i * PI / 180.0);
    cossenos[i] = cos(i * PI / 180.0);
  }
  servo_inf.write(90.0 + 30.0 * senos[1]);
  servo_sup.write(90.0 + 30.0 * cossenos[1]);
  pinMode(LED_PIN, OUTPUT);       // LED Visual Output
  digitalWrite(LED_PIN, HIGH);    // LED High while signal is High (can be removed)
  delay(2000);
  myESC.calib();
  digitalWrite(LED_PIN, LOW);    // LED High Once Armed
  myESC.arm();                    // Send the Arm value so the ESC will be ready to take commands
  delay(2000);                    // Wait for a while
  velocidade = 1800;
  myESC.speed(velocidade);              // Set the speed to a testing value between 1000 and 2000



}

void loop() {


  for (ang = 0; ang <= 359; ang++) {
    arg_inf = 90.0 + 20.0 * senos[ang + 1];
    arg_sup = 90.0 + 20.0 * cossenos[ang + 1];
    servo_inf.write(arg_inf);
    //  Serial.println(arg_inf);
    servo_sup.write(arg_sup);
    delay(10);
  }



}
