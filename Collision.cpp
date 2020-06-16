#include "Collision.h"
#include "VecTools.h"
#include <cmath>

CollisionResult Collision::collides(Ball& obj1, Ball& obj2)
{
	CollisionResult result;
	sf::Vector2f normal = obj2.getPosition() - obj1.getPosition();
	if (normal.x*normal.x + normal.y*normal.y <= obj1.radius*obj1.radius*4) { // assuming equal radius for now
		result.collided = true;
	}
	else {
		result.collided = false;
		return result;
	}
	float normal_length = VecTools::magnitude(normal);
	result.depth = obj1.radius + obj2.radius - normal_length;
	result.unitNormal = normal / normal_length;
	result.contactPoint = obj1.getPosition() + obj1.radius * result.unitNormal;
	return result;
}
void Collision::resolve_collision(Ball& obj1, Ball& obj2, const CollisionResult& collision)
{
	// To add: positional correction and associated slop
	sf::Vector2f rv = obj2.vel_ - obj1.vel_;
	float velAlongNormal = VecTools::dot(rv, collision.unitNormal);
	if (velAlongNormal > 0) {
		// Objects are already moving away from each other, so no need for impulse
		return;
	}
	float e = 0.8f; // coefficient of restitution
	constexpr float mass = 0.5f;
	float j = -(1 + e) * velAlongNormal / (1/mass + 1/mass);
	//j = 1.f;
	sf::Vector2f impulse = j * collision.unitNormal;
	obj1.vel_ -= impulse / mass;
	obj2.vel_ += impulse / mass;
}
