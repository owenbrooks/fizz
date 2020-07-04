#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"
#include "AABB.h"

const sf::Color ballColors[] = { sf::Color::Magenta, sf::Color::Yellow, sf::Color::White, sf::Color::Green, sf::Color::Red,
sf::Color::Blue, sf::Color::Cyan };
constexpr float density = 0.005f;

class Ball
{
public:
	Ball(float x, float y, int x_limit, int y_limit, float radius, sf::Shape* shape);
	void render(sf::RenderWindow& window);
	void update(float deltaTime, const ConfigState& config);
	void setPosition(sf::Vector2<float> newPos);
	sf::Vector2f getPosition();
	void setVelocity(sf::Vector2f newVel);
	void reset();
	void setCollided(bool);
	float radius = 25.f;
	float inv_mass;
	sf::Vector2f vel_;
	const AABB getAABB() const;
private:
	sf::Vector2f pos_;
	sf::Shape* shape_;
	int y_limit_;
	int x_limit_;
	sf::Vector2f init_pos_;
	static unsigned int colorIndex;
	void move(sf::Vector2f vec);
};

