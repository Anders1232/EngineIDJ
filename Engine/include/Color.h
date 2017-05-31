#ifndef COLOR_H
#define COLOR_H

struct Color {
  public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    Color();
    Color( unsigned char r, unsigned char g, unsigned char b );
};

#endif // COLOR_H