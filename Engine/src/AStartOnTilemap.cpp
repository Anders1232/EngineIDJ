#include <utility>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include "AStarOnTilemap.h"

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
	
	/*
	//lista  de caminhos <destino,<anterior,custo>>);
	std::list<std::pair<unsigned int ,std::pair<unsigned int,double> > > paths;
	//Lista para armazenar nós a serem processados
	std::list<std::pair<double,unsigned int> > process_list;
	//inicia o vetor de distâncias e de visitados
	std::vector<double> dist(graph.size(),INFINITE);
	std::vector<double> visitados(graph.size(),false);

	//a distância de orig para orig é 0
	dist[orig] = 0.0;
	process_list.push_back(std::make_pair(dist[orig],orig));
	paths.push_back(std::make_pair(orig,std::make_pair(orig,dist[orig])));

	unsigned int aux_dest,aux_origin,aux_cost,aux_node,actual_node_position;
	//Loop de processamento do djkstra
	while(!process_list.empty()){//essa condição iremos alterar para (achou o caminho desejado?)

		std::pair<double,unsigned int> p = process_list.front(); // extrai o pair do topo
		aux_node = p.second; // obtém o vértice do pair
		actual_node_position = find_node_position(aux_node,graph);
		process_list.pop_front(); // remove da fila

		if(!visitados[aux_node]){
			// percorre os vértices "v" adjacentes de "actual_node"
			for(unsigned int j = 0 ; j < graph[actual_node_position].adjacencias.size();j ++){
			// obtém um vértice adjacente e o custo da aresta
				
				aux_dest = graph[actual_node_position].adjacencias[j].destino;
				aux_cost = graph[actual_node_position].adjacencias[j].peso;
				
				if(dist[aux_dest] > dist[aux_node] + aux_cost){
				
					if (dist[aux_dest] != INFINITE){

						process_list.remove(std::make_pair(dist[aux_dest],aux_dest));
						paths.remove(std::make_pair(aux_dest,std::make_pair(aux_node, aux_cost)));

					}
					// atualiza a distância de "v" e insere na fila
					dist[aux_dest] = dist[aux_node] + aux_cost;
					paths.push_back(std::make_pair(aux_dest,std::make_pair(aux_node, aux_cost)));
					process_list.push_back(std::make_pair(aux_cost,aux_dest));

				}

			}
			visitados[aux_node] = true;
		}
		
	}

	//Deducao do caminho
	std::list<std::pair<unsigned int ,std::pair<unsigned int,double> > >::iterator it;
	std::list<unsigned int> path;
	unsigned int actual_node,aux_compare;
	actual_node = dest;
	
	while(actual_node != orig){
		
		for(it = paths.begin(); it != paths.end(); ++ it){
			
			if(it->first == actual_node){

				path.push_front(actual_node);
				actual_node = it->second.first;
				break;
				ROS_INFO("Atual: %d",actual_node);

			}
		}
	}

	return(path);*/
}
