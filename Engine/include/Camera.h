#ifndef CAMERA_H
#define CAMERA_H

#include "Gameobject.h"
#include "Vec2.h"

#define CAMERA_DEFAULT_MIN_ZOOM (0.7)
#define CAMERA_DEFAULT_MAX_ZOOM (1.5)
#define CAMERA_DEFAULT_ZOOMABLE (true)
#define CAMERA_DEFAULT_ZOOM_SPEED (5.0)
/*
	\brief A classe que modela a câmera
	
	A Câmera contém informações sobre qual posição da tela deve ser renderizada, qual objeto deve ficar centralizado(caso necessário).
	Também é responsável por lidar o Zoom, rastreando informações como:
		- Zoom travado
		- Zoom atual
		- Velocidade de zoom
		- Zoom mínimo e máximo
*/
class Camera
{
	public:
		static void Follow(GameObject* newFocus);
		static void Unfollow(void);
		static void Update(float dt);
		static Vec2 pos;
		static Vec2 speed;
		static void ForceZoom(float newZoom);
		static void SetZoomable(bool zoomable);
		static void Zoom(float deltaZoom);
		static void SetZoomLimits(float minZoom=0, float maxZoom=0);// set to 0 is to set to default
		static float GetZoom(void);
		static void SetZoomSpeed(float newZoomSpeed);
	private:
		/*! \brief Construtor privado não implementado.
		 *
		 *	Essa classe deve ser estática e se alguém tentar de alguma forma instanciar dará erro na compilação/ligação.
		 */
		Camera();
		static GameObject* focus;/**< Gameobject que ficará centralizado na câmera. Caso seja nullptr a câmera se moverá pelas setinhas/WASD.*/
		static float currentZoom;/**< Armazena o valor do zoom atual, informando em quantas vezes os objetos devem ser ampliados. Ele deve estar estre o minZoom e o maxZoom, a não ser que o método ForceZoom seja usado. Os métodos Zoom e ForceZoom alteram seu valor.*/
		static float minZoom;/**< Armazena o valor mínimo que o zoom pode ter. Esse limite é ignorado pelo método ForceZoom. É alterado pelo SetZoomLimits.*/
		static float maxZoom;/**< Armazena o valor mínimo que o zoom pode ter. Esse limite é ignorado pelo método ForceZoom. É alterado pelo SetZoomLimits.*/
		static bool zoomFixed;/**< Se for verdadeiro, o zoom não será alterado pelo método Zoom. Caso contrário o método Zoom pode mudar o valor corrente do zoom. É alterado pelo método SetZoomnable.*/
		static float zoomSpeed;/**< Armazena a velocidade com a qual o zoom deve ocorrer. O argumento do método Zoom é multiplicado por esse valor para depois ser somado ao currentZoom.*/
};

#endif // CAMERA_H
