#include <Servo.h>
Servo s;
#define pinX    A0
#define pinY    A5
#define swPin    2
bool button_state;
int angle_servo = 0 ;

void setup() {
  //s.attach(3);
  //s.write(angle_servo);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  //pinMode(swPin, INPUT);
//  digitalWrite(swPin, HIGH);

  Serial.begin(9600);
  Serial.println("X   Y   boutton");
}

void loop() {
  //boolean button_state = digitalRead(swPin);
  int X = map(analogRead(pinX),0,1023,-50,50);
  int Y = map(analogRead(pinY),0,1023,-50,50);

  //angle_servo = map(X, 0, 1023, 0, 180);//convertit la place 0-1023 en 0-180
  //s.write(angle_servo);
  Serial.print("Valeur en X : ");
  Serial.println(X);
  Serial.print("Valeur en Y : ");
  Serial.println(Y);

  delay(1500);
  
  
 /*
  Serial.print(X);
  Serial.print("  ");
  Serial.print(Y);
  Serial.print("  ");
  Serial.println(button_state);*/
  
  
  

}
