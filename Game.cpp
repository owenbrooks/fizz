#include "Game.h"

Game::Game() : window_(sf::VideoMode(800, 800), "Fizz"), gen_(sf::VideoMode::getDesktopMode().height)
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	window_.create(sf::VideoMode(desktop.width, desktop.height, desktop.bitsPerPixel), "Fizz", sf::Style::Fullscreen);
	window_.setFramerateLimit(120);
}

void Game::run()
{
	sf::Clock clock;

	while (window_.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		processEvents();
		update(deltaTime);
		render();	
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window_.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			window_.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Key::Q) { // 16 is for q
				window_.close();
			}
			else if (event.key.code == sf::Keyboard::Key::C) {
				gen_.clear();
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left) {
				gen_.createBallAt(event.mouseButton.x, event.mouseButton.y);
			}
			break;
		case sf::Event::MouseMoved:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
				gen_.createBallAt(event.mouseMove.x, event.mouseMove.y);
			}
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	gen_.update(deltaTime);
}

void Game::render()
{
	window_.clear();
	gen_.render(window_);
	window_.display();
}