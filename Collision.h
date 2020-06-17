#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
struct CollisionResult
{
	bool collided = false;
	sf::Vector2f contactPoint;
	sf::Vector2f unitNormal;
	float depth;
};
class Collision
{
public:
	static CollisionResult collides(Ball& obj1, Ball& obj2);
	static void resolve_collision(Ball& obj1, Ball& obj2, const CollisionResult& collision);
	static void positional_correction(Ball& obj1, Ball& obj2, const CollisionResult& collision);
};

