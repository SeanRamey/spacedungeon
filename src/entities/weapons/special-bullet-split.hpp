#ifndef SPECIAL_BULLET_SPLIT
#define SPECIAL_BULLET_SPLIT
#include "bullet.hpp"
#include "entity.hpp"

class SpecialBulletShrapnel : public Bullet{
    private:

    public:
        void update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities);
        SpecialBulletShrapnel(sf::Vector2f endPosition, sf::Vector2u size, unsigned int speed, unsigned int damage);
        ~SpecialBulletShrapnel();
};
#endif