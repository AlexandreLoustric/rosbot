#include <Arduino.h>

void resetStateMotors();

void goForward(uint16_t speed, unsigned long time);

void goBackward(uint16_t speed, unsigned long time);

void goRight(uint16_t speed, unsigned long time);

void goLeft(uint16_t speed, unsigned long time);

void goDiagRight(uint16_t speed, unsigned long time, String direction);

void goDiagLeft(uint16_t speed, unsigned long time, String direction);

void rotate_90(String direction);

void rotate_dtheta(String direction);
