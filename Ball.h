#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

class Ball
{
public:
	Ball(float x, float y, int x_limit, int y_limit, float radius);
	void render(sf::RenderWindow& window);
	void update(float deltaTime, const ConfigState& config);
	void setPosition(sf::Vector2<float> newPos);
	sf::Vector2f getPosition();
	void setVelocity(sf::Vector2f newVel);
	void reset();
	void setCollided(bool);
	float radius = 25.f;
	sf::Vector2f vel_;
private:
	sf::Vector2f pos_;
	sf::CircleShape shape_;
	int y_limit_;
	int x_limit_;
	sf::Vector2f init_pos_;
};

