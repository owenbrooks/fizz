#include "Ball.h"

constexpr float gravity = 0.003f;
constexpr float cor = 0.8f;
constexpr float vel_y_threshold = 0.2f;

Ball::Ball(float x, float y, int low_limit) : vel_(0.f, 0.f), shape_(sf::CircleShape(radius, 8)), y_limit_(low_limit), init_pos_(x, y)
{
	shape_.setPosition(x - radius, y - radius);
	shape_.setFillColor(sf::Color::Magenta);
}
void Ball::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}
void Ball::update(float deltaTime)
{
	// check collision status
	if (shape_.getPosition().y + 2*radius < y_limit_ || vel_.y < 0) {
		sf::Vector2f accel(0.f, gravity);
		vel_ += accel * deltaTime;
		shape_.move(0, vel_.y * deltaTime);
	}
	else {
		shape_.setPosition(shape_.getPosition().x, y_limit_ - 2*radius);
		if (vel_.y > vel_y_threshold) {
			vel_.y = -cor * vel_.y;
		}
		else {
			vel_.y = 0;
		}
		shape_.move(0, vel_.y * deltaTime);
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
void Ball::reset()
{
	shape_.setPosition(init_pos_);
	vel_ = sf::Vector2f(0.f, 0.f);
}
void Ball::setCollided(bool collided)
{
	if (collided) {
		shape_.setFillColor(sf::Color::Red);
	}
	else {
		shape_.setFillColor(sf::Color::Magenta);
	}
}
sf::Vector2f Ball::getPosition()
{
	return shape_.getPosition();
}