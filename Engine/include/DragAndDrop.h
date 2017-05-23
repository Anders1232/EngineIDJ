#ifndef DRAGANDDROP_H
#define DRAGANDDROP_H

#include "Component.h"
#include "TileMap.h"
/**
	\brief Classe responsavel por arrastar e posicionar Objetos.

	O DragAndDrop e´ um tipo de Componente. O objetivo do DragAndDrop é Selecionar um objeto arrastavel por meio de Input e posiciona-lo em uma tile. E assim, atualizar o mapa de Tiles.
*/
class DragAndDrop : public Component
{
	public:
		/**
			\brief Construtor.
			\param *map será usado para inserir o objeto no tileMap.
			\param draggin flag booleana. Informa se o objeto esta sendo arrastado.
			\param dragOnActionHold flag booleana. Informa se o clique de deploy com objeto sendo arrastado esta sendo pressionado.
		
			Instancia o tileMap com o tileSet enviado e criar o tileMap lendo o arquivo enviado.
		*/		
		DragAndDrop(TileMap *map, bool dragging= false, bool dragOnActionHold= true);
		/**
			\brief Atualiza o estado do objeto em arrasto.
			\param associated. Referencia ao objeto sendo arrastado. Usado para atualizar seu estado e posiçao

		*/
		void Update(GameObject &associated);
		/**
			\brief Informa que o tipo deste Compomente é DragAndDrop.
			\param CompomentType. A ser comparado se é igual ao Tipo desta classe.
			\return Verdadeiro se CompomentType também é do tipo DragAndDrop. Falso, caso contrário.
		*/		
		bool Is(ComponentType) const;
	private:

		bool isDragging;/**< Flag booleana. Indica se o objeto esta sendo arrastado.*/
		bool dragOnHold;/**< Flag booleana. Indica se o Input esta sendo segurado para poder arrastar.*/
		TileMap *tileMap;/**< Referencia ao tileMap para inserir o Objeto no tilemap inserido.*/
};

#endif // DRAGANDDROP_H
