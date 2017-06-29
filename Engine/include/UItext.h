#ifndef UITEXT_H
#define UITEXT_H

#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE 
#define INCLUDE_SDL_MIXER 
#define INCLUDE_SDL_TTF 
#include "SDL_include.h"

#include "Rect.h"
#include "Timer.h"
#include "UIelement.h"

#include <memory>
#include <string>

using std::string;

#define MIN_TIME_SHOWN (0.15)
#define TEXT_FREQUENCY (0.25)

/**
	\brief Classe que modela textos.

	Os textos são lidos a partir de arquivos ttf, renderizados com base em um TextStyle, com um tamanho pré-informado e a partir de uma coordena (x, y).
	Internamente gerencia uma textura desse texto pré-renderizado.
*/
class UItext : public UIelement {
	public:
		/**
			\brief Informa como o texto será rendeizaddo.

			Informa os modos de renderizar um texto.
		*/
		enum TextStyle {
			SOLID,/**< O texto é renderizado diretamente, sem nenhum tipo de tratamento visual.*/
			SHARED,/**< o texto é renderizado em um retângulo da cor dada em um argumento SDL_Color no hora de renderizar.*/
			BLENDED/**< Cria um texto com as bordas suavizadas (usando o canal alpha), para que ele se adapte melhor à região da tela onde for renderizado. É mais custoso de se renderizar que os outros dois, mas faz
		uma diferença perceptível.*/
		};
		/**
			\brief Construtor
			\param fontFile Arquivo ttf da fonte.
			\param fontSize Tamanho da fonte.
			\param style Como o texto será renderizado, veja TextStyle para mais informações.
			\param color Cor do texto renderizado.
			\param isStrobing define se tempo deve piscar.
			\param x Coordenada x a partir do qual o texto deve ser renderizado.
			\param y Coordenada y a partir do qual o texto deve ser renderizado.

			Instância um Text com os argumentos informados.
		*/
		UItext
		(
			string fontFile,
			int fontSize,
			TextStyle style,
			SDL_Color color,
			string text,
			UIelement::BehaviorType behavior = UIelement::BehaviorType::FIT,
			bool isStrobing = false
		);
		/**
			\brief Destrutor

			Destrói o Text, a textura interna também é destruída para não ter memory leak.
		*/
		~UItext();
		/**
			\brief Update

			Atualiza o textTime.
		*/
		virtual void Update(float dt, Rect parentCanvas);
		/**
			\brief Renderiza Texto.

			Renderiza o texto na posição informada. Checa se o texto deve piscar e trata esta piscagem com o tempo textTime.
		*/
		virtual void Render(bool debugRender = false) const;
		/**
			\brief Altera o texto.

			Altera a posição do texto. Para essa modificação fazer efeito a textura precisa ser refeita.
		*/
		void SetText(string text);
		/**
			\brief Altera a cor.

			Altera a cor do texto. Para essa modificação fazer efeito a textura precisa ser refeita.
		*/
		void SetColor(SDL_Color color);
		/**
			\brief Altera o estilo.
			\todo Ver A viabilidade de adicionar um argumento SDL_color para o caso do novo estilo ser SHARED.

			Altera o estilo do texto. Para essa modificação fazer efeito a textura precisa ser refeita.
		*/
		void SetStyle(TextStyle style);
		/**
			\brief Altera o tamanho da fonte.

			Altera o estilo do texto. Para essa modificação fazer efeito a textura precisa ser refeita.
		*/
		void SetFontSize(int fontSize);
		/**
			\brief Obtém o tamanho do texto.

			Obtém o tamanho do texto em pixels.
		*/
		Vec2 GetSize(void) const;
		/**
			\brief Altera tempo mostrado enquanto pisca. 

			Altera o tempo em que o texto vai ser renderizado a cada ciclo de piscagem.
		*/
		void SetTimeShown(float newTime);
		/**
			\brief Altera tempo de piscagem.

			Altera o tempo total de cada ciclo de piscagem (tempo de texto sendo renderizado + tempo sem renderização).
		*/
		void SetStrobeFrequency(float fullTime);
		bool Is(std::string UItype) const;
	private:
		/**
			\brief Cria a textura que contém o texto

			Se existir um textura anteriormente, esta é destruída. Então uma nova é feita com base no estado atual do Text.
		*/
		void RemakeTexture(void);
		std::shared_ptr<TTF_Font> font;/**< Ponteiro para a fonte.*/
		SDL_Texture* texture;/**< O texto para exibir na tela precisa ser texturizado. Essa variável contém a textura do texto.*/
		string text;/**< String com o texto do Text.*/
		TextStyle style;/**< Forma com a qual o texto está texturizado*/
		int fontSize;/**< Tamanho da fonte do texto.*/
		SDL_Color color;/**< Cor do texto,*/
		Timer textTime;/**< Tempo para piscagem do texto*/
		string fontFile; /**< String com o nome do arquivo com a fonte. É necessário para o caso em que a fonte seja modificada.*/
		bool isStrobe;/**< Flag que determina se o texto deve piscar*/
		float strobeFrequency;/**< Tempo de um ciclo da piscagem. Seu valor é TEXT_FREQUENCY por padrão.*/
		float timeShown;/**< Tempo em que o texto é mostrado na piscagem. Seu valor é MIN_TIME_SHOWN por padrão.*/
};

#endif // UITEXT_H