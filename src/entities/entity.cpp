#include "stdpch.hpp"

#include <cfloat>
#include "level.hpp"
#include "entity.hpp"
#include "othermath.h"
#include "log.hpp"
#include "level.hpp"
//#include <cmath>
//#include <algorithm>
//#include <iostream>

bool windowContains(sf::View view, sf::Sprite sprite);

Entity::Entity(sf::Vector2f position, sf::Vector2u size, sf::Texture* texture, Level* level, unsigned int hitPoints)
: velocity(0,0)
, collisionRect(position.x, position.y, size.x, size.y)
, sprite()
, isDead(false)
, hitPoints(hitPoints)
, level(level) {
    if(texture != nullptr) {
        sprite.setTexture(*texture);
    }
    setOrigin(sf::Vector2f(size.x/2, size.y/2));
    setPosition(position);
}

Entity::Entity(float x, float y, unsigned int w, unsigned int h, sf::Texture* texture, Level* level, unsigned int hitPoints)
: velocity(0,0)
, collisionRect(x,y,w,h)
, sprite()
, isDead(false)
, hitPoints(hitPoints)
, level(level) {
    if(texture != nullptr) {
        sprite.setTexture(*texture);
    }
    setOrigin(sf::Vector2f(w/2, h/2));
    setPosition(x,y);
}

Entity::~Entity() {

}

void Entity::update(sf::Time frameTime) {
    move(velocity * frameTime.asSeconds());
    collisionRect.left = getPosition().x;
    collisionRect.top = getPosition().y;
    if(animation.getTexture() != nullptr) {
        animation.update(frameTime);
        sprite.setTextureRect(animation.getCurrentCellRect());
    }
    
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform(); // will apply all transformations on the entity to the sprite when it is drawn


    //if(windowContains(target.getView(), sprite)) {
        target.draw(sprite, states);
    //}

}

void Entity::face(sf::Vector2f position){
    setRotation(calculateAngleTo(position) - 90); // minus 90 degrees because SFML assumes a different direction is 0
}

float Entity::calculateAngleTo(sf::Vector2f otherPosition){
    sf::Vector2f temp;
    sf::Vector2f thisPosition = getPosition();
    temp.x = thisPosition.x - otherPosition.x;
    temp.y = thisPosition.y - otherPosition.y;
    float newAngle;
    if(temp.x == 0) temp.x += FLT_MIN;
    if(temp.y == 0) temp.y += FLT_MIN;
    if(temp.x != 0 && temp.y != 0) {
        newAngle = radiansToDegrees(atanf((temp.y) / (temp.x)));
        if(otherPosition.x > thisPosition.x){
            newAngle += 180;    
        } 
    } else {
        if(temp.x > 0) {
            newAngle = 300;
        }
    }
    return newAngle;
}

void Entity::setVelocity(sf::Vector2f newVelocity) {
    velocity = newVelocity;
}

void Entity::accelerate(sf::Vector2f newVelocity) {
    velocity += newVelocity;
}

void Entity::limitVelocity(const unsigned int MAX_SPEED) {

    // Let m be the allowed maximum speed and v=(v₁,v₂) be the current velocity. 
    // Calculate |v|² = v₁² + v₂² and check if |v²| > m². If so set
    // v₁ ← m/|v| · v₁
    // v₂ ← m/|v| · v₂
    float velocityMagnitude = sqrtf(powf(velocity.x, 2) + powf(velocity.y, 2));
    if(powf(velocityMagnitude, 2) > powf((float)MAX_SPEED, 2)) {
        velocity.x = MAX_SPEED / velocityMagnitude * velocity.x;
        velocity.y = MAX_SPEED / velocityMagnitude * velocity.y;
    }
}

sf::Vector2f Entity::getVelocity() {
    return velocity;
}

sf::Vector2u Entity::getSize() {
    sf::IntRect rect = sprite.getTextureRect();
    return sf::Vector2u(rect.width, rect.height);
}

Level* Entity::getLevel() {
    return level;
}

sf::FloatRect Entity::getCollisionRect() {
    return collisionRect;
}

bool Entity::windowContains(sf::View view, sf::Sprite sprite) const {
    if(sprite.getPosition().x > -100 + view.getCenter().x - view.getSize().x / 2 && sprite.getPosition().x < 100 + view.getCenter().x + view.getSize().x / 2 &&
       sprite.getPosition().y > -100 + view.getCenter().y - view.getSize().y / 2 && sprite.getPosition().y < 100 + view.getCenter().y + view.getSize().y / 2){
        return true;
    }
        
    return false;
}

void Entity::setAnimation(Animation newAnimation){
    animation = newAnimation;
    sprite.setTexture(*animation.getTexture());
    sprite.setTextureRect(animation.getCurrentCellRect());
}

unsigned int Entity::getHitpoints() {
    return hitPoints;
}

void Entity::setTexture(sf::Texture* texture) {
    sprite.setTexture(*texture);
}

void Entity::repair(unsigned int hitPoints) {
    if(this->hitPoints - hitPoints >= 0) {
        this->hitPoints -= hitPoints;
    }
}

void Entity::damage(unsigned int hitPoints) {
    if(this->hitPoints - hitPoints <= 0) {
        this->hitPoints = 0;
        destroy();
    }
    else if(this->hitPoints - hitPoints > 0) {
        this->hitPoints -= hitPoints;
    }
}

void Entity::setHitpoints(unsigned int hitPoints) {
    this->hitPoints = hitPoints;
}

void Entity::destroy() {
    hitPoints = 0;
    isDead = true;
}

bool Entity::isDestroyed() {
    return isDead;
}

void Entity::revive(){
    this->isDead = false;
}

void Entity::setLevel(Level* level){
    this->level = level;
}