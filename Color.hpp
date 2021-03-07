#ifndef COLOR
#define COLOR

#define R_SIZE 5
#define G_SIZE 6
#define B_SIZE 5

#define R_MAX 31
#define G_MAX 63
#define B_MAX 31

#define COLORS_COUNT 11

class Color565
{
  private:
    uint8_t R : R_SIZE;
    uint8_t G : G_SIZE;
    uint8_t B : B_SIZE;
  
  public:
    Color565(uint8_t r = R_MAX, uint8_t g = G_MAX, uint8_t b = B_MAX) : R(r), G(g), B(b) { }
  
    uint16_t ToNumber() const
    {
      return (((((uint16_t) R) << G_SIZE) + ((uint16_t) G)) << B_SIZE) + ((uint16_t) B); 
    }
  
    static Color565 Black;
    static Color565 Red;
    static Color565 Green;
    static Color565 Blue;
    static Color565 Cian;
    static Color565 Yellow;
    static Color565 Orange;
    static Color565 Brown;
    static Color565 Purple;
    static Color565 Gray;
    static Color565 White;
  
    static Color565 * const Colors[COLORS_COUNT];
};

Color565 Color565::Black  = Color565(    0,     0,     0);
Color565 Color565::Red    = Color565(R_MAX,     0,     0);
Color565 Color565::Green  = Color565(    0, G_MAX,     0);
Color565 Color565::Blue   = Color565(    0,     0, B_MAX);
Color565 Color565::Cian   = Color565(    0, G_MAX, B_MAX);
Color565 Color565::Yellow = Color565(R_MAX, G_MAX,     0);
Color565 Color565::Orange = Color565(R_MAX,    38,     0);
Color565 Color565::Brown  = Color565(   23,    34,     0);
Color565 Color565::Purple = Color565(R_MAX,     0, B_MAX);
Color565 Color565::Gray   = Color565(   16,    33,    16);
Color565 Color565::White  = Color565(R_MAX, G_MAX, B_MAX);

Color565 * const Color565::Colors[COLORS_COUNT] = {
    &Color565::Black,
    &Color565::Red,
    &Color565::Green,
    &Color565::Blue,
    &Color565::Cian,
    &Color565::Yellow,
    &Color565::Orange,
    &Color565::Brown,
    &Color565::Purple,
    &Color565::Gray,
    &Color565::White,
};

#endif
