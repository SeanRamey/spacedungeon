#ifndef SPECIAL_BULLET_SPLIT
#define SPECIAL_BULLET_SPLIT
#include "bullet.hpp"
#include "entity.hpp"

class SpecialBulletShrapnel : public Bullet{
    private:

    public:
        void update(sf::Time frameTime, sf::RenderWindow* window);
        SpecialBulletShrapnel(sf::Vector2f position, sf::Vector2f finalPosition, sf::Vector2u size, unsigned int speed, unsigned int damage, Level* level);
        ~SpecialBulletShrapnel();
};
#endif
