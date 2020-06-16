#include "Ball.h"

constexpr float gravity = 0.003f;
constexpr float cor = 0.8f;
constexpr float vel_y_threshold = 0.2f;

Ball::Ball(float x, float y, int x_limit, int y_limit) : vel_(0.f, 0.f), shape_(sf::CircleShape(radius, 8)), x_limit_(x_limit), y_limit_(y_limit), init_pos_(x - radius, y - radius)
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
		shape_.move(vel_.x * deltaTime, vel_.y * deltaTime);
	}
	else { // collision with ground
		shape_.setPosition(shape_.getPosition().x, y_limit_ - 2*radius);
		if (vel_.y > vel_y_threshold) {
			vel_.y = -cor * vel_.y;
		}
		else {
			vel_.y = 0;
		}
		shape_.move(vel_.x * deltaTime, vel_.y * deltaTime);
	}
	if (shape_.getPosition().x + 2 * radius > x_limit_) {
		shape_.setPosition(x_limit_ - 2 * radius, shape_.getPosition().y);
		vel_.x = -cor * vel_.x;
	}
	else if (shape_.getPosition().x < 0) {
		shape_.setPosition(0.f, shape_.getPosition().y);
		vel_.x = -cor * vel_.x;
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