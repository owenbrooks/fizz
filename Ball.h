#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
public:
	Ball(float x, float y, int low_limit);
	void render(sf::RenderWindow& window);
	void update(float deltaTime);
	void setPosition(sf::Vector2<float> newPos);
	void setVelocity(sf::Vector2f newVel);
private:
	sf::Vector2f pos_;
	sf::Vector2f vel_;
	sf::CircleShape shape_;
	int y_limit_;
};

