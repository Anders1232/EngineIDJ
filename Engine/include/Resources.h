#ifndef RESOURCES_H
#define RESOURCES_H

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

#include <string>
#include <unordered_map>
#include <memory>

using std::string;

/**
	\brief Classe estática responsável por gestão dos recursos em memória.
	\todo Ver com a monitora quando/como as músicas e sons devem ser alocados/desalocados.

	Esta classe gerencia o uso de memória, em especial implementa o reuso de imagens, músicas sons e fontes já carregadas. poupando tempo de carregameto e evita ter em memória recursos repetidos.
	Isso é feito mantendo fazendo o uso de tabelas de hash, onde cada elemento mapeado é um ponteiro compartilhado(shared_ptr).
*/
class Resources
{
	public:
		/**
			\brief Obtém o ponteiro para a imagem.
			\param file Nome do arquivo da imagem que se deseja abrir.
			\return Imagem carregada em memória

			Se a imagem em questão já  estiver em memória, um ponteiro para ela é enviado. Caso contrário ela é carregada, colocada no hash e então retornada.
			Ao se colocar a imagem no hash, criando o shared_ptr, um destrutor desse ponteiro é enviado como uma função lambda. Esse destrutor desaloca a imagem da memória.
		*/
		static std::shared_ptr<SDL_Texture> GetImage(string file);
		/**
			\brief Obtém o ponteiro para a música.
			\param file Nome do arquivo de música que se deseja abrir.
			\return Música carregada em memória

			Se a música em questão já  estiver em memória, um ponteiro para ela é enviado. Caso contrário ela é carregada, colocada no hash e então retornada.
			Ao se colocar a música no hash, criando o shared_ptr, um destrutor desse ponteiro é enviado como uma função lambda. Esse destrutor desaloca a música da memória.
		*/
		static std::shared_ptr<Mix_Music> GetMusic(string file);
		/**
			\brief Obtém o ponteiro para o áudio.
			\param file Nome do arquivo de áudio que se deseja abrir.
			\return Áudio carregado em memória

			Se o áudio em questão já  estiver em memória, um ponteiro para ele é enviado. Caso contrário ele é carregada, colocado no hash e então retornado.
			Ao se colocar o áudio no hash, criando o shared_ptr, um destrutor desse ponteiro é enviado como uma função lambda. Esse destrutor desaloca o áudio da memória.
		*/
		static std::shared_ptr<Mix_Chunk> GetSound(string file);
		/**
			\brief Obtém o ponteiro para a fonte.
			\param file Nome do arquivo de fonte que se deseja abrir.
			\param fontsize O tamanho requerido para a fonte.
			\return Fonte carregada em memória

			Se a fonte em questão já  estiver em memória no tamanho requerido, um ponteiro para ela é enviado. Caso contrário ela é carregada, colocada no hash e então retornada.
			Ao se colocar a fonte no hash, criando o shared_ptr, um destrutor desse ponteiro é enviado como uma função lambda. Esse destrutor desaloca a fonte da memória.
		*/
		static std::shared_ptr<TTF_Font> GetFont(string file, int fontSize);
		/**
			\brief Desaloca da memória os recursos que não estão em uso

			Internamente chama o ClearImages, ClearMusic, ClearSound e o ClearFonts. Veja a documentação de cada um desses métodos para mais informações.
		*/
		static void ClearResources(void);
	private:
		/**
			\brief Constutor privado que não deve ser implementado.

			Isso garante que qualquer tentativa de instanciar esse classe dará erro de ligação. Essa classe é totalmente estática.
		*/
		Resources();
		/**
			\brief Destrói as imagens não usadas da memória.

			A tabela de hash das imagens(imageTable) é percorrida e, se não houver nenhuma outra referência para essa imagem no programa, a imagem é destruída, chamando indiretamente a função lambda enviada na criação do shared_ptr.
		*/
		static void ClearImages(void);
		/**
			\brief Destrói as músicas não usadas da memória.

			A tabela de hash das músicas(musicTable) é percorrida e, se não houver nenhuma outra referência para essa imagem no programa, a música é destruída, chamando indiretamente a função lambda enviada na criação do shared_ptr.
		*/
		static void ClearMusic(void);
		/**
			\brief Destrói os sons não usadas da memória.

			A tabela de hash dos sons(soundTable) é percorrida e, se não houver nenhuma outra referência para esse som no programa,, o som é destruída, chamando indiretamente a função lambda enviada na criação do shared_ptr.
		*/
		static void ClearSound(void);
		/**
			\brief Destrói as fontes não usadas da memória.

			A tabela de hash das fontes(fontTable) é percorrida e, se não houver nenhuma outra referência para essa fonte no programa,, a fonte é destruída, chamando indiretamente a função lambda enviada na criação do shared_ptr.
		*/
		static void ClearFonts(void);
		static std::unordered_map<string, std::shared_ptr<SDL_Texture>> imageTable;/**< Tabela de hash com as texturas carregadas.*/
		static std::unordered_map<string, std::shared_ptr<Mix_Music>> musicTable;/**< Tabela de hash com as músicas carregadas.*/
		static std::unordered_map<string, std::shared_ptr<Mix_Chunk>> soundTable;/**< Tabela de hash com os sons carregados.*/
		static std::unordered_map<string, std::shared_ptr<TTF_Font>> fontTable;/**< Tabela de hash com as fontes carregadas. Cada combinação fonte-tamanho é uma entrada diferente no hash. Isso pe feito concatenando o tamanho da fonte ao nome do arquivo da mesma.*/
};

#endif // RESOURCES_H
