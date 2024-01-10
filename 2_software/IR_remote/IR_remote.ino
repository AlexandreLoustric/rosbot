/*https://www.volta.ma/comment-utiliser-un-recepteur-ir-et-une-telecommande-avec-arduino/arduino/#:~:text=Le%20r%C3%A9cepteur%20est%20construit%20de,Arduino)%20o%C3%B9%20il%20est%20d%C3%A9cod%C3%A9.
 * */
#include <IRremote.h> // include the IRremote library

#define RECEIVER_PIN 2 // define the IR receiver pin

#define button_power 0xFFA25D
#define button_vol_plus 0xFF629D
#define button_0 FF6987
#define button_1 FF30CF
#define button_2 FF18E7
#define button_3 FF7A85
#define button_4 FF10EF
#define button_5 FF38C7
#define button_6 FF5AA5
#define button_7 FF42BD
#define button_8 FF4AB5
#define button_9 FF52AD
#define button_vol_moins FFA857
#define button_start_stop FF02FD
#define button_avance_rapide FFC23D
#define button_recule_rapide FF22DD
#define button_haut FF906F
#define button_bas FFE01F
#define button_EQ FF9867
#define button_FUNC_STOP FFE21D
#define button_ST_REPT FFB04F

IRrecv receiver(RECEIVER_PIN); // create a receiver object of the IRrecv class
decode_results results; // create a results object of the decode_results class

unsigned long previous = 0;


#define pin_led 4
bool state_led = false;

void setup() {
  Serial.begin(9600); // begin serial communication with a baud rate of 9600

  receiver.enableIRIn(); // enable the receiver
  receiver.blink13(true); // enable blinking of the built-in LED when an IR signal is received

  pinMode(pin_led, OUTPUT);
  digitalWrite(pin_led, LOW);

}

void loop() {
  if (receiver.decode(&results)) { // decode the received signal and store it in results
    Serial.println(results.value, HEX); // print the values in the Serial Monitor
    receiver.resume(); // reset the receiver for the next code

    switch (results.value) {
      case button_power :
        state_led = !state_led;
        Serial.println(state_led);
        digitalWrite(pin_led, state_led);
        break;

      case button_vol_plus :
        String vol_plus = "VOL+";
        Serial.println(vol_plus);
        break;
    }

    previous = results.value;

  }
}


/* Table de conversion (tout est en 0x)

    0   FF6987
    1   FF30CF
    2   FF18E7
    3   FF7A85
    4   FF10EF
    5   FF38C7
    6   FF5AA5
    7   FF42BD
    8   FF4AB5
    9   FF52AD
    power    FFA25D
    vol+    FF629D
    vol-    FFA857
    start/stop    FF02FD
    avance rapide   FFC23D
    recul rapide    FF22DD
    haut    FF906F
    bas   FFE01F
    EQ    FF9867
    FUNC/STOP   FFE21D
    ST/REPT   FFB04F


    Problème de fiabilité : quand on appuie plus de 4 fois sur la même touche; le receveur recoit une mauvaise information.
    Il vaut aussi mieux éviter de rester appuyer trop longtemps sur la même touche mais peut ce régler par un délai
*/
