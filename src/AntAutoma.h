#ifndef ANTAUTOMA_H   /* Include guard */
#define ANTAUTOMA_H
#include <Arduino.h>
#include "CoOrds.h"
/*
This is the class for a single ant in the system
*/
enum state {WANDER = 0};
class Ant {
    int16_t screenWidth = 160;
    int16_t screenHeight = 128;
    public :
    void resetAnt(uint16_t screenWidth, uint16_t screenHeight, byte velocity);
    int16_t getCurrentX();
    int16_t getCurrentY();
    int16_t getOldX();
    int16_t getOldY();
    float getAngle();
    void moveAnt();
    ;
    private :
    CoOrds currentPos;//where we're at now
    CoOrds oldPos;//used to remove ant from screen
    float angle;//uses radians so 0 - 6.26 roughly
    byte velocity;
    state antState;
    float angleBetweenTwoPoints(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
    ;
};

#endif