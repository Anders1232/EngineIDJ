#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Vec2.h"

#define CAMERA_DEFAULT_MIN_ZOOM (0.3)
#define CAMERA_DEFAULT_MAX_ZOOM (1.5)
#define CAMERA_DEFAULT_ZOOMABLE (true)
#define CAMERA_DEFAULT_ZOOM_SPEED (5.0/200.)
#define CAMERA_DEFAULT_MIN_SPEED (150.)
#define CAMERA_DEFAULT_MAX_SPEED (500.)
/**
	\brief Classe que modela a câmera
	
	A Câmera contém informações sobre qual posição da tela deve ser renderizada, qual objeto deve ficar centralizado(caso necessário).
	Também é responsável por lidar o Zoom, rastreando informações como:
		- Zoom travado
		- Zoom atual
		- Velocidade de zoom
		- Zoom mínimo e máximo
*/
class Camera {
	public:
		/**
			\brief Coloca a câmera para seguir o GameObject enviado.
			\param newFocus objetos o qual a câmera deve acompanhar.
			
			Basicamente atribui newFocus ao focus.
		*/
		static void Follow(GameObject* newFocus);
		/**
			\brief Caso a câmera esteja seguindo um objeto, a câmera pare de seguir esse objeto.
			
			Basicamente atribui nullptr ao focus.
		*/
		static void Unfollow(void);
		/**
			\brief Atualiza o estado da câmera.
			\param dt Intervalo de tempo transcorrido do frame anterior para o grame atual.
			
			Uma série de operações devem ser feitas:
				- Se o mouse estiver seguindo algum GameObject, deve-se fazer o cálculo para que esse gameobject seja renderizado no centro tela levando em conta o zoom. Isso é calculado pela diferença:
					- Do Vec2 relativo centro do box do GameObject
					- Com a metade das dimensões da tela vezes o inverso do zoom da câmera.
				- Caso contrário, devemos mover a câmera com base no input do usuário. Essa movimentação é feita da seguinte forma:
					- Se a seta para a cima ou o botão "w" for pressionado decrementa-se o y da posição da câmera em Camera::speed * dt.
					- Se a seta para a esquerda ou o botão "a" for pressionado decrementa-se o x da posição da câmera em Camera::speed * dt.
					- Se a seta para a baixo ou o botão "s" for pressionado incrementa-se o y da posição da câmera em Camera::speed * dt.
					- Se a seta para a direita ou o botão "d" for pressionado incrementa-se o x da posição da câmera em Camera::speed * dt.
				- Se a rodinha do mouse(scroll) estiver em movimentação, chamar o método Camera::Zoom enviando o valor y do movimento feito no scroll.
		*/
		static void Update(float dt);
		/**
			\brief Ponto de início do que deve ser exibido na tela
			\todo Verificar viabilidade de tornar privado.
			
			Contém a informação do ponto no jogo que corresponde ao (0,0) da janela do jogo.
		*/
		static Vec2 pos;
		/**
			\brief Força um valor para o zoom.
			\param newZoom novo valor para o Zoom
			
			O valor informado se torna o zoom corrente. O novo valor do zoom pode extrapolar os limites existentes. Esse valor, mesmo que fora dos limites, será atribuído ao currentZoom.,
		*/
		static void ForceZoom(float newZoom);
		/**
			\brief Trava ou destrava o zoom.
			\param newZoom novo valor para o Zoom

			Caso o argumento da função seja true, as futuras chamadas à Zoom não terão mais efeito. Caso seja false as futuras chamadas à Zoom terão efeito. Esse efeito é obtido atribuindo à variável zoomFixed o oposto desse valor.
		*/
		static void SetZoomable(bool zoomable);
		/**
			\brief Altera o zoom corrente.
			\param deltaZoom Variação no zoom.

			O zoom corrente é alterado linearmente em deltaZoom*zoomSpeed. Só tem efeito se o valor de zoomFixed for falso.
			Se o novo valor para o zoom extrapolar o limite superior, o valor do limite superior será atribuído ao currentZoom.
			Se o novo valor para o zoom extrapolar o limite inferior, o valor do limite inferior será atribuído ao currentZoom.
		*/
		static void Zoom(float deltaZoom);
		/**
			\brief Estabelece os limites superior e inferior do zoom.
			\param minZoom Novo limite inferior.
			\param maxZoom Novo limite superior.

			Se o valor de minZoom ou maxZoom for zero, o valor default será atribuído no lugar.
		*/
		static void SetZoomLimits(float minZoom=0, float maxZoom=0);// set to 0 is to set to default
		/**
			\brief Informa o valor do zoom corrente.

			Se o valor for 1.0 significa que nenhum zoom está sendo aplicado.
			Se for maior que 1.0 significa que as imagens devem ser ampliadas.
			Se for menor que 1.0 significa que as imagens devem ser reduzidas.
		*/
		static float GetZoom(void);
		/**
			\brief Estabelece os limites superior e inferior da velocidade da câmera.
			\param minSpeed Novo limite inferior.
			\param maxSpeed Novo limite superior.

			Se o valor de minSpeed ou maxSpeed for zero, o valor default será atribuído no lugar.
		*/
		static void SetSpeedLimits(float minSpeed=0, float maxSpeed=0);
		static float GetMinSpeed(void);
		static float GetMaxSpeed(void);
		/**
			\brief Altera a sensibilidade do zoom.
			\param newZoomSpeed Novo valor para sensibilidade o zoom.

			Quanto maior o newZoomSpeed, mais sensível será o zoom.
			Quanto menor o newZoomSpeed, menos sensível será o zoom.
			Esse efeito é obtido atribuindo newZoomSpeed à zoomSpeed.
		*/
		static void SetZoomSpeed(float newZoomSpeed);
	private:
		/*! \brief Construtor privado que não deve ser implementado.
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
		static float minSpeed;/**< */
		static float maxSpeed;/**< */
		static float currentSpeed;/**< Armazena a velocidade de movimento da câmera quando não está focalizada em nenhum objeto.*/
};

#endif // CAMERA_H
