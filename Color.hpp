#ifndef COLOR
#define COLOR

#define R_SIZE 5
#define G_SIZE 6
#define B_SIZE 5

#define R_MAX 31
#define G_MAX 63
#define B_MAX 31

struct Color
{
  uint8_t R : R_SIZE;
  uint8_t G : G_SIZE;
  uint8_t B : B_SIZE;

  Color(uint8_t r, uint8_t g, uint8_t b) : R(r), G(g), B(b) { }

  uint16_t ToNumber()
  {
    return ((((uint16_t) R) << G_SIZE) + ((uint16_t) G)) << B_SIZE + ((uint16_t) B); 
  }

  static const Color Black;
  static const Color Red;
  static const Color Green;
  static const Color Blue;
  static const Color White;
};

const Color Color::Black = Color(    0,     0,     0);
const Color Color::Red   = Color(R_MAX,     0,     0);
const Color Color::Green = Color(    0, G_MAX,     0);
const Color Color::Blue  = Color(    0,     0, B_MAX);
const Color Color::White = Color(R_MAX, G_MAX, B_MAX);

#endif
