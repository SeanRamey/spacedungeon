#include "bullet.hpp"
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


    public: 
        Gun(Entity*, unsigned int);
        ~Gun();
        void update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities);
        void draw(sf::RenderWindow* window);
        void shoot();
        void setType(unsigned int type);
};