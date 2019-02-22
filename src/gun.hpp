#include "bullet.hpp"
#include <vector>
#include "entity.hpp"

class Gun {
    private:
        Entity* parent;
        std::vector<Bullet*> bullets;
        unsigned int type;
    public: 
        Gun(Entity*, unsigned int);
        ~Gun();
        void update(sf::Time frameTime, sf::RenderWindow* window);
        void draw(sf::RenderWindow* window);
        void shoot();
        void setType(unsigned int type){
            this->type = type;
        }
};