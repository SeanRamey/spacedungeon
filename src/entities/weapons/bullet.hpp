#ifndef BULLET_HPP
#define BULLET_HPP
//#include "sfmlpch.hpp"
#include "entity.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Bullet : public Entity {
    public:
        Bullet(sf::Vector2f position, sf::Vector2f targetPosition, Entity* owner, sf::Vector2u size, unsigned int initialSpeed, unsigned int damage, Level* level, sf::Time maxTimeAlive = sf::seconds(3));
        virtual ~Bullet();
        virtual void update(sf::Time frameTime);
        unsigned int getDamage();

    protected:
        Entity* owner;
        unsigned int initialSpeed;
        unsigned int damage;

        sf::Clock timeAlive;
        sf::Time maxTimeAlive;

        sf::Vector2f targetPosition;

    private:
    
};
#endif 
