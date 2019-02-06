#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "collision-box.hpp"

class Entity {

    protected:
        sf::Vector2f position;
        sf::Vector2u size;
        sf::Vector2f nextPosition;
        sf::Vector2f velocity;
        float angle;

        sf::Sprite sprite;
    public:
        CollisionBox collisionBox;

        enum types : int {PLAYER_SHIP, ALIEN_SHIP, TILE};
        types type;

        virtual void update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities) = 0;
        virtual void draw(sf::RenderWindow* window);
        // virtual void getNextPosition(sf::Time frameTime) = 0;
        virtual void setVelocity(sf::Vector2f vector);
        virtual void checkCollision(Entity* entity) = 0;
        virtual void setTexture(sf::Texture* texture);
        virtual void applyMovement(sf::Time frameTime);
        virtual sf::Vector2f getVelocity();
        virtual void addVelocity(sf::Vector2f newVelocity);
        virtual float calculateAngleTo(sf::Vector2f position);
        virtual void face(sf::Vector2f position);
        virtual sf::Vector2u getSize();
        sf::Vector2f getPosition();
        Entity(sf::Vector2f position, sf::Vector2f size);
        Entity(float x, float y, unsigned int w, unsigned int h);
        ~Entity();
        
        unsigned int MAX_SPEED = 1000; // MAX_SPEED MUST BE LARGER THAN ACCELERATION
        unsigned int ACCELERATION = 100;
        float FRICTION = 0.98;
};

#endif