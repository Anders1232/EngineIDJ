#ifndef COMPONENTTYPE_H
#define COMPONENTTYPE_H

/**
	\brief Tipos de Componentes

	Enumeração com os tipos de componentes possíveis, usado no método Is que todo componente deve implementar.
	Foi colocado em um arquivo separado por problemas de inclusão circular entre GameObject e Component.
*/
enum ComponentType{
	DRAG_AND_DROP=0,
	HIT_POINTS,
	AI_GO_DOWN,
	WAVE_MANAGER,
	SIZE,
	COMPONENT_TYPE_SIZE
};

#endif // COMPONENTTYPE_H
