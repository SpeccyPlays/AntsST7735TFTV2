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
    int8_t maxSpeed = 4;
    int8_t maxForce = 1;
    int8_t wanderingDistance = 4;
    byte boundary = 5;
    public :
    void resetAnt(uint16_t screenWidth, uint16_t screenHeight, byte velocity);
    int16_t getCurrentX();
    int16_t getCurrentY();
    int16_t getOldX();
    int16_t getOldY();
    int16_t getDesiredX();
    int16_t getDesiredY();
    void setState(state newState);
    void setDesired(int16_t x, int16_t y);
    void seeking(int16_t x, int16_t y);
    void wandering();
    void steering();
    void moveAnt();
    private :
    CoOrds currentPos;//where we're at now
    CoOrds oldPos;//used to remove ant from screen
    CoOrds desired;//where we want to go   
    float angle;//uses radians
    CoOrds velocity;
    CoOrds desiredVelocity;
    CoOrds steeringForce;
    state antState;
    CoOrds setMagnitude(CoOrds temp, int8_t newMag);
    void calculateVelocties();
};

#endif