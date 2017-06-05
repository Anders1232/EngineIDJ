#include "AStarOnTilemap.h"

std::list<int> AStarOnTilemap::operator()(int originTile,int destTile ,TileMap &tilemap,Heuristic heuristic){

	//lista  de caminhos <destino,<anterior,custo>>);
	std::list<std::pair<unsigned int ,std::pair<unsigned int,double> > > paths;
	//Lista para armazenar nós a serem processados
	std::list<std::pair<double,unsigned int> > process_list;
	//inicia o vetor de distâncias e de visitados
	std::vector<double> dist(tilemap.GetTileVector().size(),INFINITE);
	std::vector<double> visitados(tilemap.GetTileVector().size(),false);

	//a distância de orig para orig é 0
	dist[originTile] = 0.0;
	process_list.push_back(std::make_pair(dist[originTile],originTile));
	paths.push_back(std::make_pair(originTile,std::make_pair(originTile,dist[originTile])));

	unsigned int aux_dest,aux_origin,aux_cost,aux_node,actual_node_position;
	//Loop de processamento do A*

	while(1){

		std::pair<double,unsigned int> p = process_list.front(); // extrai o pair do topo
		process_list.pop_front(); // remove da fila

		if(p.second == destTile){

			paths.push_back(std::make_pair(p.second,std::make_pair(p_second, tilemap.GetTileVector()[p.second].weight)));
			break;

		}

		std::vector<unsigned int> neighbors = tilemap.GetNeighbors(p.second);

		// percorre os vértices "v" adjacentes de "actual_node"
		for(unsigned int j = 0 ; j < neighbors.size();j ++){
		// obtém um vértice adjacente e o custo da aresta
			if(visitados[neighbors[j]] || tilemap.GetTileVector()[p.second].traversable){

				continue;

			}

			aux_cost = tilemap.GetTileVector()[neighbors[j]].weight;
				
			if(dist[aux_dest] > dist[p.second] + aux_cost){
				
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

	return(path);
}
