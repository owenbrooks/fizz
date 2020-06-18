#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include "Config.h"

class Generator
{
public:
	Generator(int x_limit, int y_limit);
	void createBallAt(float x, float y);
	void render(sf::RenderWindow& window);
	void update(float frameTime, const ConfigState& state);
	void clear();
	void reset();
	void togglePaused();
	unsigned int getObjCount();
private:
	std::vector<Ball> instances_;
	std::vector<Ball> prev_instances_;
	int x_limit_;
	int y_limit_;
	bool paused_;
};

