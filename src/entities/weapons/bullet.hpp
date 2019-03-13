#ifndef BULLET_HPP
#define BULLET_HPP
//#include "sfmlpch.hpp"
#include "entity.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Bullet : public Entity {
    public:
        Bullet(sf::Vector2f, sf::Vector2u, unsigned int, unsigned int, sf::Time, Level* level);
        Bullet(sf::Vector2f, sf::Vector2f, sf::Vector2u, unsigned int, unsigned int, sf::Time, Level* level);
        virtual void update(sf::Time frameTime, sf::RenderWindow* window);
        
        ~Bullet();
        bool isDead();
        virtual void onDeath();

    protected:
        unsigned int initialSpeed;
        unsigned int damage;

        bool dead;

        sf::Clock timeAlive;
        sf::Time maxTimeAlive;

        sf::Vector2f finalPosition;

        virtual void checkCollision(Entity* entity);
    
};
#endif 
