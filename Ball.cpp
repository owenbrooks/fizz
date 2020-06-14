#include "Ball.h"

constexpr float radius = 50.f;
constexpr float gravity = 0.003f;
constexpr float cor = 0.8f;

Ball::Ball(float x, float y, int low_limit) : vel_(0.f, 0.f), shape_(sf::CircleShape(radius, 8)), y_limit_(low_limit)
{
	shape_.setPosition(x - radius, y - radius);
	shape_.setFillColor(sf::Color::Magenta);
}
void Ball::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}
void Ball::update(sf::Time deltaTime)
{
	// check collision status
	if (shape_.getPosition().y + 2*radius < y_limit_ || vel_.y < 0) {
		sf::Vector2f accel(0.f, gravity);
		vel_ += accel * (float)deltaTime.asMilliseconds();
		shape_.move(0, vel_.y * (float)deltaTime.asMilliseconds());
	}
	else {
		shape_.setPosition(shape_.getPosition().x, y_limit_ - 2*radius);
		vel_.y = -cor * vel_.y;
		shape_.move(0, vel_.y * (float)deltaTime.asMilliseconds());
	}
}
void Ball::setPosition(sf::Vector2<float> newPos) 
{
	shape_.setPosition(newPos.x - radius, newPos.y - radius);
}
void Ball::setVelocity(sf::Vector2f newVel)
{
	vel_ = newVel;
}