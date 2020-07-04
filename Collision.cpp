#include "Collision.h"
#include "VecTools.h"
#include <cmath>

CollisionResult Collision::collides(Ball& obj1, Ball& obj2)
{
	CollisionResult result;
	sf::Vector2f normal = obj2.getPosition() - obj1.getPosition();
	if (normal.x*normal.x + normal.y*normal.y <= obj1.radius*obj1.radius + 2*obj1.radius*obj2.radius + obj2.radius*obj2.radius) { 
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
void Collision::resolve_collision(Ball& obj1, Ball& obj2, const CollisionResult& collision, const ConfigState& config)
{
	sf::Vector2f rv = obj2.vel_ - obj1.vel_;
	float velAlongNormal = VecTools::dot(rv, collision.unitNormal);
	if (velAlongNormal > 0) {
		// Objects are already moving away from each other, so no need for impulse
		return;
	}
	float e = config.objRestitution; // coefficient of restitution
	float j = -(1 + e) * velAlongNormal / (obj1.inv_mass + obj2.inv_mass);
	sf::Vector2f impulse = j * collision.unitNormal;
	obj1.vel_ -= impulse  * obj2.inv_mass;
	obj2.vel_ += impulse * obj1.inv_mass;
	positional_correction(obj1, obj2, collision);
}
void Collision::positional_correction(Ball& obj1, Ball& obj2, const CollisionResult& collision)
{
	constexpr float percent = 0.8f; // factor to damp or increase effect of positional correction 
	sf::Vector2f correction = (collision.depth / (obj1.inv_mass + obj2.inv_mass)) * percent * collision.unitNormal;
	obj1.setPosition(obj1.getPosition() - correction * obj2.inv_mass);
	obj2.setPosition(obj2.getPosition() + correction * obj1.inv_mass);
}
