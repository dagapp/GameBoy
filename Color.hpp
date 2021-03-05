#ifndef COLOR
#define COLOR

struct Color
{
  uint8_t R, G, B;

  Color(uint8_t r, uint8_t g, uint8_t b) : R(r), G(g), B(b) { }

  static const Color Black;
  static const Color Red;
  static const Color Green;
  static const Color Blue;
  static const Color White;
};

const Color Color::Black = Color(  0,   0,   0);
const Color Color::Red   = Color(255,   0,   0);
const Color Color::Green = Color(  0, 255,   0);
const Color Color::Blue  = Color(  0,   0, 255);
const Color Color::White = Color(255, 255, 255);

#endif
