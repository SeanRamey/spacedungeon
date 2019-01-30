#ifndef COLLISION_BOX_HPP
#define COLLISION_BOX_HPP

class CollisionBox {
     public:
        float x;
        float y;
        unsigned int w;
        unsigned int h;

        // sf::RectangleShape debugRectangle;
        void update(float x, float y);
        bool intersects(CollisionBox*);
        CollisionBox(float x, float y, unsigned int w, unsigned int h);
        ~CollisionBox();
};
#endif