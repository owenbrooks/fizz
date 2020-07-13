#include "Ball.h"

constexpr float vel_y_threshold = 0.2f;

Ball::Ball(sf::Vector2f initial_pos, sf::Vector2f boundary_limits, float radius, sf::Vector2f initial_vel, sf::Shape* shape, sf::Color color) : pos_(initial_pos), vel_(initial_vel), shape_(shape), x_limit_(boundary_limits.x), y_limit_(boundary_limits.y), init_pos_(initial_pos), radius(radius), inv_mass(radius* radius* density)
{
	shape_->setPosition(initial_pos.x - radius, initial_pos.y - radius);
	shape_->setFillColor(color);
}
void Ball::render(sf::RenderWindow& window)
{
	window.draw(*shape_);

	// Uncomment to draw bounding boxes for shapes
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

	// acceleration due to gravity
	if (config.gravityEnabled)
	{
		sf::Vector2f accel(0.f, gravity);
		vel_ += accel * deltaTime;
	}

	// check collision status
	if (pos_.y + radius > y_limit_ && vel_.y > 0) { // ground collision
		setPosition(sf::Vector2f(pos_.x, y_limit_ - radius));
		if (vel_.y > vel_y_threshold) {
			vel_.y = -cor * vel_.y;
		}
		else {
			vel_.y = 0;
		}
	}
	else if (config.topWallEnabled && pos_.y - radius < 0 && vel_.y < 0) { // top wall collision
		setPosition(sf::Vector2f(pos_.x, radius));
		vel_.y = -cor * vel_.y;
	}
	if (pos_.x + radius > x_limit_) { // right wall collision
		setPosition(sf::Vector2f(x_limit_ - radius, pos_.y));
		vel_.x = -cor * vel_.x;
	}
	else if (pos_.x < radius) { // left wall collision
		setPosition(sf::Vector2f(radius, pos_.y));
		vel_.x = -cor * vel_.x;
	}

	move(vel_ * deltaTime);
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