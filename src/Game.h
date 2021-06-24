#pragma once
#include <SFML/Graphics.hpp>
#include "Generator.h"
#include "Info.h"
#include "Config.h"

class Game
{
public:
	Game();
	void run();
private:
	void processEvents();
	void update(float deltaTime, float frameTime);
	void render();
	sf::RenderWindow window_;
	Generator gen_;
	Config config_;
	Info info_;
	sf::Font font_;
	bool inFireMode_ = true;
};