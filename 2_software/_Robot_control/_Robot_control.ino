#include <AFMotor.h>
#include <IRremote.h>
#include "MotorControl.h"

/*-----------------------------------------------------------------

  Description des moteurs :
  AF_DCMotor frontRight(4,MOTOR34_64KHZ);
  AF_DCMotor frontLeft(1,MOTOR12_64KHZ);
  AF_DCMotor backRight(3,MOTOR34_64KHZ);
  AF_DCMotor backLeft(2,MOTOR12_64KHZ);

  Fonctions à utiliser :
  void resetStateMotors();
  void goForward(uint16_t speed, unsigned long time);
  void goBackward(uint16_t speed, unsigned long time);
  void goRight(uint16_t speed, unsigned long time);
  void goLeft(uint16_t speed, unsigned long time);
  void goDiagRight(uint16_t speed, unsigned long time, String direction);
  void goDiagLeft(uint16_t speed, unsigned long time, String direction);
  void rotate_90(String direction);
  void rotate_dtheta(String direction);

  Description des vitesses
  #define MIN_SPEED     0
  #define TEST_SPEED    150
  #define TURN_SPEED    150
  #define MAX_SPEED     255

  #define STATE_LOCK 500
   -----------------------------------------------------------------
*/
/*changer variable speed dans fonction pour protéger si trop grand
   mode
*/
//#define MODE_DEBUG
#define MODE_MANUEL         /*mode enchainement des commandes hardcodées*/
//#define MODE_TELECOM    /*mode enchainement des commandes recues par la télécommande*/
//#define MODE_JOYSTICK

#define IR_RECEIVER_PIN 10 // define the IR receiver pin

#define button_power 0xFFA25D
#define button_vol_plus 0xFF629D
#define button_0 0xFF6987
#define button_1 0xFF30CF
#define button_2 0xFF18E7
#define button_3 0xFF7A85
#define button_4 0xFF10EF
#define button_5 0xFF38C7
#define button_6 0xFF5AA5
#define button_7 0xFF42BD
#define button_8 0xFF4AB5
#define button_9 0xFF52AD
#define button_vol_moins 0xFFA857
#define button_start_stop 0xFF02FD
#define button_avance_rapide 0xFFC23D
#define button_recule_rapide 0xFF22DD
#define button_haut 0xFF906F
#define button_bas 0xFFE01F
#define button_EQ 0xFF9867
#define button_FUNC_STOP 0xFFE21D
#define button_ST_REPT 0xFFB04F

#define pin_led 9 //attaché à au signal s du header 01x03 "servo_2"

#define pinJoystickX    A0
#define pinJoystickY    A5
#define rotatePin       2
int X, Y;
boolean rotateButtonState;

IRrecv receiver(IR_RECEIVER_PIN); // create a receiver object of the IRrecv class
decode_results motorCommand; // create a results object of the decode_results class


uint16_t motorSpeed = 150;
unsigned long oneDemiSec = 500;
unsigned long oneSec = 1000;
unsigned long dt = 100;

void IRsetup() {
  //receiver.enableIRIn(); // enable the receiver
  receiver.blink13(true); // enable blinking of the built-in LED when an IR signal is received
}


void setup() {
  resetStateMotors();
  //IRsetup();

  pinMode(pin_led, OUTPUT);
  digitalWrite(pin_led, LOW);
  delay(oneSec);
  digitalWrite(pin_led, HIGH);
  delay(oneSec);
  digitalWrite(pin_led, LOW);

  pinMode(pinJoystickX, INPUT);
  pinMode(pinJoystickY, INPUT);
  pinMode(rotateButtonState, INPUT_PULLUP);

}

void loop() {
#ifdef MODE_DEBUG
  //AF_DCMotor frontLeft2(1,MOTOR12_64KHZ);
  AF_DCMotor backLeft2(2, MOTOR12_64KHZ);
  //frontLeft2.setSpeed(motorSpeed);
  backLeft2.setSpeed(motorSpeed);
  //frontLeft2.run(FORWARD);
  backLeft2.run(FORWARD);
#endif


#ifdef MODE_MANUEL


  goForward(motorSpeed, oneSec);
  goRight(motorSpeed, oneSec);
  goBackward(motorSpeed, oneSec);
  goLeft(motorSpeed, oneSec);

#endif

#ifdef MODE_JOYSTICK
  X = map(analogRead(pinJoystickX), 0, 1023, -50, 50);//convertit la plage 0-1023
  Y = map(analogRead(pinJoystickY), 0, 1023, -50, 50);
  rotateButtonState = digitalRead(rotatePin);

  if (X > 25 && abs(Y) < 25) {
    goLeft(motorSpeed, oneSec);
  } else if (X < -25 && abs(Y) < 25) {
    goRight(motorSpeed, oneSec);
  } else if (Y > 25 && abs(X) < 25) {
    goBackward(motorSpeed, oneSec);
  } else if (Y < -25 && abs(X) < 25) {
    goForward(motorSpeed, oneSec);
  } else if (rotateButtonState = LOW) {
    rotate_90("RIGHT");
  }
#endif


#ifdef MODE_TELECOM
  digitalWrite(pin_led, LOW);
  if (receiver.decode(&motorCommand)) { // decode the received signal and store it in results
    //Serial.println(results.value, HEX); // print the values in the Serial Monitor
    receiver.resume(); // reset the receiver for the next code

    switch (motorCommand.value) {
      case button_start_stop :
        resetStateMotors();
        digitalWrite(pin_led, HIGH);
        break;

      case button_vol_plus :
        goForward(motorSpeed, oneSec);
        digitalWrite(pin_led, HIGH);
        break;

      case button_vol_moins :
        goBackward(motorSpeed, oneSec);
        digitalWrite(pin_led, HIGH);
        break;

      case button_avance_rapide :
        goRight(motorSpeed, oneSec);
        digitalWrite(pin_led, HIGH);
        break;

      case button_recule_rapide :
        goLeft(motorSpeed, oneSec);
        digitalWrite(pin_led, HIGH);
        break;

      case button_power :
        goDiagLeft(motorSpeed, oneSec, "FORWARD");
        digitalWrite(pin_led, HIGH);
        break;

      case button_ST_REPT :
        goDiagLeft(motorSpeed, oneSec, "BACKWARD");
        digitalWrite(pin_led, HIGH);
        break;

      case button_FUNC_STOP :
        goDiagRight(motorSpeed, oneSec, "FORWARD");
        digitalWrite(pin_led, HIGH);
        break;

      case button_0 :
        goDiagRight(motorSpeed, oneSec, "BACKWARD");
        digitalWrite(pin_led, HIGH);
        break;

      case button_EQ :
        rotate_dtheta("RIGHT");
        digitalWrite(pin_led, HIGH);
        break;

      case button_2 :
        rotate_dtheta("LEFT");
        digitalWrite(pin_led, HIGH);
        break;

      case button_9 :
        rotate_90("RIGHT");
        digitalWrite(pin_led, HIGH);
        break;

      case button_haut :
        motorSpeed += 50;
        digitalWrite(pin_led, HIGH);
        break;

      case button_bas :
        motorSpeed -= 50;
        digitalWrite(pin_led, HIGH);
        break;

      case button_7 :
        oneSec -= 100;
        digitalWrite(pin_led, HIGH);
        break;

      case button_8 :
        oneSec += 100;
        digitalWrite(pin_led, HIGH);
        break;

      default :
        resetStateMotors();
        break;
    }
  }
  //previous = results.value;
#endif

}
