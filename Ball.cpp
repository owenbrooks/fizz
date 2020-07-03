#include "Ball.h"

constexpr float vel_y_threshold = 0.2f;
unsigned int Ball::colorIndex = 0;

Ball::Ball(float x, float y, int x_limit, int y_limit, float radius, sf::Shape* shape) : pos_(x, y), vel_(0.f, 0.f), shape_(shape), x_limit_(x_limit), y_limit_(y_limit), init_pos_(x, y), radius(radius)
{
	shape_->setPosition(x - radius, y - radius);
	shape_->setFillColor(ballColors[colorIndex%7]);
	colorIndex++;
}
void Ball::render(sf::RenderWindow& window)
{
	window.draw(*shape_);

	//sf::RectangleShape boundingBoxRect(sf::Vector2f(2*radius, 2*radius));
	//AABB boundingBox = getAABB();
	////boundingBoxRect.setPosition(pos_ - sf::Vector2f(radius, radius));
	//boundingBoxRect.setPosition(boundingBox.min);
	//boundingBoxRect.setFillColor(sf::Color::Transparent);
	//boundingBoxRect.setOutlineColor(sf::Color::Green);
	//boundingBoxRect.setOutlineThickness(1.f);
	//window.draw(boundingBoxRect);
}
void Ball::update(float deltaTime, const ConfigState& config)
{
	const float gravity = config.gravity;
	const float cor = config.boundaryRestitution;
	// check collision status
	if (pos_.y + radius < y_limit_ || vel_.y < 0) {
		sf::Vector2f accel(0.f, gravity);
		vel_ += accel * deltaTime;
		move(vel_* deltaTime);
	}
	else { // collision with ground
		setPosition(sf::Vector2f(pos_.x, y_limit_ - radius));
		if (vel_.y > vel_y_threshold) {
			vel_.y = -cor * vel_.y;
		}
		else {
			vel_.y = 0;
		}
		move(vel_ * deltaTime);
	}
	if (pos_.x + radius > x_limit_) { // right wall collision
		setPosition(sf::Vector2f(x_limit_ - radius, pos_.y));
		vel_.x = -cor * vel_.x;
	}
	else if (pos_.x < radius) { // left wall collision
		setPosition(sf::Vector2f(radius, pos_.y));
		vel_.x = -cor * vel_.x;
	}
}
void Ball::move(sf::Vector2f vec)
{
	pos_ += vec;
	shape_->move(vec);
}
void Ball::setPosition(sf::Vector2<float> newPos) 
{
	pos_ = newPos;
	shape_->setPosition(newPos.x - radius, newPos.y - radius);
}
void Ball::setVelocity(sf::Vector2f newVel)
{
	vel_ = newVel;
}
void Ball::reset()
{
	shape_->setPosition(init_pos_ - sf::Vector2f(radius, radius));
	pos_ = init_pos_;
	vel_ = sf::Vector2f(0.f, 0.f);
}
void Ball::setCollided(bool collided)
{
	if (collided) {
		shape_->setFillColor(sf::Color::Red);
	}
	else {
		shape_->setFillColor(sf::Color::Magenta);
	}
}
sf::Vector2f Ball::getPosition()
{
	return pos_;
}
const AABB Ball::getAABB() const
{
	sf::Vector2f min(pos_.x - radius, pos_.y - radius);
	sf::Vector2f max(pos_.x + radius, pos_.y + radius);
	return AABB(min, max);
}