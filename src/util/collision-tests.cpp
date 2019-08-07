#include "collision-tests.hpp"

namespace Collision {

   bool TestMovingAABB(
        sf::FloatRect box1,
        sf::FloatRect box2,
        sf::Vector2f vel1,
        sf::Vector2f vel2,
        float* timeOfCollision ) {
        
        *timeOfCollision = 0.0f;
    
        if(box1.intersects(box2)) {
            return true;
        }
        
        sf::Vector2f relativeVel = vel2 - vel1;
        
        float firstTime = 0.0f;
        float lastTime = 1.0f;
        
        if(relativeVel.x < 0.0f) {
            if(box2.width < box1.left) return false;
            if(box1.width < box2.left) firstTime = std::max( (box1.width - box2.left) / relativeVel.x, firstTime);
            if(box2.width > box1.left) lastTime = std::min( (box1.left - box2.width) / relativeVel.x, lastTime);
        }
        if(relativeVel.x > 0.0f) {
            if(box2.left > box1.width) return false;
            if(box2.width < box1.left) firstTime = std::max( (box1.left - box2.width) / relativeVel.x, firstTime);
            if(box1.width > box2.left) lastTime = std::min( (box1.width - box2.left) / relativeVel.x, lastTime);
        }
        
        if(relativeVel.y < 0.0f) {
            if(box2.height < box1.top) return false;
            if(box1.height < box2.top) firstTime = std::max( (box1.height - box2.top) / relativeVel.y, firstTime);
            if(box2.height > box1.top) lastTime = std::min( (box1.top - box2.height) / relativeVel.y, lastTime);
        }
        if(relativeVel.y > 0.0f) {
            if(box2.top > box1.height) return false;
            if(box2.height < box1.top) firstTime = std::max( (box1.top - box2.height) / relativeVel.y, firstTime);
            if(box1.height > box2.top) lastTime = std::min( (box1.height - box2.top) / relativeVel.y, lastTime);
        }
        
        if(firstTime > lastTime) return false;
        
        *timeOfCollision = firstTime;
        return true;
    }


}
