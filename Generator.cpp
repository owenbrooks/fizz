#include "Generator.h"
#include "Collision.h"
#include <cmath>
#include "VecTools.h"
#include "BroadPhase.h"
#include <iostream>   
constexpr size_t max_objs = 10000;
constexpr auto PI = 3.14159265358979323846f;
Generator::Generator(int x_limit, int y_limit, const ConfigState& config) : config_(config), new_obj_(config.ballRadius), x_limit_(x_limit), y_limit_(y_limit), instances_(), paused_(false), color_index_(0)
{
}
void Generator::createBallAt(float x, float y, float radius)
{
	createBallAt(x, y, radius, sf::Vector2f(0.f, 0.f));
}
void Generator::createBallAt(float x, float y, float radius, sf::Vector2f initialVel)
{
	shapes_.push_back(std::make_unique<sf::CircleShape>(radius));
	Ball newBall = Ball(x, y, x_limit_, y_limit_, radius, initialVel, shapes_.back().get(), ballColors[color_index_ % 7]);
	color_index_++;
	instances_.push_back(newBall);
	if (instances_.size() > max_objs) {
		instances_.erase(instances_.begin());
	}
}
void Generator::render(sf::RenderWindow& window)
{
	for (auto& inst : instances_) {
		inst.render(window);
	}
	if (inFireMode_) {
		window.draw(new_obj_);
		window.draw(fire_line_);
	}
}
void Generator::update(float deltaTime, const ConfigState& config)
{
	if (paused_) {
		return;
	}
	if (instances_.size() > 1) {
		auto pairs = BroadPhase::sweep_and_prune(instances_);
		for (auto pair : pairs) {
			const CollisionResult collision_res = Collision::collides(*pair.first, *pair.second);
			if (collision_res.collided) {
				Collision::resolve_collision(*pair.first, *pair.second, collision_res, config);
			}
		}
	}
	for (auto& inst : instances_) {
		inst.update(deltaTime, config);
	}

	if (inFireMode_) {
		if (!placed_) {
			sf::Vector2f new_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition()) - sf::Vector2f(config_.ballRadius, config_.ballRadius);
			new_obj_.setPosition(new_pos);
		}
		else {
			// calculate distance between new_obj and mouse
			sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
			sf::Vector2f difference = new_obj_.getPosition() + sf::Vector2f(config_.ballRadius, config_.ballRadius) - mousePos;
			float distance = VecTools::magnitude(difference);
			constexpr float fire_line_width = 4.f;
			fire_line_.setSize(sf::Vector2f(distance, fire_line_width));
			float angle = atan2(difference.y, difference.x);
			fire_line_.setPosition(mousePos);
			fire_line_.setRotation(angle * 360.f / (2.f * PI));
		}
	}
}
void Generator::handleMouseEvent(const sf::Event& event)
{
	switch (event.type) {
	case sf::Event::MouseButtonPressed: {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (inFireMode_) {
				if (!placed_) {
					placed_ = true;
				}
				else {
					fire();
					inFireMode_ = false;
				}
			}
			else {
				createBallAt((float)event.mouseButton.x, (float)event.mouseButton.y, config_.ballRadius);
			}
		}
		break;
	}
	}
}
void Generator::toggleFireMode()
{
	if (inFireMode_) {
		inFireMode_ = false;
	}
	else {
		inFireMode_ = true;
		placed_ = false;
		sf::Vector2f radiusCompensation(config_.ballRadius, config_.ballRadius);
		new_obj_.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition()) - radiusCompensation);
		new_obj_.setRadius(config_.ballRadius);
		new_obj_.setFillColor(ballColors[color_index_ % 7]);

		fire_line_.setPosition(-100.f, -100.f);
		fire_line_.setRotation(0.f);
		fire_line_.setFillColor(ballColors[color_index_ % 7]);
	}
}
void Generator::fire()
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
	sf::Vector2f difference = new_obj_.getPosition() + sf::Vector2f(config_.ballRadius, config_.ballRadius) - mousePos;
	sf::Vector2f initialVel = difference * 0.005f;

	createBallAt(new_obj_.getPosition().x + config_.ballRadius, new_obj_.getPosition().y + config_.ballRadius, config_.ballRadius, initialVel);
}
void Generator::clear()
{
	instances_.clear();
}
void Generator::reset()
{
	for (auto& inst : instances_) {
		inst.reset();
	}
}
void Generator::togglePaused()
{
	paused_ = !paused_;
}
unsigned int Generator::getObjCount()
{
	return instances_.size();
}
