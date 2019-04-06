#ifndef ALIEN_SHIP_HPP
#define ALIEN_SHIP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "entity.hpp"

class AlienShip : public Entity
{
    public:
        AlienShip(float x, float y, unsigned int w, unsigned int h, sf::Texture* texture, Level* level);
        AlienShip(float x, float y, unsigned int w, unsigned int h, Level* level);
        ~AlienShip();
        void update(sf::Time frameTime, sf::RenderWindow* window);
        void setMovement(sf::Vector2f movement);
        void checkCollision(Entity* entities);
        sf::Vector2f getMovement();
        void fire();

    private:

        void updateAI();
        void movingState();
        void firingState();
        sf::Clock changeMovementTimer;
        sf::Clock firingTimer;
        enum State
        {
            FIRING,
            MOVING
        };
        State state = MOVING;
        const sf::Time CHANGE_MOVEMENT_DELAY = sf::seconds(1);
        const sf::Time FIRING_DELAY = sf::seconds(1);
        const unsigned int MAX_SPEED = 100; // pixels per second

};

#endif
