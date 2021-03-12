#ifndef SNAKE
#define SNAKE

#include "Program.hpp"

#define size 12
#define length 20

struct Coordinate
{
  int x = 0, y = 0;
};

class Snake : public Program
{
  private:
    Coordinate s[100];
    Coordinate Apple;

    int dir = 2, snakeLength = 4;
    bool GameOver = false;
    bool to_draw = true;

  public:
    Snake() : Program("Змейка") { } 

    virtual void Begin() override { }
    virtual void End() override 
    {
        GameOver = false;
        to_draw = true;
        dir = 2;
        snakeLength = 4;
        s[0].x = 0;
        s[0].y = 0; 
    }
    
    virtual void Process(Buttons * buttons) override
    {
      if (!GameOver)
      {
        if (buttons->Up)
            dir = 0;
        if (buttons->Left)
            dir = 1;
        if (buttons->Down)
            dir = 2;
        if (buttons->Right)
            dir = 3;

        Graphics::ChangeColor(Color565::Green);
        Graphics::Square(size * s[snakeLength - 1].x, size * s[snakeLength - 1].y, size, true); //Сделать с белой заливкой (против говняного следа)
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

        if (s[0].x == Apple.x && s[0].y == Apple.y)
        {
            snakeLength += 1;
            Apple.x = rand() % (length - 1);
            Apple.y = rand() % (length - 1);
            Graphics::ChangeColor(Color565::Red);
            Graphics::Square(size * Apple.x, size * Apple.y, size, true);
        }

        for (int i = snakeLength - 1; i > 0; --i)
            if (s[0].x == s[i].x && s[0].y == s[i].y)
                GameOver = true;
                
        if (s[0].x > length - 1 || s[0].x < 0 || s[0].y < 0 || s[0].y > length - 1)
        {
          for (int i = 0; i < snakeLength; i++)
          {
            if (s[i].x > length - 1)
            {
                s[i].x = 0;
            }
            else if (s[i].x < 0)
            {
                s[i].x = length - 1;
            }
            else if (s[i].y < 0)
            {
                s[i].y = length - 1;
            }
            else if (s[i].y > length - 1)
            {
                s[i].y = 0;
            }
          }
        }

        for (int i = 0; i < snakeLength; i++)
        {
            Graphics::ChangeColor(Color565::Orange);
            Graphics::Square(size * s[i].x, size * s[i].y, size, true);      
        }

        if (to_draw)
        {
            Draw();
            Apple.x = rand() % (length - 1);
            Apple.y = rand() % (length - 1);
            Graphics::ChangeColor(Color565::Red);
            Graphics::Square(size * Apple.x, size * Apple.y, size, true);
            to_draw = false;
        }
      }
      else
      {
        
      }
    }

    virtual void Draw() override
    {
      Graphics::Clear();
      
      /*for (int i = 0; i < length; i++)
        for (int j = 0; j < length; j++)
          Graphics::Square(size * i, size * j, size);*/

      Graphics::ChangeColor(Color565::Green);
      Graphics::Square(0, 0, size * length, true);

     /* for (int i = 0; i <= length; i++)
      {
        Graphics::Line(size * i,        0, size * i, size * length);
        Graphics::Line(       0, size * i, size * length, size * i);
      }*/
    }
};

#endif
