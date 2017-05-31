#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <vector>
#include "Tileset.h"
#include "Vec2.h"
#include "GameObject.h"

#define TILE_VAZIO -1
#define SPAWN_POINT (14)
#define COLLISION_LAYER (1)

using std::string;
using std::vector;

/**
	\brief Classe que modela o TileMap

	Gerencia um tileMap,internamente possui um tileSet que é usado para renderizar o mapa. Internamente possui três mapas: um para o tileSet, outro para colisão e um terceiro de GameObjects.
*/
class TileMap{
	public:
		/**
			\brief Construtor.
			\param tileSet TileSet que será usado pelo tileMap.
			\param file Arquivo com as informações do tileMap.
			\param collisionTileMapFile Arquivo com as informações do TileMap de colisão.
		
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
			\brief Obtém o índice do tileMap na posição informada
			\param index2D índice xy do tileMap,.tal como retornado pelo GetTileMousePos.
			\param layer Layer da qual queremos obter a informação existente em index2D.
			\return índice existente na posição (x, y, z do tileMap).
		
			O valor de retorno é um referência para a posição para que se possa permitir alteração externa.
			PS: Com grandes poderes vêm grandes responsabilidades.
		*/
		int& AtLayer(int index2D, int layer) const;
		/**
			\brief Renderiza o TileMap a partir da posição dada.
			\param cameraX Valor x da câmera, será usado como coordenada X de início do tileMap.
			\param cameraY Valor y da câmera, será usado como coordenada Y de início do tileMap.

			Renderiza-se todas as layers começando pelas de menor valor numérico de profundidade até as de maior valor numérico.
		*/
		void Render(int cameraX=0, int cameraY=0, bool parallax= false) const;
		/**
			\brief Renderiza a layer informada.
			\param layer Layer a ser renderizada.
			\param cameraX Valor x da câmera, será usado como coordenada X de início do tileMap.
			\param cameraY Valor y da câmera, será usado como coordenada Y de início do tileMap.

			Renderiza-se todas as posições da matriz na layer indicada, com suas alterações sendo feitas por parallaxe.
			Observação: pode exibir o tileMap de colisão se assim for pedido em ShowCollisionInfo.
		*/
		void RenderLayer(int layer, int cameraX=0, int cameraY=0, bool parallax= false) const;
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
		/**
			\brief Sobre qual tile o mouse está.
			\param mousePos posição do mouse, é passado como referência por motivos de performance
			\param affecteedByZoom verdadeiro se o tileMap está sofrendo zoom, falso caso contrário.
			\param layer layer no tileMap do qual se quer obter a posição.
			\todo Verificar se deve lançar exceção ao invés de retornar um valor negativo.

			Retorna o número de layers(profundidade) do tileMap.Retorna o índice da posição do tileMap relativo à posição do mouse, esse valor pode ser enviado ao método TileMap::At para saber o conteúdo da posição.
			O valor retornado será negativo e inválido se alguma coordenada do mouse tiver fora dos limites do tileMap.
			Internamente usa-se busca binária para achar o tile correspondente.
		*/
		int GetTileMousePos(Vec2 const &mousePos, bool affecteedByZoom, int layer)const;
		/**
			\brief Insere GameObjct no tileMap
			\param obj GameObject a ser inserido no tileMap de GameObjects.

			Utiliza a posição do mouse no momento(que deve ser a mesma do centro do GameObject) para identificar onde o GameObject deve ser colocado no tileMap de GameObjects. Então obj é colocado nessa posição, sua posição é alterada para se encaixar exatamente com o início da posição.
			Atualiza-se o tileMao de colisão para adicionar a informação que tem um GameObject na posição respectiva.
		*/
		void InsertGO(GameObject* obj);
		/**
			\brief Ativa ou desativa a exibição na tela das informações do tileMap de colisão

			Se show for verdadeiro, futuras chamadas à Render fará com que seja exibido o tileMap de colisão.
			Se shor for falso, futuras chamadas à Render não exibirão o tileMap de colisão.
		*/
		void ShowCollisionInfo(bool show);
		/**
			\brief Informa estado a exibição do tilemap de colisão.

			Retorna verdadeiro se o tileMap de colisão estiver sendo exibido, falso caso contrário.
		*/
		bool IsShowingCollisionInfo();
		/**
			\brief Obtém os spawnGroups com seus spawn points.
			\todo Verificar utilidade de usar define para buscar o spawn groups se de deve utilizar argumentos mesmo.
			\todo Resolver bug na detecção de adjacências.

			É responsabilidade do chamador desalocar o vector retornado.
		*/
		vector<vector<int>>* GetSpawnPositions(void) const;
		/**
			\brief Obtém o tamanho de um tile

			O tamanho retornado não leva em consideração zoom, mas leva em consideração escala.
		*/
		Vec2 GetTileSize(void) const;
	protected:
		/**
			\brief Carrega um arquivo das informações do timeMap.
			\param target Tilemap onde as informações do arquvio deve ser carregadas.
			\param setOfficialSize Verdadeiro se a largura, altura e profundiade lidas devem se tornar as oficiais do tilemap.

			O arquivo deve começar com 3 números: largura, altura e profundidade.
			Depois disso dever existir um números inteiros igual ao produto dos três números lidos organizados em layers, linhas e colunas.
			O argumento setOfficialSize deve ser verdadeiro se estiver lendo o arquivo de tileMap relativo com informações do tileSet.
		*/
		void Load(string file, std::vector<int> &target, bool setOfficialSize= false);
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
		std::vector<GameObject*> gameObjectMatrix;/**< TileMap linearizado de GameObjects*/	//bidimensional??
		bool displayCollisionInfo;/**<Verdadeiro se as informações de colisão devem ser exibidas no TileMap::Render, falso caso contrário.*/
};

#endif // TILEMAP_H
