#pragma once
#include <SFML/Graphics.hpp>
// axis-aligned bounding box, used for the broad-phase collision detection
struct AABB
{
	sf::Vector2f min;
	sf::Vector2f max;
	AABB(sf::Vector2f &min, sf::Vector2f &max) : min(min), max(max) {};
};

