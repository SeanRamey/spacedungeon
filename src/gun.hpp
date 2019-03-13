#ifndef GUN_HPP
#define GUN_HPP
#include "bullet.hpp"
#include <vector>

class Gun {
    private:
        Entity* parent;
        std::vector<Bullet*> bullets;
        unsigned int type;
    public: 
        Gun(Entity*, unsigned int type);
        ~Gun();
        void update(sf::Time frameTime);
        void shoot();
        void setType(unsigned int type);
};

#endif