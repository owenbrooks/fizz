#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
struct CollisionResult
{
	bool collided;
	sf::Vector2f contactPoint;
	sf::Vector2f contactNormal;
};
class Collision
{
public:
	static CollisionResult collides(Ball& obj1, Ball& obj2);
};

