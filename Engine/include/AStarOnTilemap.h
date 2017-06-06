#include "AStarHeuristic.h"
#include "TileMap.h"
#include <list>

template<typename T>

class AStarOnTilemap{
<<<<<<< HEAD

	public:

		AStarOnTilemap(int originTile,int destTile ,TileMap &tilemap,Heuristic heuristic);
		std::list<int> FindPath();

	private:

		int originTile,destTile;
		TileMap &tilemap;
		Heuristic heuristic;

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


=======
	AStarOnTilemap();
	std::list<int> operator()(int originTile,int destTile ,TileMap &tilemap, Heuristic heuristic, int tilePreferido, vector<int> &tilesAndaveis);
>>>>>>> 20d28b56f2d0255b1efff8315bf2a7bd5dafd614
};


