#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <vector>
#include "Tileset.h"

#define TILE_VAZIO -1

using std::string;

/**
	\brief Classe que modela o TileMap

	Gerencia um tileMap,internamente possui um tileSet que é usado para renderizar o mapa.
*/
class TileMap {
	public:
		/**
			\brief Construtor.
			\param tileSet TileSet que será usado pelo tileMap.
			\param file Arquivo com as informações do tileMap.
		
			Instancia o tileMap com o tileSet enviado e criar o tileMap lendo o arquivo enviado.
		*/
		TileMap(string file, TileSet *tileSet);
		/**
			\brief Obtém o índice do tileMap na posição informada
			\param x Posição X do tileMap
			\param y posição Y do tileMap.
			\param z posição z do tileMap.
			\return índice existente na posição (x, y, z do tileMap).
		
			O valor de retorno é um referência para a posição para que se possa permitir alteração externa.
			PS: Com grandes poderes vêm grandes responsabilidades.
		*/
		int& At(int x, int y, int z=0) const;
		/**
			\brief Renderiza o TileMap a partir da posição dada.
			\param cameraX Valor x da câmera, será usado como coordenada X de início do tileMap.
			\param cameraY Valor y da câmera, será usado como coordenada Y de início do tileMap.

			Renderiza-se todas as layers começando pelas de menor valor numérico de profundidade até as de maior valor numérico.
		*/
		void Render(int cameraX=0, int cameraY=0) const;
		/**
			\brief Renderiza a layer informada.
			\param layer Layer a ser renderizada.
			\param cameraX Valor x da câmera, será usado como coordenada X de início do tileMap.
			\param cameraY Valor y da câmera, será usado como coordenada Y de início do tileMap.

			Renderiza-se todas as posições da matriz na layer indicada, com suas alterações sendo feitas por parallaxe.
		*/
		void RenderLayer(int layer, int cameraX=0, int cameraY=0) const;
		/**
			\brief Informa a largura do tileMap.

			Retorna a largura do tileMap em posições.
		*/
		int GetWidth(void) const;
		/**
			\brief Informa a altura do tileMap.

			Retorna a altura do tileMap em posições.
		*/
		int GetHeight(void) const;
		/**
			\brief Informa o número de layers do tileMap.

			Retorna o número de layers(profundidade) do tileMap.
		*/
		int GetDepth(void) const;
	private:
		/**
			\brief Carrega um arquivo das informações do timeMap.

			O arquivo deve começar com 3 números: largura, altura e profundidade.
			Depois disso dever existir um números inteiros igual ao produto dos três números lidos organizados em layers, linhas e colunas.
		*/
		void Load(string file);
		/**
			\brief Altera o tileSet usado pelo tileMap

			O tileSet informado passa a ser usado pelo tileMap.
		*/
		void SetTileSet(TileSet *tileSet);
		/**
			\brief Calcula a paralaxe
			\param num coordenada a ser modificada.
			\param camera posição da mesma coordenada da câmera.
			\param layer Layer da coordenada que ser modificada
			\return Valor da coordenada alterado pela parallaxe.

			Ele subtrai da coordenada o produto da câmera pelo incremento da layer.
		*/
		int CalculateParallaxScrolling(int num, int camera, int layer) const;
		std::vector<int> tileMatrix;/**< Matriz tridimentsional de índices linearizados em um vetor.*/
		TileSet *tileSet;/**< TileSet utilizado para renderização.*/
		int mapWidth;/**< Largura do TileMap.*/
		int mapHeight;/**< Altura do TileMap.*/
		int mapDepth;/**< Número de camadas do TileMap.*/
};

#endif // TILEMAP_H
