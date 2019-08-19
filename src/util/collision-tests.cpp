#include "collision-tests.hpp"

namespace Collision {

   bool TestMovingAABB(
        sf::FloatRect box1,
        sf::FloatRect box2,
        sf::Vector2f vel1,
        sf::Vector2f vel2,
        float* timeOfCollision,
		sf::Vector2f* normals) {
        
        *timeOfCollision = 0.0f;
    
        if(box1.intersects(box2)) {
            return true;
        }
        
        sf::Vector2f relativeVel = vel2 - vel1;

        if(relativeVel.x == 0){
			relativeVel.x = FLT_MIN;
        } 
		if(relativeVel.y == 0){
			relativeVel.y = FLT_MIN;
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





		float xInvEntry, yInvEntry;
		float xInvExit, yInvExit;
		// find the distance between the objects on the near and far sides for both x and y
		if (vel1.x > 0.0f)
		{
			xInvEntry = box2.left - box1Right;
			xInvExit = box2Right - box1.left;
		}
		else 
		{
			xInvEntry = box2Right - box1.left;
			xInvExit = box2.left - box1Right;
		}
		if (vel1.y > 0.0f)
		{
			yInvEntry = box2.top - box1Bottom;
			yInvExit = box2Bottom - box1.top;
		}
		else
		{
			yInvEntry = box2Bottom - box1.top;
			yInvExit = box2.top - box1Bottom;
		}

		// calculate normals

		float xEntry, yEntry;
		float xExit, yExit;

		if (vel1.x == 0.0f)
		{
			xEntry = -std::numeric_limits<float>::infinity();
			xExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			xEntry = xInvEntry / vel1.x;
			xExit = xInvExit / vel1.x;
		}

		if (vel1.y == 0.0f)
		{
			yEntry = -std::numeric_limits<float>::infinity();
			yExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			yEntry = yInvEntry / vel1.y;
			yExit = yInvExit / vel1.y;
		}

		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normals->x = 1.0f;
				normals->y = 0.0f;
			}
				else
			{
				normals->x = -1.0f;
				normals->y = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normals->x = 0.0f;
				normals->y = 1.0f;
			}
				else
			{
				normals->x = 0.0f;
				normals->y = -1.0f;
			}
		}
        
        // No overlap possible if time of first contact occurs after time of last contact
        if(firstTime > lastTime  || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f){
			normals->x = 0.0f;
			normals->y = 0.0f;
		   	return false;
		}
        *timeOfCollision = firstTime;
        return true;
    }


}
