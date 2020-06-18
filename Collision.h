#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Config.h"
struct CollisionResult
{
	bool collided = false;
	sf::Vector2f contactPoint;
	sf::Vector2f unitNormal;
	float depth = 0.f;
};
class Collision
{
public:
	static CollisionResult collides(Ball& obj1, Ball& obj2);
	static void resolve_collision(Ball& obj1, Ball& obj2, const CollisionResult& collision, const ConfigState& config);
	static void positional_correction(Ball& obj1, Ball& obj2, const CollisionResult& collision);
};

