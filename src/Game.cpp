// This file contains the main game loop, window setup and processing of events (e.g. mouse clicks, key presses)
#include "Game.h"
#include <iostream>

Game::Game() : window_(sf::VideoMode(800, 800), "Fizz"), gen_(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, config_.getState()), config_(), info_()
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
		config_.setFont(font_);
	}
}

void Game::run()
{
	// Implements a fixed timestep loop as detailed in https://gafferongames.com/post/fix_your_timestep/
	// This means the simulation should give perfectly reproducible results
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
			if (!config_.isActive()) {
				if (event.key.code == sf::Keyboard::Key::Q) {
					// Quit the app
					window_.close();
				}
				else if (event.key.code == sf::Keyboard::Key::C) {
					// Clear the screen of all objects
					gen_.clear();
				}
				else if (event.key.code == sf::Keyboard::Key::R) {
					// Reset the objects to their starting positions
					gen_.reset();
				}
				else if (event.key.code == sf::Keyboard::Key::P) {
					// Pause the simulation (objects can still be added while simulation is paused
					gen_.togglePaused();
				}
				else if (event.key.code == sf::Keyboard::Key::H) {
					// Hides/shows info about the current performance/configuration options
					info_.toggleHidden();
				}
				else if (event.key.code == sf::Keyboard::Key::G) {
					// Turns gravity on or off
					config_.toggleGravity();
				}
				else if (event.key.code == sf::Keyboard::Key::T) {
					// Enables/disables the top of the screen acting like a wall.
					// When it is disabled, items can occupy space above the top of the screen.
					config_.toggleTopWall();
				}
				else if (event.key.code == sf::Keyboard::Key::F) {
					// Enables/disables fire mode
					// In fire mode, the ball is not just dropped after one click, but is launched in a direction after
					// a second click, as if hit by a pool cue.
					gen_.toggleFireMode();
				}
				else if (event.key.code == sf::Keyboard::Key::SemiColon) {
					if (event.key.shift) { // for colon key
						// Shows the box that can be used to change configuration parameters of the simulation
						// e.g. force of gravity, size of the objects to be inserted, coefficient of restitution of the objects
						config_.showCommandBox();
					};
				}
			}
			else if (event.key.code == sf::Keyboard::Key::Enter) {
				// Use the enter key to execute a command that has been entered in the command box
				config_.executeCommand();
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left) {
					gen_.handleMouseEvent(event);
			}
			break;
		case sf::Event::MouseMoved:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !config_.isActive()) {
				// Moving the mouse while holding the S key will generate many objects following the mouse
				gen_.createBallAt(sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y), config_.getState().ballRadius);
			}
			break;
		case sf::Event::TextEntered:
			if (config_.isActive())
			{
				config_.handleEvent(event);
			}
			break;
		}
	}
}

void Game::update(float deltaTime, float frameTime)
{
	ConfigState currConfig = config_.getState();
	gen_.update(deltaTime, currConfig);
	config_.update();
	info_.update(frameTime, currConfig, gen_.getObjCount());
}

void Game::render()
{
	window_.clear();
	gen_.render(window_);
	info_.render(window_);
	config_.render(window_);
	window_.display();
}