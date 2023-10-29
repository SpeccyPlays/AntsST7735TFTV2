#include <Arduino.h>
#include "AntAutoma.h"

void Ant::resetAnt(uint16_t screenWidth, uint16_t screenHeight, byte velocity){
    this->currentPos.x = random(boundary, screenWidth - boundary); //random(10, screenWidth - 10);
    this->currentPos.y = random(boundary, screenHeight = boundary);//random(10, screenHeight - 10);
    this->angle = random(360) * PI / 180.0;//convert to radians don't forget
    this->antState = WANDER;
    this->velocity.x = 2;
    this->velocity.y = 2;
    this->desired.x = screenWidth /2;
    this->desired.y = screenHeight /2;
};
void Ant::setState(state newState){
    antState = newState;
};
void Ant::setDesired(int16_t x, int16_t y){
    desired.x = x;
    desired.y = y;
};
CoOrds Ant::setMagnitude(CoOrds temp, int8_t newMag){
    float length = sqrt((temp.x * temp.x + temp.y * temp.y));
    if (length != 0){
        temp.x =  (temp.x / length) * newMag;
        temp.y = (temp.y / length) * newMag;
    }
    return temp;
};
void Ant::seeking(int16_t x, int16_t y){
    setDesired(x, y);
};
void Ant::wandering(){
    int16_t tempX = currentPos.x + velocity.x * wanderingDistance;
    int16_t tempY = currentPos.y + velocity.y * wanderingDistance;
    float randAngle = random(360) * PI / 180.0;
    uint8_t randomDistance = random(10, 30);
    tempX += randomDistance * cos(randAngle);
    tempY += randomDistance * sin(randAngle);
    setDesired(tempX, tempY);
};
void Ant::calculateVelocties(){
    /*
    
    */
    desiredVelocity.x = (desired.x - currentPos.x);
    desiredVelocity.y = (desired.y - currentPos.y);
    desiredVelocity = setMagnitude(desiredVelocity, maxSpeed);
    desiredVelocity.x *= maxSpeed;
    desiredVelocity.y *= maxSpeed;
    if (desiredVelocity.x > maxSpeed){
        desiredVelocity.x = maxSpeed;
    }
    else if (desiredVelocity.x < -maxSpeed){
        desiredVelocity.x = -maxSpeed;
    }
    if (desiredVelocity.y > maxSpeed){
        desiredVelocity.y = maxSpeed;
    }
    else if(desiredVelocity.y < -maxSpeed){
        desiredVelocity.y = -maxSpeed;
    }
};
void Ant::steering(){
    calculateVelocties();
    steeringForce.x = desiredVelocity.x - velocity.x;
    steeringForce.y = desiredVelocity.y - velocity.y;

    if (steeringForce.x > maxForce){
        steeringForce.x = maxForce;
    }
    else if (steeringForce.x < -maxForce){
        steeringForce.x = -maxForce;
    }
    if (steeringForce.y > maxForce){
        steeringForce.y = maxForce;
    }
    else if (steeringForce.y < -maxForce){
        steeringForce.y = -maxForce;
    }
    velocity.x += steeringForce.x;
    velocity.y += steeringForce.y;
};
void Ant::moveAnt(){
    /*

    */
    oldPos.x = currentPos.x;
    oldPos.y = currentPos.y;
    if (currentPos.x < boundary){
        velocity.x += 2;
    }
    else if (currentPos.x > screenWidth - boundary){
        velocity.x -= 2;
    }
    if (currentPos.y < boundary){
        velocity.y += 2;
    }
    else if (currentPos.y > screenHeight - boundary){
        velocity.y -= 2;
    }
    switch(antState){
        case WANDER :
        wandering();
        break;
        case SEEK :
        break;
    }
    steering();
    currentPos.x += velocity.x;
    currentPos.y += velocity.y;
};
int16_t Ant::getCurrentX(){
    return currentPos.x;
};
int16_t Ant::getCurrentY(){
    return currentPos.y;
};
int16_t Ant::getOldX(){
    return oldPos.x;
};
int16_t Ant::getOldY(){
    return oldPos.y;
};
int16_t Ant::getDesiredX(){
    return desired.x;
};
int16_t Ant::getDesiredY(){
    return desired.y;
};
