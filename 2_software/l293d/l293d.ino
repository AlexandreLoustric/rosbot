//Commande d'un moteur avec la puce l293D

#define IN1 2
#define IN2 7
#define EN1 3
/*Si IN1 et HIGH et IN2 LOW le moteur tournera dans un sens et inversement. EN1 est le pwm controlant la vitesse du moteur 1*/
int time_stamp;
int vitesse = 0;

void setup() {

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(EN1,OUTPUT);
  analogWrite(EN1,255);
  Serial.begin(9600);

}

void loop() {
  Serial.println("Début programme...");
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  Serial.println("Augmentation de la vitesse du moteur...");
  while(vitesse<255){
    time_stamp = millis();
    analogWrite(EN1,vitesse);
    if(millis()-time_stamp < 100){
      vitesse+=10;
    }
    
  }
  delay(3000);
  Serial.println("Changement de sens...");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  delay(3000);

}
