#include "BroadPhase.h"
#include "AABB.h"
#include <numeric>
#include <algorithm>
#include <list>

std::vector<std::pair<int, int>> BroadPhase::sweep_and_prune(const std::vector<Ball>& bodies)
{
	std::vector<std::pair<int, int>> candidates;

	std::vector<int> bodyIndices(bodies.size());
	std::iota(std::begin(bodyIndices), std::end(bodyIndices), 0); // fill bodyIndices with numbers 0 onwards

	std::vector<AABB> boundingBoxes;
	std::transform(bodies.begin(), bodies.end(), std::back_inserter(boundingBoxes), 
		[](const Ball& body) { return body.getAABB(); });

	// sweep along x axis
	std::sort(bodyIndices.begin(), bodyIndices.end(), 
		[boundingBoxes](int a, int b) { return boundingBoxes[a].min.x < boundingBoxes[b].min.x; });

	std::list<int> activeList = { bodyIndices[0] };
	for (auto currBody = bodyIndices.begin() + 1; currBody != bodyIndices.end(); ++currBody) {
		if (activeList.size() > 0) {
			for (auto activeBodyIt = activeList.begin(); activeBodyIt != activeList.end();) {
				if (boundingBoxes[*activeBodyIt].max.x > boundingBoxes[*currBody].min.x) {
					candidates.push_back(std::pair<int, int>(*currBody, *activeBodyIt));
					++activeBodyIt;
				}
				else {
					activeBodyIt = activeList.erase(activeBodyIt);
				}
			}
			activeList.push_back(*currBody);
		}
	}
	
	return candidates;
}

template<typename Func>
void insertion_sort(std::vector<int>& array, Func pred) {
    for (auto it = array.begin(), end = array.end(); it != end; ++it) {
        // 1. Search
        auto const insertion_point = std::upper_bound(array.begin(), it, *it, pred);

        // 2. Insert
        std::rotate(insertion_point, it, it + 1);
    }
}
