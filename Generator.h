#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"

class Generator
{
public:
	Generator(int x_limit, int y_limit);
	void createBallAt(float x, float y);
	void render(sf::RenderWindow& window);
	void update(float deltaTime);
	void clear();
	void reset();
	void togglePaused();
private:
	std::vector<Ball> instances_;
	std::vector<Ball> prev_instances_;
	int x_limit_;
	int y_limit_;
	bool paused_;
};

