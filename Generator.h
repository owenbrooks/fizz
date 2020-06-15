#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"

class Generator
{
public:
	Generator(int low_limit);
	void createBallAt(float x, float y);
	void render(sf::RenderWindow& window);
	void update(float deltaTime);
	void clear();
	void reset();
private:
	std::vector<Ball> instances_;
	std::vector<Ball> prev_instances_;
	int low_limit_;
};

