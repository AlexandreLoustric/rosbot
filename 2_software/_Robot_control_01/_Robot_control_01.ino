#include <AFMotor.h>
#include <IRremote.h>

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
   -----------------------------------------------------------------
*/
/*changer variable speed dans fonction pour protéger si trop grand
   mode
*/
#define MIN_SPEED     0
#define TEST_SPEED    150
#define TURN_SPEED    150
#define MAX_SPEED     255

#define STATE_LOCK 500

#define IR_RECEIVER_PIN 2 // define the IR receiver pin

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


AF_DCMotor frontRight(4,MOTOR34_64KHZ); 
AF_DCMotor frontLeft(1,MOTOR12_64KHZ);
AF_DCMotor backRight(3,MOTOR34_64KHZ); 
AF_DCMotor backLeft(2,MOTOR12_64KHZ);

//IRrecv receiver(IR_RECEIVER_PIN); // create a receiver object of the IRrecv class
decode_results motorCommand; // create a results object of the decode_results class

uint16_t motorSpeed = 150;
unsigned long oneDemiSec = 500;
unsigned long oneSec = 1000;


void setup() {
  resetStateMotors();

  IRsetup();

  pinMode(pin_led, OUTPUT);
  digitalWrite(pin_led, LOW);
  delay(oneSec);
  digitalWrite(pin_led, HIGH);
  delay(oneSec);
  digitalWrite(pin_led, LOW);

  goForward(motorSpeed, oneSec);

  
}

void loop() {
/*
 *  if (IrReceiver.decode()) {
    IrReceiver.resume();
    int command = IrReceiver.decodedIRData.command;
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

      default :
        resetStateMotors();
        break;
      }
    }*/
  
/*
  goForward(motorSpeed, oneSec);
  goRight(motorSpeed, oneSec);
  goBackward(motorSpeed, oneSec);
  goLeft(motorSpeed, oneSec);*/
  
}

void IRsetup() {
  //receiver.enableIRIn(); // enable the receiver
  IrReceiver.begin(IR_RECEIVER_PIN);
  IrReceiver.blink13(true); // enable blinking of the built-in LED when an IR signal is received
}


void resetStateMotors(){
  frontRight.setSpeed(0);
  frontRight.run(RELEASE);
  frontLeft.setSpeed(0);
  frontLeft.run(RELEASE);
  backRight.setSpeed(0);
  backRight.run(RELEASE);
  backLeft.setSpeed(0);
  backLeft.run(RELEASE);
  delay(STATE_LOCK);
}

void goForward(uint16_t speed, unsigned long time){
  frontRight.setSpeed(speed);
  frontLeft.setSpeed(speed);
  backRight.setSpeed(speed);
  backLeft.setSpeed(speed);
  frontRight.run(FORWARD);
  frontLeft.run(FORWARD);
  backRight.run(FORWARD);
  backLeft.run(FORWARD);
  
  delay(time);
  resetStateMotors();
  
  delay(STATE_LOCK);
}

void goBackward(uint16_t speed, unsigned long time){
  frontRight.setSpeed(speed);
  frontLeft.setSpeed(speed);
  backRight.setSpeed(speed);
  backLeft.setSpeed(speed);
  frontRight.run(BACKWARD);
  frontLeft.run(BACKWARD);
  backRight.run(BACKWARD);
  backLeft.run(BACKWARD);
  
  delay(time);
  resetStateMotors();
  
  delay(STATE_LOCK);
}

/* Translation vers la droite */
void goRight(uint16_t speed, unsigned long time){
  frontRight.setSpeed(speed);
  frontLeft.setSpeed(speed);
  backRight.setSpeed(speed);
  backLeft.setSpeed(speed);
  frontRight.run(BACKWARD);
  frontLeft.run(FORWARD);
  backRight.run(FORWARD);
  backLeft.run(BACKWARD);
  
  delay(time);
  resetStateMotors();
  
  delay(STATE_LOCK);
}

/* Translation vers la gauche */
void goLeft(uint16_t speed, unsigned long time){
  frontRight.setSpeed(speed);
  frontLeft.setSpeed(speed);
  backRight.setSpeed(speed);
  backLeft.setSpeed(speed);
  frontRight.run(FORWARD);
  frontLeft.run(BACKWARD);
  backRight.run(BACKWARD);
  backLeft.run(FORWARD);
  
  delay(time);
  resetStateMotors();
  
  delay(STATE_LOCK);
}

void goDiagRight(uint16_t speed, unsigned long time, String direction){
  if(direction.equals("FORWARD")){
    frontRight.setSpeed(0);
    frontLeft.setSpeed(speed);
    backRight.setSpeed(speed);
    backLeft.setSpeed(0);
    frontRight.run(RELEASE);
    frontLeft.run(FORWARD);
    backRight.run(FORWARD);
    backLeft.run(RELEASE);
  }else if (direction.equals("BACKWARD")){
    frontRight.setSpeed(0);
    frontLeft.setSpeed(speed);
    backRight.setSpeed(speed);
    backLeft.setSpeed(0);
    frontRight.run(RELEASE);
    frontLeft.run(BACKWARD);
    backRight.run(BACKWARD);
    backLeft.run(RELEASE);
  }else{
    resetStateMotors();
  }

  delay(time);
  resetStateMotors();
  
  delay(STATE_LOCK);
}

void goDiagLeft(uint16_t speed, unsigned long time, String direction){
  if(direction.equals("FORWARD")){
    frontRight.setSpeed(speed);
    frontLeft.setSpeed(0);
    backRight.setSpeed(0);
    backLeft.setSpeed(speed);
    frontRight.run(FORWARD);
    frontLeft.run(RELEASE);
    backRight.run(RELEASE);
    backLeft.run(FORWARD);
  }else if (direction.equals("BACKWARD")){
    frontRight.setSpeed(speed);
    frontLeft.setSpeed(0);
    backRight.setSpeed(0);
    backLeft.setSpeed(speed);
    frontRight.run(BACKWARD);
    frontLeft.run(RELEASE);
    backRight.run(RELEASE);
    backLeft.run(BACKWARD);
  }else{
    resetStateMotors();
  }

  delay(time);
  resetStateMotors();
  
  delay(STATE_LOCK);
}

/* Effectue une rotation de 90° selon l'axe z */
void rotate_90(String direction){
  frontRight.setSpeed(TURN_SPEED);
  frontLeft.setSpeed(TURN_SPEED);
  backRight.setSpeed(TURN_SPEED);
  backLeft.setSpeed(TURN_SPEED);
  
  if(direction.equals("RIGHT")){
    frontRight.run(BACKWARD);
    frontLeft.run(FORWARD);
    backRight.run(BACKWARD);
    backLeft.run(FORWARD);
  }else if(direction.equals("LEFT")){
    frontRight.run(FORWARD);
    frontLeft.run(BACKWARD);
    backRight.run(FORWARD);
    backLeft.run(BACKWARD);
  }else{
    resetStateMotors();
  }
  
  unsigned long const_timeTo90 = 1200;
  delay(const_timeTo90);
  resetStateMotors();
  
  delay(STATE_LOCK);
}

/* Effectue une rotation de dtheta selon l'axe z. A répéter pour avoir la rotation voulue */
void rotate_dtheta(String direction){
  frontRight.setSpeed(TURN_SPEED);
  frontLeft.setSpeed(TURN_SPEED);
  backRight.setSpeed(TURN_SPEED);
  backLeft.setSpeed(TURN_SPEED);
  
  if(direction.equals("RIGHT")){
    frontRight.run(BACKWARD);
    frontLeft.run(FORWARD);
    backRight.run(BACKWARD);
    backLeft.run(FORWARD);
  }else if(direction.equals("LEFT")){
    frontRight.run(FORWARD);
    frontLeft.run(BACKWARD);
    backRight.run(FORWARD);
    backLeft.run(BACKWARD);
  }else{
    resetStateMotors();
  }
  
  unsigned long const_dt = 300;
  delay(const_dt);
  resetStateMotors();
  
  delay(STATE_LOCK);
}
