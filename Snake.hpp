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

	  const int size = 4, length = 60;
	  int dir = 2, snakeLength = 4;
	  bool GameOver = false;

  public:
    virtual void Process(Buttons * buttons) override
    {
		if (buttons->Up)
			dir = 0;
		if (buttons->Left)
			dir = 1;
		if (buttons->Down)
			dir = 2;
		if (buttons->Right)
			dir = 3;

    Graphics::Rect(size * s[snakeLength - 1].x, size * s[snakeLength - 1].y, size, size);
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
			Graphics::Rect(size * s[i].x, size * s[i].y, size, size, true);

		if (s[0].x == Apple.x && s[0].y == Apple.y)
		{
			snakeLength += 1;
			Apple.x = rand() % length;
			Apple.y = rand() % length;
		  Graphics::Rect(size * Apple.x, size * Apple.y, size, size, true);
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
			if (s[i].x < 0)
			{
				s[i].x = length;
			}
			if (s[i].y < 0)
			{
				s[i].y = length;
			}
			if (s[i].y > length)
			{
				s[i].y = 0;
			}
		}
    }

    virtual void Draw() override
    {
        for (int i = 0; i < length; i++)
          for (int j = 0; j < length; j++)
            Graphics::Rect(size * i, size * j, size, size);
    }
};

#endif
