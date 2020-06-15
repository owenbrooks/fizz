#include "Collision.h"

CollisionResult Collision::collides(Ball& obj1, Ball& obj2)
{
	CollisionResult result;
	sf::Vector2f normal = obj2.getPosition() - obj1.getPosition();
	if (normal.x*normal.x + normal.y*normal.y <= obj1.radius*obj1.radius*4) { // assuming equal radius for now
		result.collided = true;
	}
	else {
		result.collided = false;
	}
	return result;
}
