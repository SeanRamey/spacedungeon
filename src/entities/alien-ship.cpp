#include "alien-ship.hpp"
#include "random-numbers.hpp"
#include <iostream>
#include <algorithm>

AlienShip::AlienShip(sf::Vector2f position, sf::Vector2u size, sf::Texture* texture, Level* level)
: Entity(position, size, texture, level) {
    type = Entity::Type::ALIEN_SHIP;
}

AlienShip::AlienShip(float x, float y, unsigned int w, unsigned int h, sf::Texture* texture, Level* level)
: Entity(x, y, w, h, texture, level) {
    type = Entity::Type::ALIEN_SHIP;
}

AlienShip::~AlienShip() {

}

// void AlienShip::checkCollision(Entity* entity) {
//     if(entity != this) {
//         if(collisionBox.intersects(&entity->collisionBox)) {
//             if(entity->type == Entity::PLAYER_SHIP) {
//                 // entity->damage(damage);
//             }
//         }
//     }
// }

void AlienShip::update(sf::Time frameTime) {
    updateAI();
    Entity::update(frameTime);
}

void AlienShip::updateAI() {
    
    switch(state) {
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

void AlienShip::movingState() {
    if(changeMovementTimer.getElapsedTime() >= CHANGE_MOVEMENT_DELAY) {
        switch(Util::GetRandomNumber(0,3)) {
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

void AlienShip::firingState() {
    fire();
    state = MOVING;
}

void AlienShip::fire() {

}

// void AlienShip::draw(sf::RenderTarget &target, sf::RenderStates states) {
//     //target.draw(sprite, states);
//     //Entity::draw(target, states);

//     states.transform *= getTransform(); // will apply all transformations on the entity to the sprite when it is drawn

//     if(windowContains(target.getView(), sprite)) {
//         target.draw(sprite, states);
//     }
// }

// void AlienShip::setTexture(sf::Texture* texture) {
//     if(texture == nullptr) {
//         Log::error("Enitity::setTexture(): Texture pointer invalid. The texture probably wasn't loaded.");
//         exit(-1);
//     }
//     sprite.setTexture(*texture);
//}