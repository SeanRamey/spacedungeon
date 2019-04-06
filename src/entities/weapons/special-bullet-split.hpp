#ifndef SPECIAL_BULLET_SPLIT
#define SPECIAL_BULLET_SPLIT
#include "bullet.hpp"
#include "entity.hpp"

class SpecialBulletSplit : public Bullet{

    public:
        SpecialBulletSplit(sf::Vector2f position, sf::Vector2f targetPosition, Entity* owner, Level* level);
        ~SpecialBulletSplit();

        void update(sf::Time frameTime);

    private:
        const unsigned int SPEED = 1500;
        const sf::Vector2u SIZE = sf::Vector2u(10,10);
        const unsigned int DAMAGE = 1;
};
#endif
