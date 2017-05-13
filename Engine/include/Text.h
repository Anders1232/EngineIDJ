#ifndef TEXT_H
#define TEXT_H

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_mixer.h>
	#include <SDL_ttf.h>
#elif __APPLE__
	#include "TargetConditionals.h"
	//mac
#elif __linux__
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_mixer.h>
	#include <SDL2/SDL_ttf.h>
#else
	#error "Unknown compiler"
#endif

#include "Rect.h"
#include <memory>
#include <string>
using std::string;

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
	\brief Classe que modela textos.

	Os textos são lidos a partir de arquivos ttf, renderizados com base em um TextStyle, com um tamanho pré-informado e a partir de uma coordena (x, y).
	Internamente gerencia uma textura desse texto pré-renderizado.
*/
class Text {
	public:
		/**
			\brief Construtor
			\param fontFile Arquivo ttf da fonte.
			\param fontSize Tamanho da fonte.
			\param style Como o texto será renderizado, veja TextStyle para mais informações.
			\param color Cor do texto renderizado.
			\param x Coordenada x a partir do qual o texto deve ser renderizado.
			\param y Coordenada y a partir do qual o texto deve ser renderizado.

			Instância um Text com os argumentos informados.
		*/
		Text
		(
			string fontFile,
			int fontSize,
			TextStyle style,
			SDL_Color color,
			int x= 0,
			int y=0
		);
		/**
			\brief Destrutor

			Destrói o Text, a textura interna também é destruída para não ter memory leak.
		*/
		~Text();
		void Render(int CameraX=0, int cameraY=0) const;
		/**
			\brief Altera a posição do texto na tela
			\param centerX Verdadeiro caso queira que o texto se centralize horizontalmente. Falso caso contrário.
			\param centerY Verdadeiro caso queira que o texto se centralize verticalmente. Falso caso contrário.

			Altera a posição do texto na tela. Se centerX for verdadeiro o argumento y é ignorado. Caso contrário o argumento x será usado como coordenada x a partir do qual o texto será renderizado.
			Altera a posição do texto na tela. Se centerY for verdadeiro o argumento y é ignorado. Caso contrário o argumento y será usado como coordenada y a partir do qual o texto será renderizado.
		*/
		void SetPos(int x, int y, bool centerX=false, bool centerY=false);
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
		Vec2 GetSize(void)const;
	private:
		/**
			\brief Cria a textura que contém p texto

			Se existir um textura anteriormente a mesma e destruída. Então uma nova é feita com base no estado atual do Text.
		*/
		void RemakeTexture(void);
		std::shared_ptr<TTF_Font> font;/**< Ponteiro para a fonte.*/
		SDL_Texture* texture;/**< O texto para exibir na tela precisa ser texturizado. Essa variável contém a textura do texto.*/
		string text;/**< String com o texto do Text.*/
		TextStyle style;/**< Forma com a qual o texto está texturizado*/
		int fontSize;/**< Tamanho da fonte do texto.*/
		SDL_Color color;/**< Cor do texto,*/
		Rect box;/**< Posição a partir da qual o texto deve ser renderizado.*/
		string fontFile; /**< String com o nome do arquivo com a fonte. É necessário para o caso em que a fonte seja modificada.*/
};


#include "Resources.h"
#include "Game.h"
#include "Error.h"

#endif // TEXT_H
