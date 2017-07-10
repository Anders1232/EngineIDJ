
#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include "GameObject.h"
#include "WaveManager.h"
#include "UIelement.h"
#include "UItext.h"
#include "UItextButton.h"
#include "UIcanvas.h"
#include "UIverticalGroup.h"
#include "UIhorizontalGroup.h"
#include "UIimage.h"

#define PLAYER_DATA_INSTANCE PlayerData::GetInstance()

#define TOTAL_LIFES 30
#define START_MONEY 150
/**
	\brief Classe PlayerData armazena os dados do Jogador e exibe o quadro de pontos, vidas e gold do mesmo.

	 PlayerData funciona como uma singleton e eh chamada em StageState e WaveManager.
*/
class PlayerData: public Component {
	public:
		static PlayerData& GetInstance(void);
        ~PlayerData();
		void Render() const;
		void Update(float dt);
		bool Is(ComponentType type) const;
		static void Reset(void);
		void GoldUpdate(int amount, bool winPoints=true);
		void PointsUpdate(int amount);
		void IncrementKills(void);
		void DecrementLife(void);
		int GetGold(void);
		int GetLifes(void);
		int GetKills(void);
		int GetPoints(void);
    private:
        PlayerData();
		static PlayerData* instance;
		int gold;/**<Representa a quantidade de ouro deo jogador. Ouro usado para comprar torres e ganho matando inimigos.*/
		uint kills;/**<Contador de inimigos matados.*/
		int lifes;/**<Contador de vidas do jogador. Representa uma tolerancia de quantos inimigos ainda podem passar.*/
		int points;/**<Contador de pontos do jogador. Pontuaçao do jogador. Matar inimigos e passar de wave aumenta os pontos e deixar inimigos passarem os diminui.*/
};


#endif