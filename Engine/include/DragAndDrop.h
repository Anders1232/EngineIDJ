#ifndef DRAGANDDROP_H
#define DRAGANDDROP_H

#include "Component.h"
#include "TileMap.h"
/**
	\brief Classe responsável por arrastar e posicionar Objetos.

	O DragAndDrop é um tipo de Componente. O objetivo do DragAndDrop é selecionar um objeto arrastavel por meio de Input e posicioná-lo em uma tile. E assim, atualizar o mapa de Tiles.
*/
class DragAndDrop : public Component{
	public:
		/**
			\brief Construtor.
			\param map Usado para inserir o objeto no tileMap.
			\param draggin Informa se o objeto esta sendo arrastado.
			\param dragOnActionHold Variável não utilizada, tem como objetivo verificar se o arrastar é enquanto o botão da ação é segurado ou se pressiona uma vez para arrastar e outra vez para soltar.
			\todo Implementar o dragOnActionHold.
		
			Instancia o DragAndDrop, informando se o objeto está sendo arrastado.
		*/
		DragAndDrop(TileMap *map,bool dragOnActionHold= true);
		/**
			\brief Atualiza o estado do objeto em arrasto.
			\param associated GameObject que possui esse componente.
			
			Nesse método a lógica do drag and drop é implementada. Se o botão do drag estiver sendo segurado o objeto é arrastado mantendo seu centro onde o mouse está. Quando o botão relativo ao drag and drop é liberado chama-se o tileMap para iserir o GameObject no tile onde o mouse está.
		*/
		void Update(GameObject &associated, float dt);
		/**
			\brief Informa que o tipo deste Compomente é DragAndDrop.
			\param CompomentType A ser comparado se é igual ao Tipo desta classe.
			
			Retorna Verdadeiro se CompomentType também é do tipo DragAndDrop, caso contrário retorna falso.
		*/
		bool Is(ComponentType) const;
	private:
		bool dragOnHold;/**< [Não utilizado no momento] Armazena a informação se o botão deve ser segurado para arrastar, ou apenas pressiona uma vez para arrastar e outra vez para soltar.*/
		TileMap *tileMap;/**< TileMap no qual o GameObject será inserido após o drag.*/
};

#endif // DRAGANDDROP_H
