#include "VecTools.h"
#include <cmath>

// Collection of common vector calculations
float VecTools::magnitude(sf::Vector2f v)
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}
float VecTools::dot(sf::Vector2f v1, sf::Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}
sf::Vector2f VecTools::normalised(sf::Vector2f v)
{
	return v / VecTools::magnitude(v);
}
