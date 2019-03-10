#include <cfloat>
#include "level.hpp"
#include "entity.hpp"
#include "othermath.h"
#include "log.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

Entity::Entity(sf::Vector2f position, sf::Vector2f size, Level* level)
: position(position.x,position.y)
, size(size.x, size.y)
, collisionBox(position.x, position.y, size.x, size.y)
, animation()
{
    this->level = level;
}

Entity::Entity(float x, float y, unsigned int w, unsigned int h, Level* level)
: position(x,y)
, size(w,h)
, collisionBox(x, y, w, h)
, animation()
{
    this->level = level;
}

Entity::~Entity()
{
}

bool windowContains(sf::View view, sf::Sprite sprite){
    if(sprite.getPosition().x > -100 + view.getCenter().x - view.getSize().x / 2 && sprite.getPosition().x < 100 + view.getCenter().x + view.getSize().x / 2 &&
       sprite.getPosition().y > -100 + view.getCenter().y - view.getSize().y / 2 && sprite.getPosition().y < 100 + view.getCenter().y + view.getSize().y / 2){
        return true;
    } else {
        return false;
    }
}

void Entity::draw(sf::RenderWindow* window) { 
    animation.update();
    if(animation.getCurrentTexture() != nullptr){
        sprite.setTexture(*animation.getCurrentTexture());
    }
        
    sprite.setOrigin(size.x / 2, size.y / 2);
    sprite.setPosition(position.x, position.y);
    sprite.setRotation(angle);
    if(windowContains(window->getView(), sprite)){
        window->draw(sprite);
    } else {
    }
    // sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(this->collisionBox.w, this->collisionBox.h));
    // shape.setPosition(this->collisionBox.x, this->collisionBox.y);
    // window->draw(shape);
}

void Entity::face(sf::Vector2f position){
    angle = calculateAngleTo(position) - 90; // minus 90 degrees because SFML assumes a different direction is 0 on the sprite
}

float Entity::calculateAngleTo(sf::Vector2f position){
    sf::Vector2f temp;
    temp.x = this->position.x - position.x;
    temp.y = this->position.y - position.y;
    float newAngle;
    if(temp.x == 0) temp.x += FLT_MIN;
    if(temp.y == 0) temp.y += FLT_MIN;
    if(temp.x != 0 && temp.y != 0) {
        newAngle = radiansToDegrees(atanf((temp.y) / (temp.x)));
        if(position.x > this->position.x){
            newAngle += 180;    
        } 
    } else {
        if(temp.x > 0) {
            newAngle = 300;
        }
    }
    return newAngle;
}

void Entity::setVelocity(sf::Vector2f velocity) {
    // apply the velocity 
    this->velocity.x = velocity.x; 
    this->velocity.y = velocity.y;
   
    // then make sure velocity doesn't exceed MAX_SPEED
    // FORMULA: 
    // Let m be the allowed maximum speed and v=(v₁,v₂) be the current velocity. 
    // Calculate |v|² = v₁² + v₂² and check if |v²| > m². If so set
    // v₁ ← m/|v| · v₁
    // v₂ ← m/|v| · v₂
    float velocityMagnitude = sqrtf(powf(this->velocity.x, 2) + powf(this->velocity.y, 2));
    if(powf(velocityMagnitude, 2) > powf((float)MAX_SPEED, 2)) {
        this->velocity.x = MAX_SPEED / velocityMagnitude * this->velocity.x;
        this->velocity.y = MAX_SPEED / velocityMagnitude * this->velocity.y;
    }
}

void Entity::addVelocity(sf::Vector2f newVelocity) {

    // apply the velocity (added) first
    this->velocity.x += newVelocity.x;
    this->velocity.y += newVelocity.y;

    // then make sure velocity doesn't exceed MAX_SPEED
    // FORMULA: 
    // Let m be the allowed maximum speed and v=(v₁,v₂) be the current velocity. 
    // Calculate |v|² = v₁² + v₂² and check if |v²| > m². If so set
    // v₁ ← m/|v| · v₁
    // v₂ ← m/|v| · v₂
    float velocityMagnitude = sqrtf(powf(this->velocity.x, 2) + powf(this->velocity.y, 2));
    if(powf(velocityMagnitude, 2) > powf((float)MAX_SPEED, 2)) {
        this->velocity.x = MAX_SPEED / velocityMagnitude * this->velocity.x;
        this->velocity.y = MAX_SPEED / velocityMagnitude * this->velocity.y;
    }
    
}

sf::Vector2f Entity::getVelocity() {
    return velocity;
}

Level* Entity::getLevel(){
    return this->level;
}

void Entity::applyMovement(sf::Time frameTime){
    nextPosition.x += velocity.x * frameTime.asSeconds();
    nextPosition.y += velocity.y * frameTime.asSeconds();
    position.x += nextPosition.x;
    position.y += nextPosition.y;
    nextPosition.x = 0;
    nextPosition.y = 0;
    collisionBox.x = position.x;
    collisionBox.y = position.y;
}

sf::Vector2f Entity::getPosition(){
    return this->position;
}

void Entity::setTexture(sf::Texture* texture) {
    if(texture == nullptr) {
        Log::error("Texture pointer not valid. The texture probably wasn't loaded.");
        exit(-1);
    }
    sprite.setTexture(*texture);
}

void Entity::setAnimation(sf::Image image, sf::Vector2u spriteSize, std::vector<int> stateLengths){
    animation.init(image, spriteSize, stateLengths);
}

sf::Vector2u Entity::getSize() {
    return size;
}

void Entity::setState(short state){
    animation.setState(state);
}

void Entity::setDelay(sf::Time delay){
    animation.setDelay(delay);
}