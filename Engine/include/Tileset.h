#ifndef TILESET_H
#define TILESET_H

#include <string>
#include "Sprite.h"

using std::string;

/**
	\brief Classe responsável por modelar um tileset.

	Um tileSet é uma imagem que contém várias subimagens, que são idexadas por sua posição no arquivo.
*/
class TileSet
{
	public:
		/**
			\brief Instancia um tileSet.
			\param tileWidth Espessura de uma subimagem do tileSet.
			\param tileHeight Altura de uma subimagem do tileSet.
			\param file Nome do arquivo de imagem com o TileSet.

			Instancia o sprite interno com o arquivo informado, inicializa tileWidth e tileHeight com os argumentos dados.
			Depois, através do quociente da largura do spirte pelo tileWidth obtém-se o valor inicial de columns e similarmente usando a altura do sprite e o tileHeight, o valor inicial para rows.
		*/
		TileSet(int tileWidth, int tileHeight, string file);
		/**
			\brief Renderiza tile.
			\param index Índice do tile no tileSet.
			\param x Posição x onde o tile deve ser renderizado.
			\param y Posição y onde o tile deve ser renderizado.
			\param zoom Verdadeiro se o tile deve sofrer zoom, falso caso contrário.

			Usando aritmética de módulo conseguimos associar o index à uma posição (linha, coluna) na matriz de tiles.
			Essa informação é usada para entaão obter o x e y do tile no sprite.
			Após isso calcula-se o rect onde essa imagem será renderizada utilizando o x e y enviados como argumento e atribuindo a w e h tileWidth e tileHeight.
			Nesse momento verifica-se o o tile deve sofrer zoom, se sim, o rect calculado acima é multiplicado pelo valor de zoom armazenado na câmera.
			Após isso, renderiza-se o tile informado na posição calculada da tela.
		*/
		void Render(unsigned int index, float x, float y, bool zoom= true);
		/**
			\brief Obtém largura de um tile.
			\return Valor de tileWidth.

			Retorna tileWidth.
		*/
		int GetTileWidth(void);
		/**
			\brief Obtém altura de um tile.
			\return Valor de tileHeight.

			Retorna tileHeight.
		*/
		int GetTileHeight(void);
	private:
		Sprite tileSet;/**< Sprite com o tileSet em si.*/
		int rows;/**< Número de lilhas de tiles existentes no tileSet.*/
		int columns;/**< Número de colunas de tiles existentes no tileSet.*/
		int tileWidth;/**< Espessura de um tile.*/
		int tileHeight;/**< Altura de um tile.*/
};

#endif // TILESET_H
