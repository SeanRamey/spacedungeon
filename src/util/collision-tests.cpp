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
            if(box2.left + box2.width < box1.left) return false;
            if(box1.left + box1.width < box2.left) firstTime = std::min( (box1.left + box1.width - box2.left) / relativeVel.x, lastTime);
            if(box2.left + box2.width > box1.left) lastTime = std::max( (box1.left - box2.left + box2.width) / relativeVel.x, firstTime);
        }
        if(relativeVel.x > 0.0f) {
            if(box2.left > box1.left + box1.width) return false;
            if(box2.left + box2.width < box1.left) firstTime = std::min( (box1.left - box2.left + box2.width) / relativeVel.x, lastTime);
            if(box1.left + box1.width > box2.left) lastTime = std::max( (box1.left + box1.width - box2.left) / relativeVel.x, firstTime);
        }
        
        if(relativeVel.y < 0.0f) {
            if(box2.top + box2.height < box1.top) return false;
            if(box1.top + box1.height < box2.top) firstTime = std::min( (box1.top + box1.height - box2.top) / relativeVel.y, firstTime);
            if(box2.top + box2.height > box1.top) lastTime = std::max( (box1.top - box2.top + box2.height) / relativeVel.y, lastTime);
        }
        if(relativeVel.y > 0.0f) {
            if(box2.top > box1.top + box1.height) return false;
            if(box2.top + box2.height < box1.top) firstTime = std::min( (box1.top - box2.top + box2.height) / relativeVel.y, firstTime);
            if(box1.top + box1.height > box2.top) lastTime = std::max( (box1.top + box1.height - box2.top) / relativeVel.y, lastTime);
        }


        // // For each axis, determine times of first and last contact, if any
        // for (int i = 0; i < 3; i++) {
        //     if (v[i] < 0.0f) {
        //         if (b.max[i] < a.min[i]) return 0;
        //         // Nonintersecting and moving apart
        //         if (a.max[i] < b.min[i]) tfirst = Max((a.max[i] - b.min[i]) / v[i], tfirst);
        //         if (b.max[i] > a.min[i]) tlast = Min((a.min[i] - b.max[i]) / v[i], tlast);
        //     }
        //     if (v[i] > 0.0f) {
        //         if (b.min[i] > a.max[i]) return 0;
        //         // Nonintersecting and moving apart
        //         if (b.max[i] < a.min[i]) tfirst = Max((a.min[i] - b.max[i]) / v[i], tfirst);
        //         if (a.max[i] > b.min[i]) tlast = Min((a.max[i] - b.min[i]) / v[i], tlast);
        //     }
        //     // No overlap possible if time of first contact occurs after time of last contact
        //     if (tfirst > tlast) return 0;
        // }

        
        if(firstTime > lastTime) return false;
        
        *timeOfCollision = firstTime;
        return true;
    }


}
