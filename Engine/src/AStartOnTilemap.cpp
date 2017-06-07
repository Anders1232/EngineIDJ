#include <utility>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include "AStarOnTilemap.h"

AStarOnTilemap::AStarOnTilemap(int originTile,int destTile ,TileMap &tilemap, AStarHeuristic *heuristic):
	originTile(originTile),
	destTile(destTile),
	tilemap(tilemap),
	heuristic(heuristic){
}

struct LessThanByHeuristic{
	bool operator()(const std::pair<double,unsigned int> lhs,const std::pair<double,unsigned int> rhs) const{
		return lhs.second + heuristic((lhs.first,destTile,tilemap)) < rhs.second + heuristic((rhs.first,destTile,tilemap));
	}
};

/*
struct Node{
	public:
//		int id;//precisa ter id??
		int weight;
		int cameFrom;
		Node(int weigth, int cameFrom);
		operator<(Node &other);
}

Node::Node(int weigth, int cameFrom):weigth(weight), cameFrom(cameFrom){
}


std::list<int> AStarOnTilemap::operator()(int originTile,int destTile ,TileMap &tilemap,Heuristic heuristic, int tilePreferido, vector<int> *tilesAndaveis){
	std::map<int, std::unique_ptr<Node>> nosAvaliados;
	std::priority_queue<std::pair<int, Node> > nosDescobertos;// e nao avaliados
	std::vector<>

};*/

std::list<int> AStarOnTilemap::FindPath(){
	//lista  de caminhos <destino,<anterior,custo>>);
	std::list<std::pair<unsigned int ,std::pair<unsigned int,double> > > paths;
	//Heap para armazenar nós a serem processados
	my_priority_queue<std::pair<double,unsigned int> > processList(LessThanByHeuristic);
	//inicia o vetor de distâncias e de visited
	std::vector<double> dist(tilemap.GetTileVector().size(),INFINITE);
	std::vector<double> visited(tilemap.GetTileVector().size(),false);
	//a distância de orig para orig é 0
	dist[originTile] = 0.0;
	//Inicializa listas de processamento e de caminhos
	processList.emplace(std::make_pair(dist[originTile],originTile));
	paths.push_back(std::make_pair(originTile,std::make_pair(originTile,dist[originTile])));

	//Loop de processamento do Djkistra
	while(!processList.empty()){
		//Seleciona o nó com menor custo fazendo assim uma busca guiada(A*)
		std::pair<double,unsigned int> current = processList.top();
		processList.pop();// remove da lista
		//Obtém todos os vizinhos de "current"
		std::vector<unsigned int> neighbors = tilemap.GetNeighbors(current.second);
		// percorre os vértices "v" adjacentes de "current"
		for(unsigned int j = 0 ; j < neighbors.size();j ++){
			//Se o vértice já foi visitado ou não é atingível passa-se para o proximo
			if(visited[neighbors[j]] || !tilemap.GetTileVector()[neighbors[j]].traversable){continue;}
			//Obtem o custo do vizinho atual
			aux_cost = tilemap.GetTileVector()[neighbors[j]].weight;
			//Verifica se o custo do caminho a partir de current é menor que o registrado no vizinho
			if(dist[neighbors[j]] > dist[p.second] + aux_cost){
				//Caso o vizinho já tenha sido processado em alguma iteração
				if (dist[neighbors[j]] != INFINITE){
					//Remove o custo e o caminho associado ao vizinho das listas visto que novos serão inseridos
					processList.remove(std::make_pair(dist[neighbors[j]],neighbors[j]));
					paths.remove(std::make_pair(aux_dest,std::make_pair(aux_node,aux_cost)));
				}
				// atualiza a distância do vizinho e insere nas listas
				dist[neighbors[j]] = dist[p.second] + aux_cost;
				paths.push_back(std::make_pair(neighbors[j],std::make_pair(p.second,aux_cost)));
				processList.push_back(std::make_pair(aux_cost,neighbors[j]));
			}
		}
		visited[current.second] = true;
	}
	//Deducao do caminho
	std::list<std::pair<unsigned int ,std::pair<unsigned int,double> > >::iterator it;
	std::list<unsigned int> path;
	unsigned int actual_node,aux_compare;
	actual_node = destTile;
	
	while(actual_node != originTile){
		for(it = paths.begin(); it != paths.end(); ++ it){
			if(it->first == actual_node){
				path.push_front(actual_node);
				actual_node = it->second.first;
				break;
			}
		}
	}
	return(path);
}

