#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include "Config.h"

class Generator
{
public:
	Generator(int x_limit, int y_limit, const ConfigState& config);
	void render(sf::RenderWindow& window);
	void update(float frameTime, const ConfigState& state);
	void createBallAt(sf::Vector2f pos, float radius);
	void createBallAt(sf::Vector2f pos, float radius, sf::Vector2f initialVel);
	void handleMouseEvent(const sf::Event& event);
	void clear();
	void reset();
	void togglePaused();
	unsigned int getObjCount();
	void toggleFireMode();
private:
	void fire();
	const ConfigState& config_;
	std::vector<Ball> instances_;
	sf::CircleShape new_obj_;
	sf::Vector2f boundary_limits_;
	std::vector<std::unique_ptr<sf::Shape>> shapes_;
	sf::RectangleShape fire_line_;
	bool paused_ = false;
	bool inFireMode_ = true;
	bool placed_ = false;
	unsigned int color_index_ = 0;
};

const sf::Color ballColors[] = { sf::Color::Magenta, sf::Color::Yellow, sf::Color::White, 
								 sf::Color::Green, sf::Color::Red, sf::Color::Blue, sf::Color::Cyan };

