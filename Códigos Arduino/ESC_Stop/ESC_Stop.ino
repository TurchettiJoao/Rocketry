/*
  ESC_Stop
    This is to illustrate the "stop" command that can be use. It will send a 500us value which in most cases will stop the motor.
    If another value is needed, it can be changed in the library ESC.h under "ESC_STOP_PULSE"

  27 April 2017
  by Eric Nantel
*/
#include "ESC.h"
#define LED_PIN (13)              // Pin for the LED 

ESC myESC (5, 1000, 2000, 1500);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)
int oESC;                                                 // Variable for the speed sent to the ESC

#define SPEED_MIN (1300)                                  // Set the Minimum Speed in microseconds
#define SPEED_MAX (1800)                                  // Set the Minimum Speed in microseconds

char dado;
int velocidade;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);       // LED Visual Output
  delay(2000);
  digitalWrite(LED_PIN, HIGH);    // LED High while signal is High (can be removed)
  myESC.calib();
  digitalWrite(LED_PIN, LOW);    // LED High Once Armed
  myESC.arm();                    // Send the Arm value so the ESC will be ready to take commands
  delay(1000);                    // Wait for a while
  velocidade = 1500;
  myESC.speed(velocidade);              // Set the speed to a testing value between 1000 and 2000
}

void loop() {
  /*if (Serial.available() > 0) {
    dado = Serial.read();
    if (dado == '+') {
      velocidade = velocidade + 50;
      myESC.speed(velocidade);
    }
    else if (dado == '-') {
      velocidade = velocidade - 50;
      myESC.speed(velocidade);
    }
    }
    Serial.println(velocidade);*/

  for (oESC = SPEED_MIN; oESC <= SPEED_MAX; oESC += 1) {  // goes from 1000 microseconds to 2000 microseconds
    myESC.speed(oESC);                                    // tell ESC to go to the oESC speed value
    delay(10);                                            // waits 10ms for the ESC to reach speed
  }
  delay(1000);
  for (oESC = SPEED_MAX; oESC >= SPEED_MIN; oESC -= 1) {  // goes from 2000 microseconds to 1000 microseconds
    myESC.speed(oESC);                                    // tell ESC to go to the oESC speed value
    delay(10);                                            // waits 10ms for the ESC to reach speed
  }
  delay(1000);                                            // Wait for a while befor restart

}
