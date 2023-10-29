#include <Arduino.h>
#include "AntAutoma.h"

void Ant::resetAnt(uint16_t screenWidth, uint16_t screenHeight, byte velocity){
    this->currentPos.x = screenWidth /2; //random(10, screenWidth - 10);
    this->currentPos.y = screenHeight / 2;//random(10, screenHeight - 10);
    this->angle = random(360) * PI / 180.0;//convert to radians don't forget
    this->antState = WANDER;
    this->velocity = velocity;
};
void Ant::moveAnt(){
    /*
    Find a point double the velocity of the ant
    Generate a random angle between 1-6
    Move temp x and y to that spot
    Find the angle from ant to that spot

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
    int16_t tempY = currentPos.y; 
    tempY += ((velocity*2) * sin(angle));
    int16_t tempX = currentPos.x; 
    tempX += ((velocity*2) * cos(angle));
    /*
    Thank you chatgpt for the below to pick a random point on a circle
    */
    float randAngle = random(360) * PI / 180.0;
    uint8_t randomDistance = random(2, 6);
    tempX = tempX + randomDistance * cos(randAngle);
    tempY = tempY + randomDistance * sin(randAngle);
    float tempAngle = angleBetweenTwoPoints(currentPos.x, currentPos.y, tempX, tempY);
    angle = tempAngle;
    currentPos.y += velocity * sin(angle);
    currentPos.x += velocity * cos(angle);
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
