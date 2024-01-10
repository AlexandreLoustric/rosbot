#include <AFMotor.h>


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

AF_DCMotor frontRight(4,MOTOR34_64KHZ); 
AF_DCMotor frontLeft(1,MOTOR12_64KHZ);
AF_DCMotor backRight(3,MOTOR34_64KHZ); 
AF_DCMotor backLeft(2,MOTOR12_64KHZ);

uint16_t motorSpeed = 150;
unsigned long oneDemiSec = 500;
unsigned long oneSec = 1000;


void setup() {
  resetStateMotors();
  
}

void loop() {

  goForward(motorSpeed, oneSec);
  goRight(motorSpeed, oneSec);
  goBackward(motorSpeed, oneSec);
  goLeft(motorSpeed, oneSec);
  
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
