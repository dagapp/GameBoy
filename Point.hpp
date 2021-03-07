#ifndef POINT
#define POINT

struct Point
{
  uint16_t X = 0, Y = 0;

  Point(uint16_t x = 0, uint16_t y = 0) : X(x), Y(y) { }
};

#endif
