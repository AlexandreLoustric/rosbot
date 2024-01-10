#include <Stepper.h>
double stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);  // Pin inversion to make the library work 
/*on vient d'indiquer que pour myStepper, un tour sera 2048 pas donc la commande myStepper.step(2*2048) lui fera faire deux tours*/

void setup(){
  myStepper.setSpeed(19);    //pour définir le nombre de tours par minute --> Ne peut pas aller au dela de 18 tours par minute
  Serial.begin(9600);
}
 
void loop(){  
  // 1 rotation counterclockwise:  
  Serial.println("counterclockwise");    
  myStepper.step(2*stepsPerRevolution);  
  delay(1000);
    
  // 1 rotation clockwise: 
  Serial.println("clockwise");  
  myStepper.step(-stepsPerRevolution);
  delay(1000);
}

/*Conclusion : je ne sais pas si le moteur pas à pas pourra être utile dans le projet à voir, j'aurais au moins vu comment il marche
