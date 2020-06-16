#include "Generator.h"
#include "Collision.h"
#include <cmath>
#include "VecTools.h"
Generator::Generator(int x_limit, int y_limit) : x_limit_(x_limit), y_limit_(y_limit), instances_(), paused_(false)
{
}
void Generator::createBallAt(float x, float y)
{
	Ball newBall = Ball(x, y, x_limit_, y_limit_);
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
	if (paused_) {
		return;
	}
	if (instances_.size() > 1) {
		for (auto it_a = instances_.begin(); it_a != instances_.end() - 1; it_a++) {
			for (auto it_b = it_a + 1; it_b != instances_.end(); it_b++) {
				const CollisionResult collision_res = Collision::collides(*it_a, *it_b);
				(*it_a).setCollided(collision_res.collided);
				(*it_b).setCollided(collision_res.collided);
				if (collision_res.collided) {
					Collision::resolve_collision(*it_a, *it_b, collision_res);
				}
			}
		}
	}
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
void Generator::togglePaused()
{
	paused_ = !paused_;
}