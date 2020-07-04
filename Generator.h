#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include "Config.h"

class Generator
{
public:
	Generator(int x_limit, int y_limit, const ConfigState& config);
	void createBallAt(float x, float y, float radius);
	void createBallAt(float x, float y, float radius, sf::Vector2f initialVel);
	void handleMouseEvent(const sf::Event& event);
	void render(sf::RenderWindow& window);
	void update(float frameTime, const ConfigState& state);
	void clear();
	void reset();
	void togglePaused();
	unsigned int getObjCount();
	void toggleFireMode();
private:
	const ConfigState& config_;
	std::vector<Ball> instances_;
	std::vector<Ball> prev_instances_;
	std::vector<std::unique_ptr<sf::Shape>> shapes_;
	sf::CircleShape new_obj_;
	sf::RectangleShape fire_line_;
	int x_limit_;
	int y_limit_;
	bool paused_;
	bool inFireMode_ = true;
	bool placed_ = false;
	unsigned int color_index_;
	void fire();
};

const sf::Color ballColors[] = { sf::Color::Magenta, sf::Color::Yellow, sf::Color::White, 
								 sf::Color::Green, sf::Color::Red, sf::Color::Blue, sf::Color::Cyan };

