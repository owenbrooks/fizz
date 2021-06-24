#pragma once
#include <SFML/Graphics.hpp>

// Collection of common vector calculations
namespace VecTools
{
	float magnitude(sf::Vector2f v);
	float dot(sf::Vector2f v1, sf::Vector2f v2);
	sf::Vector2f normalised(sf::Vector2f v);
};

