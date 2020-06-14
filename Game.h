#pragma once
#include <SFML/Graphics.hpp>
#include "Generator.h"

class Game
{
public:
	Game();
	void run();
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
private:
	sf::RenderWindow window_;
	Generator gen_;
};