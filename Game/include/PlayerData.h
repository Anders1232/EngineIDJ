
#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include "GameObject.h"
#include "WaveManager.h"
#include "UItext.h"
#include "UItextButton.h"
#include "UIcanvas.h"
#include "UIverticalGroup.h"
#define PLAYER_DATA_INSTANCE PlayerData::GetInstance()

#define TOTAL_LIFES 30;

/**
	\brief Classe PlayerData armazena os dados do Jogador e exibe o quadro de pontos, vidas e gold do mesmo.

	 PlayerData funciona como uma singleton e eh chamada em StageState e WaveManager.
*/
class PlayerData: public Component{
	public:
		PlayerData();
		~PlayerData();
		void Render() const;
		void Update(float dt);
		bool Is(ComponentType type) const;
		void NotifyKillsUpdate(int wave, EnemyData enemyData);
		void NotifyLifeLost(int wave, EnemyData enemyData);
		void GoldUpdate(int amount);
		void PointsUpdate(int amount);
		static PlayerData& GetInstance(void);
		void DecrementLife(void);
		void CountNextWave(int wave);
		/** 
			\brief Pegar vidas Restantes.
			\return playerLifes: vidas restantes.
			Retorna as vidas restantes do jogador.
		*/
		int GetLifes(void);
    private:
		UIcanvas HUDcanvas;/**<Representa a area renderizavel na tela. Usado para renderizar o Quadro de pontos.*/
		UIverticalGroup playerTable;/**<Representa a Quadro de pontos. Usado para agrupar quantidade de vidas, ouro, pontos e mortes.*/
		UItext boardName;/**<Nome do Quadro de pontos. Renderizado como um atributo no quadro de pontos.*/
		UItext playerPoints;/**<Nome do Quadro de pontos. Renderizado como um atributo no quadro de pontos.*/
		UItext playerGold;/**<Representa ouro do jogador. Renderizado como um atributo no quadro de pontos.*/
		UItext playerKills;/**<Numero de inimigos mortos pelo jogador. Renderizado como um atributo no quadro de pontos.*/
		UItext playerLifes;/**<Numero de vidas do jogador. Renderizado como um atributo no quadro de pontos.*/
		UItext playerWave;/**<Contador de waves do jogador.*/

		int gold;/**<Representa a quantidade de ouro deo jogador. Ouro usado para comprar torres e ganho matando inimigos.*/
		uint kills;/**<Contador de inimigos matados.*/
		int lifes;/**<Contador de vidas do jogador. Representa uma tolerancia de quantos inimigos ainda podem passar.*/
		int points;/**<Contador de pontos do jogador. Pontuaçao do jogador. Matar inimigos e passar de wave aumenta os pontos e deixar inimigos passarem os diminui.*/
};


#endif