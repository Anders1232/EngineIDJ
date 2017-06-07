#include "AStarHeuristic.h"
#include "TileMap.h"
#include <list>
#include <algorithm>
#include <memory>

template<typename T>

class my_priority_queue : public std::priority_queue<T, std::vector<T>>{
	public:
		bool remove(const T& value){
		auto it = std::find(this->c.begin(), this->c.end(), value);
		if (it != this->c.end()) {
			this->c.erase(it);
			std::make_heap(this->c.begin(), this->c.end(), this->comp);
			return true;
		}
		else {
			return false;
			}
		}
};


