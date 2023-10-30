#include <Arduino.h>
#include "AntAutoma.h"

void Ant::resetAnt(uint16_t screenWidth, uint16_t screenHeight, byte velocity){
    this->currentPos.x = random(boundary, screenWidth - boundary); //random(10, screenWidth - 10);
    this->currentPos.y = random(boundary, screenHeight = boundary);//random(10, screenHeight - 10);
    this->angle = random(360) * PI / 180.0;//convert to radians don't forget
    this->antState = WANDER;
    this->velocity.x = velocity;
    this->velocity.y = velocity;
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
void Ant::setAvoidPos(int16_t x, int16_t y){
    avoidPos.x = x;
    avoidPos.y = y;
};
CoOrds Ant::setMagnitude(CoOrds temp, int8_t newMag){
    float length = sqrt((temp.x * temp.x + temp.y * temp.y));
    if (length != 0){
        temp.x =  (temp.x / length) * newMag;
        temp.y = (temp.y / length) * newMag;
    }
    return temp;
};
uint8_t Ant::detectCollision(int16_t x, int16_t y, uint8_t r){
  /*
  Check if we're in the circle of x and y
  Including the radius as there's a different range for if we hit another ant or desired location
  */
  int16_t xx = x - currentPos.x;
  int16_t yy = y - currentPos.y;
  if ((( xx * xx) + (yy * yy)) < (r * r) ){
    return 1;
  }
  else {
    return 0;
  }
};
void Ant::slowDown(){
    /*
    Slow down if we're nearing the desired target
    */
    if(detectCollision(desired.x, desired.y, collisionDetectRadius)){
        if (velocity.x != 0){
            velocity.x /= 2;
        }
        if (velocity.y != 0){
            velocity.y /= 2;
        }
    }
};
void Ant::avoiding(){
    if (detectCollision(avoidPos.x, avoidPos.y, antDetectRadius)){
        velocity.x += 1;
        velocity.y += 1;
    }
};
void Ant::seeking(int16_t x, int16_t y){
    setDesired(x, y);
};
void Ant::wandering(){
    /*
    Go to a point in front of the ant
    Pick a random point on a circle from there
    Set that to where the ant wants to head towards
    Makes the movement look more natural

    */
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
    Set the desired velocity to the amount we need to move to desired
    Reduce the magnitude or it'll go straight there
    Limit the velocity for the same reason 
    (I think for the last two)
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
    /*
    How much the ant will turn towards it's desired destination
    Use the class maxforce value to limit or increase the turning force
    */
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
    Check boundaries first, see what state it's in, then do everything needed to move
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
        slowDown();
        break;
        case AVOID :
        avoiding();
        wandering();
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
