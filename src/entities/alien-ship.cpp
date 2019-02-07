#include "alien-ship.hpp"
#include "random-numbers.hpp"
#include "resources.hpp"
#include <iostream>
#include <iostream>
#include <algorithm>

AlienShip::AlienShip(float x, float y, unsigned int w, unsigned int h, sf::Texture* texture)
: Entity(x,y,w,h)
{
}

AlienShip::AlienShip(float x, float y, unsigned int w, unsigned int h)
: Entity(x,y,w,h)
{
    type = Entity::types::ALIEN_SHIP;
}

AlienShip::~AlienShip()
{

}

void AlienShip::checkCollision(Entity* entity){
    if(entity != this){
        if(collisionBox.intersects(&entity->collisionBox)){
            if(entity->type == Entity::PLAYER_SHIP){
                // entity->damage(damage);
            }
        }
    }
}

void AlienShip::update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities)
{
    updateAI();
    // collision goes here
    for(Entity* entity : entities){
        checkCollision(entity);
    }
    applyMovement(frameTime);
    collisionBox.update(position.x, position.y);
}

void AlienShip::updateAI()
{
    
    switch(state)
    {
        case MOVING:
        movingState();
        break;

        case FIRING:
        firingState();
        break;

        default:
        movingState();
    }
}

void AlienShip::movingState()
{
    if(changeMovementTimer.getElapsedTime() >= CHANGE_MOVEMENT_DELAY)
    {
        switch(Util::GetRandomNumber(0,3))
        {
            case 0:
            // up
            setVelocity(sf::Vector2f(0,-30));
            break;

            case 1:
            // right
            setVelocity(sf::Vector2f(30,0));
            break;

            case 2:
            // down
            setVelocity(sf::Vector2f(0,30));
            break;

            case 3:
            // left
            setVelocity(sf::Vector2f(-30,0));
            break;

            default:
            break;
        }

        changeMovementTimer.restart();
        state = FIRING;
    }
}

void AlienShip::firingState()
{
    fire();
    state = MOVING;
}

// void AlienShip::applyMovement(sf::Time& frameTime)
// {
//     position.x += std::min((float)MAX_SPEED, velocity.x * frameTime.asSeconds());
//     position.y += std::min((float)MAX_SPEED, velocity.y * frameTime.asSeconds());
// }

void AlienShip::fire()
{

}