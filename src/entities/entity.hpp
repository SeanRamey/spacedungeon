#ifndef ENTITY_HPP
#define ENTITY_HPP

//#include "sfmlpch.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Level; // forward declare to avoid circular dependency

class Entity : public sf::Transformable, public sf::Drawable {

    public:
        Entity(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, Level* level);
        Entity(float x, float y, unsigned int w, unsigned int h, sf::Texture* texture, Level* level);
        virtual ~Entity();

        virtual void update(sf::Time frameTime);
        sf::Vector2f getVelocity();
        void setVelocity(sf::Vector2f vector);
        void accelerate(sf::Vector2f velocity);
        void limitVelocity(const unsigned int MAX_SPEED);
        float calculateAngleTo(sf::Vector2f position);
        void face(sf::Vector2f position);
        sf::FloatRect getCollisionRect();
        sf::Vector2u getSize();
        unsigned int getHitpoints();
        void repair(unsigned int hitPoints);
        void damage(unsigned int hitPoints);
        void destroy();
        bool isDestroyed();
        
        
        //const uint32_t MAX_SPEED; // MAX_SPEED MUST BE LARGER THAN ACCELERATION
        //uint32_t ACCELERATION = 100;
        //float FRICTION = 0.98;

     protected:
        sf::Vector2f velocity;
        sf::FloatRect collisionRect;
        sf::Sprite sprite;
        unsigned int hitpoints;
        Level* level;

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states);

};

#endif