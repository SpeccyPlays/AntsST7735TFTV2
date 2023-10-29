#include <Arduino.h>
#include "AntAutoma.h"

void Ant::resetAnt(uint16_t screenWidth, uint16_t screenHeight, byte velocity){
    this->currentPos.x = screenWidth; //random(10, screenWidth - 10);
    this->currentPos.y = screenHeight;//random(10, screenHeight - 10);
    this->angle = random(360) * PI / 180.0;//convert to radians don't forget
    this->antState = WANDER;
    this->velocity.x = 2;
    this->velocity.y = 2;
    this->desired.x = screenWidth /2;
    this->desired.y = screenHeight /2;
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
void Ant::wandering(){
    int16_t tempY = currentPos.y; 
    tempY += ((velocity.y + 4) * sin(angle));
    int16_t tempX = currentPos.x; 
    tempX += ((velocity.x + 4) * cos(angle));
    float randAngle = random(360) * PI / 180.0;
    uint8_t randomDistance = random(5 * 100) / 100;
    tempX += randomDistance * cos(randAngle);
    tempY += randomDistance * sin(randAngle);
    setDesired(tempX, tempY);
}
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
    if (currentPos.x < 0){
        currentPos.x = screenWidth;
    }
    else if (currentPos.x > screenWidth){
        currentPos.x = 0;
    }
    if (currentPos.y < 0){
        currentPos.y = screenHeight;
    }
    else if (currentPos.y > screenHeight){
        currentPos.y = 0;
    }
    wandering();
    steering();
    currentPos.x += velocity.x;
    currentPos.y += velocity.y;
};
float Ant::angleBetweenTwoPoints(int16_t x1, int16_t y1, int16_t x2, int16_t y2){
    double angle = atan2(y2 - y1, x2 - x1);
    if (angle < 0.0){
        angle += 3.14 * 2;
    }
    return angle;
};
int16_t Ant::getCurrentX(){
    return this->currentPos.x;
};
int16_t Ant::getCurrentY(){
    return this->currentPos.y;
};
int16_t Ant::getOldX(){
    return this->oldPos.x;
};
int16_t Ant::getOldY(){
    return this->oldPos.y;
};
float Ant::getAngle(){
    return this->angle;
};
