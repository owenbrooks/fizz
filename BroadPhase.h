#pragma once
#include <utility>
#include "Ball.h"

typedef std::vector<Ball>::iterator BallIt;

class BroadPhase
{
public:
	//static std::vector<std::pair<int, int>> sweep_and_prune(std::vector<Ball>& bodies);
	static std::vector<std::pair<BallIt, BallIt>> sweep_and_prune(std::vector<Ball>& bodies);
};

