#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"
#include "AABB.h"

constexpr float density = 0.005f;

class Ball
{
public:
	Ball(sf::Vector2f initial_pos, sf::Vector2f boundary_limits, float radius, sf::Vector2f initial_vel, sf::Shape* shape, sf::Color color);
	void render(sf::RenderWindow& window);
	void update(float deltaTime, const ConfigState& config);
	void setPosition(sf::Vector2<float> newPos);
	sf::Vector2f getPosition();
	void setVelocity(sf::Vector2f newVel);
	void reset();
	void setCollided(bool);
	const AABB getAABB() const;
	float radius = 25.f;
	float inv_mass;
	sf::Vector2f vel_;
private:
	void move(sf::Vector2f vec);
	sf::Vector2f pos_;
	sf::Vector2f init_pos_;
	sf::Shape* shape_;
	int x_limit_;
	int y_limit_;
};

