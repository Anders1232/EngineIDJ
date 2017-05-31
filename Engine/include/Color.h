#ifndef COLOR_H
#define COLOR_H

/**
    \brief Struct para armazenar informações de cor

    Cor é uma struct cujo único propósito é permitir o armazenamento de informações de cor em uma variável só.
*/
struct Color {
  public:
    unsigned char r;/**< Canal R */
    unsigned char g;/**< Canal G */
    unsigned char b;/**< Canal B */
    /**
        \brief Cria um tipo para armazenar a cor [R,G,B]
        \param Intensidade do Canal Vermelho (Red) da cor
        \param Intensidade do Canal Verde (Green) da cor
        \param Intensidade do Canal Azul (Blue) da cor

        Essa struct representa uma cor de 8 bits. Ou seja, cada canal pode receber um número entre 0 (inclusive) e 255 (inclusive).
    */
    Color( unsigned char r, unsigned char g, unsigned char b );
};

#endif // COLOR_H