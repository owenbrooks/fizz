#include "Generator.h"
#include "Collision.h"
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
	if (instances_.size() > 1) {
		for (auto inst_it_a = instances_.begin(); inst_it_a != instances_.end() - 1; inst_it_a++) {
			for (auto inst_it_b = inst_it_a + 1; inst_it_b != instances_.end(); inst_it_b++) {
				const CollisionResult collision_res = Collision::collides(*inst_it_a, *inst_it_b);
				if (collision_res.collided) {
					(*inst_it_a).setCollided(true);
					(*inst_it_b).setCollided(true);
				}
				else {
					(*inst_it_a).setCollided(false);
					(*inst_it_b).setCollided(false);
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