#pragma once
#include <utility>
#include "Ball.h"
class BroadPhase
{
public:
	static std::vector<std::pair<int, int>> sweep_and_prune(const std::vector<Ball>& bodies);
};

