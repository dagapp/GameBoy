#ifndef SNAKE
#define SNAKE

#include "Program.hpp"

struct Coordinate
{
  int x = 0, y = 0;
};

class Snake : public Program
{
  private:
    Coordinate s[100];
    Coordinate Apple;

    const int size = 24, length = 10;
    int dir = 2, snakeLength = 4;
    bool GameOver = false;

  public:
    Snake() : Program("Змейка") { } 

    virtual void Begin() override { }
    virtual void End() override { }
    
    virtual void Process(Buttons * buttons) override
    {
      static bool to_draw = true;
      
      if (buttons->Up)
        dir = 0;
      if (buttons->Left)
        dir = 1;
      if (buttons->Down)
        dir = 2;
      if (buttons->Right)
        dir = 3;

      Graphics::ChangeColor();
      Graphics::Square(size * s[snakeLength - 1].x, size * s[snakeLength - 1].y, size, true); //Сделать с белой заливкой (против говняного следа)
      Graphics::ChangeColor(0, 0, 0);
      for (int i = snakeLength - 1; i > 0; --i)
        s[i] = s[i - 1];
      if (dir == 0)
        s[0].y -= 1;
      if (dir == 1)
        s[0].x -= 1;
      if (dir == 2)
        s[0].y += 1;
      if (dir == 3)
        s[0].x += 1;
      for (int i = 0; i < snakeLength; i++)
        Graphics::Square(size * s[i].x, size * s[i].y, size, true);

      if (s[0].x == Apple.x && s[0].y == Apple.y)
      {
        snakeLength += 1;
        Apple.x = rand() % length;
        Apple.y = rand() % length;
        Graphics::Square(size * Apple.x, size * Apple.y, size, true);
      }

      for (int i = snakeLength - 1; i > 0; --i)
        if (s[0].x == s[i].x && s[0].y == s[i].y)
          GameOver = true;

      for (int i = 0; i < snakeLength; i++)
      {
        if (s[i].x > length)
        {
          s[i].x = 0;
        }
        else if (s[i].x < 0)
        {
          s[i].x = length;
        }
        else if (s[i].y < 0)
        {
          s[i].y = length;
        }
        else if (s[i].y > length)
        {
          s[i].y = 0;
        }
      }

      if (to_draw)
      {
        Draw();
        to_draw = false;
      }
    }

    virtual void Draw() override
    {
      Graphics::Clear();
      
      /*for (int i = 0; i < length; i++)
        for (int j = 0; j < length; j++)
          Graphics::Square(size * i, size * j, size);*/

      for (int i = 0; i <= length; i++)
      {
        Graphics::Line(size * i,        0, size * i, size * length);
        Graphics::Line(       0, size * i, size * length, size * i);
      }
    }
};

#endif
