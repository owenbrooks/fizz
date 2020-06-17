#include "Game.h"
#include <iostream>

Game::Game() : window_(sf::VideoMode(800, 800), "Fizz"), gen_(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), info_(), _config()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	window_.create(sf::VideoMode(desktop.width, desktop.height, desktop.bitsPerPixel), "Fizz", sf::Style::Fullscreen);
	window_.setFramerateLimit(60);
	window_.setVerticalSyncEnabled(true);
	if (!font_.loadFromFile("cour.ttf")) {
		std::cout << "Error loading font" << std::endl;
	}
	else
	{
		info_.setFont(font_);
		_config.setFont(font_);
	}
}

void Game::run()
{
	sf::Clock clock;
	float accumulator = 0.f;
	constexpr float deltaTime = 1.f/120.f;

	while (window_.isOpen())
	{
		processEvents();
		sf::Time frameTime = clock.restart();
		accumulator += frameTime.asSeconds();

		while (accumulator >= deltaTime)
		{
			update(deltaTime*1000, frameTime.asSeconds());
			accumulator -= deltaTime;

		}
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
			if (!_config.isActive()) {
				if (event.key.code == sf::Keyboard::Key::Q) {
					window_.close();
				}
				else if (event.key.code == sf::Keyboard::Key::C) {
					gen_.clear();
				}
				else if (event.key.code == sf::Keyboard::Key::R) {
					gen_.reset();
				}
				else if (event.key.code == sf::Keyboard::Key::P) {
					gen_.togglePaused();
				}
				else if (event.key.code == sf::Keyboard::Key::SemiColon) {
					if (event.key.shift) {
						_config.showCommandBox();
					};
				}
			}
			else if (event.key.code == sf::Keyboard::Key::Enter) {
				_config.executeCommand();
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left) {
				gen_.createBallAt((float)event.mouseButton.x, (float)event.mouseButton.y);
			}
			break;
		case sf::Event::MouseMoved:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !_config.isActive()) {
				gen_.createBallAt((float)event.mouseMove.x, (float)event.mouseMove.y);
			}
			break;
		case sf::Event::TextEntered:
			if (_config.isActive())
			{
				_config.handleEvent(event);
			}
			break;
		}
	}
}

void Game::update(float deltaTime, float frameTime)
{
	gen_.update(deltaTime);
	_config.update(deltaTime);
	info_.update(frameTime, _config.getState());
}

void Game::render()
{
	window_.clear();
	gen_.render(window_);
	info_.render(window_);
	_config.render(window_);
	window_.display();
}