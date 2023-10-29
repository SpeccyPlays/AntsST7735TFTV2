#ifndef ANTAUTOMA_H   /* Include guard */
#define ANTAUTOMA_H
#include <Arduino.h>
#include "CoOrds.h"
/*
This is the class for a single ant in the system
*/
enum state {WANDER = 0, SEEK = 1};
class Ant {
    int16_t screenWidth = 160;
    int16_t screenHeight = 128;
    int8_t maxSpeed = 10;
    int8_t maxForce = 2;
    public :
    void resetAnt(uint16_t screenWidth, uint16_t screenHeight, byte velocity);
    int16_t getCurrentX();
    int16_t getCurrentY();
    int16_t getOldX();
    int16_t getOldY();
    float getAngle();
    CoOrds normalise(CoOrds temp);
    CoOrds setDesired(int16_t x, int16_t y);
    void calculateVelocties();
    void steering();
    void moveAnt();
    ;
    private :
    CoOrds currentPos;//where we're at now
    CoOrds oldPos;//used to remove ant from screen
    CoOrds desired;//where we want to go
    float angle;//uses radians
    CoOrds velocity;
    CoOrds desiredVelocity;
    CoOrds steeringForce;
    state antState;
    float angleBetweenTwoPoints(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
    ;
};

#endif