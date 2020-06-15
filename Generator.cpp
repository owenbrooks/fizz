#include "Generator.h"

Generator::Generator(int low_limit) : low_limit_(low_limit), instances_()
{
}
void Generator::createBallAt(float x, float y)
{
	Ball newBall = Ball(x, y, low_limit_);
	instances_.push_back(newBall);
	if (instances_.size() > 1000) {
		instances_.erase(instances_.begin());
	}
}
void Generator::render(sf::RenderWindow& window)
{
	for (auto& inst : instances_) {
		inst.render(window);
	}
}
void Generator::update(float deltaTime)
{
	for (auto& inst : instances_) {
		inst.update(deltaTime);
	}
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