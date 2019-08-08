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

        if(relativeVel.x == 0 || relativeVel.y == 0){
            return false;
        }

        float firstTime = 0.0f;
        float lastTime = 1.0f;

		float box1Right = box1.left + box1.width;
		float box2Right = box2.left + box2.width;
		float box1Bottom = box1.top + box1.height;
		float box2Bottom = box2.top + box2.height;

        // For each axis, determine times of first and last contact, if any
        if(relativeVel.x < 0.0f) {
            if(box2Right < box1.left) return false; // Nonintersecting and moving apart
            if(box1Right < box2.left) firstTime = std::max( (box1Right - box2.left) / relativeVel.x, firstTime);
            if(box2Right > box1.left) lastTime = std::min( (box1.left - box2Right) / relativeVel.x, lastTime);
        }
        if(relativeVel.x > 0.0f) {
            if(box2.left > box1Right) return false; // Nonintersecting and moving apart
            if(box2Right < box1.left) firstTime = std::max( (box1.left - box2Right) / relativeVel.x, firstTime);
            if(box1.left + box1Right) lastTime = std::min( (box1Right - box2.left) / relativeVel.x, lastTime);
        }

        if(relativeVel.y < 0.0f) {
            if(box2Bottom < box1.top) return false; // Nonintersecting and moving apart 
            if(box1Bottom < box2.top) firstTime = std::max( (box1Bottom - box2.top) / relativeVel.y, firstTime);
            if(box2Bottom > box1.top) lastTime = std::min( (box1.top - box2Bottom) / relativeVel.y, lastTime);
        }
        if(relativeVel.y > 0.0f) {
            if(box2.top > box1Bottom) return false; // Nonintersecting and moving apart
            if(box2Bottom < box1.top) firstTime = std::max( (box1.top - box2Bottom) / relativeVel.y, firstTime);
            if(box1Bottom > box2.top) lastTime = std::min( (box1Bottom - box2.top) / relativeVel.y, lastTime);
        }

        // No overlap possible if time of first contact occurs after time of last contact
        if(firstTime > lastTime) return false;
        
        *timeOfCollision = firstTime;
        return true;
    }


}
