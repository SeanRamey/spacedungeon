#ifndef GUN_HPP
#define GUN_HPP
#include "bullet.hpp"
#include "basic-bullet.hpp"
#include "special-bullet.hpp"
#include <vector>
#include <future>

class Gun {
    private:
        Entity* parent;
        std::vector<Bullet*> bullets;
        unsigned int type;

        sf::Vector2u basicBulletSize;
        unsigned int basicBulletSpeed; 
        unsigned int basicBulletDamage;

        sf::Vector2u specialBulletSize;
        unsigned int specialBulletSpeed;
        unsigned int specialBulletDamage;

        std::vector<int> specialBulletStateLengths = {3};

    public: 
        Gun(Entity*, unsigned int);
        ~Gun();

        std::vector<Bullet*>* getBullets();
        void update(sf::Time frameTime, sf::RenderWindow* window);
        void draw(sf::RenderWindow* window);
        void shoot();
        void setType(unsigned int type);
};
#endif