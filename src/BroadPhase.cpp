// Performs "broad-phase" collision detection using the sweep and prune algorithm
#include "BroadPhase.h"
#include "AABB.h"
#include <numeric>
#include <algorithm>
#include <list>

template<typename Func, typename Iterator>
void insertion_sort(Iterator begin, Iterator end, Func pred);

std::vector<std::pair<BallIt, BallIt>> BroadPhase::sweep_and_prune(std::vector<Ball>& bodies)
{
	// sort bounding boxes along x axis
	insertion_sort(bodies.begin(), bodies.end(),
		[](const Ball& first, const Ball& second) { return first.getAABB().min.x < second.getAABB().min.x; });

	// sweep along these bounding boxes, reporting collision candidates as they occur
	std::vector<std::pair<BallIt, BallIt>> candidates;
	std::list<BallIt> activeList = { bodies.begin() };
	for (auto currBody = bodies.begin() + 1, end = bodies.end(); currBody != end; ++currBody) {
		const auto currAABB = currBody->getAABB();
		if (activeList.size() > 0) {
			for (auto activeBodyIt = activeList.begin(); activeBodyIt != activeList.end();) {
				if ((*activeBodyIt)->getAABB().max.x > currAABB.min.x) {
					candidates.push_back(std::pair<BallIt, BallIt>(currBody, *activeBodyIt));
					++activeBodyIt;
				}
				else {
					activeBodyIt = activeList.erase(activeBodyIt);
				}
			}
			activeList.push_back(currBody);
		}
	}

	return candidates;
}

// Insertion sort used as it performs well on nearly-sorted lists
// For slow-moving objects, the order won't change much each between each time step
template<typename Func, typename Iterator>
void insertion_sort(Iterator begin, Iterator end, Func pred) {
    for (auto it = begin; it != end; ++it) {
        // 1. Search
        auto const insertion_point = std::upper_bound(begin, it, *it, pred);

        // 2. Insert
        std::rotate(insertion_point, it, it + 1);
    }
}
