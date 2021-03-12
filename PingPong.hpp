#ifndef PINGPONG
#define PINGPONG

#include "Program.hpp"

#define lengthX 240
#define lengthY 180
#define size 45
#define PlayerSpeed 5
#define radius 4

struct Object
{
	int x = 0, y = 0;
};

class PingPong : public Program
{
  int BallSpeed = PlayerSpeed + 2;
	Object player1;
	Object player2;
	Object ball;
  //Object ball_speed;
  bool begin = true;
  bool clear = true;
	double phi; 

public:
  PingPong() : Program("ПингПонг") { } 
  
  virtual void Begin() override { }
  virtual void End() override 
  {
    begin = true;
    clear = true;
    player1.x = 0;
    player1.x = 0; 
    BallSpeed = PlayerSpeed + 2;
  }
    
	virtual void Process(Buttons* buttons) override
	{
    if (buttons->Up && (lengthY - size) / 2 + PlayerSpeed * player1.y - PlayerSpeed >= 0)
			player1.y--;
		if (buttons->Left && (lengthY - size) / 2 + PlayerSpeed * player2.y - PlayerSpeed >= 0)
			player2.y--;
		if (buttons->Down && (lengthY + size) / 2 + PlayerSpeed * player1.y <= lengthY)
			player1.y++;
		if (buttons->Right && (lengthY + size) / 2 + PlayerSpeed * player2.y <= lengthY)
			player2.y++;

		if (begin)
		{
      /*ball_speed.x = rand() % (2 * BallSpeed) - BallSpeed;
      if (ball_speed.x % 2 == 0)
      {
        if (ball_speed.x >= 0)
          ball_speed.y = BallSpeed - ball_speed.x;
        else
          ball_speed.y = BallSpeed + ball_speed.x;
      }
      else
      {
        if (ball_speed.x >= 0)
          ball_speed.y = -BallSpeed + ball_speed.x;
        else
          ball_speed.y = -BallSpeed - ball_speed.x;
      }*/
    
			phi = -180 + rand() % 360;
      
			ball.x = lengthX / 2;
			ball.y = lengthY / 2;
			begin = false;
		}

		if (ball.x - radius <= 10 && ball.y - 4 >= (lengthY - size) / 2 + PlayerSpeed * player2.y - PlayerSpeed && ball.y + 4 <= (lengthY + size) / 2 + PlayerSpeed * player2.y)
		{
			Graphics::ChangeColor(Color565::Black);
			Graphics::Circle(ball.x, ball.y, radius, true);
			ball.x = 10 + radius + 1;

      /*ball_speed.y = rand() % (2 * (BallSpeed - 2)) - BallSpeed + 2;
      if (ball_speed.y >= 0)
        ball_speed.x = BallSpeed - ball_speed.y;
      else 
        ball_speed.x = BallSpeed + ball_speed.y;*/
      
			phi = -70 + rand() % 140;
		}

		if (ball.x + radius >= lengthX - 10 && ball.y - 4 >= (lengthY - size) / 2 + PlayerSpeed * player1.y - PlayerSpeed && ball.y + 4 <= (lengthY + size) / 2 + PlayerSpeed * player1.y)
		{
			Graphics::ChangeColor(Color565::Black);
			Graphics::Circle(ball.x, ball.y, radius, true);
			ball.x = lengthX - 10 - radius - 1;

      /*ball_speed.y = rand() % (2 * (BallSpeed - 2)) - BallSpeed + 2;
      if (ball_speed.y >= 0)
        ball_speed.x = -BallSpeed + ball_speed.y;
      else
        ball_speed.x = -BallSpeed - ball_speed.y;*/
     
			phi = 110 + rand() % 140;
			if (phi > 180)
			{
				phi = phi - 360;
			}
		}

		if (ball.x - radius <= 0)
		{
			player1.x++;
			begin = true;
		}

		if (ball.x + radius >= lengthX)
		{
			player2.x++;
			begin = true;
		}

		if (ball.y - radius <= 0)
		{
			Graphics::ChangeColor(Color565::Black);
			Graphics::Circle(ball.x, ball.y, radius, true);
			ball.y = radius + 1;
			
      /*ball_speed.x = rand() % (2 * (BallSpeed - 2)) - BallSpeed + 2;
      if (ball_speed.x >= 0)
        ball_speed.y = BallSpeed - ball_speed.x;
      else
        ball_speed.y = BallSpeed + ball_speed.x;*/
      
			phi = -(-160 + rand() % 140);
		}

		if (ball.y + radius >= lengthY)
		{
			Graphics::ChangeColor(Color565::Black);
			Graphics::Rect(ball.x - radius, ball.y - radius, 2 * radius + 1, lengthY - ball.y + radius + 1, true);
			ball.y = lengthY - radius - 1;
			
			/*ball_speed.x = rand() % (2 * (BallSpeed - 2)) - BallSpeed + 2;
      if (ball_speed.x >= 0)
        ball_speed.y = -BallSpeed + ball_speed.x;
      else
        ball_speed.y = -BallSpeed - ball_speed.x;*/
			
			phi = -(20 + rand() % 140);
		}

		Draw();
	}

	virtual void Draw() override
	{
    if (clear)
    {
      Graphics::ChangeColor(Color565::Black);
      Graphics::Rect(0, 0, lengthX, lengthY, true);
      clear = false;
    }
    
		Graphics::ChangeColor(Color565::White);
		Graphics::Rect(lengthX - 10, (lengthY - size) / 2 + PlayerSpeed * player1.y, 10, size, true);
		Graphics::ChangeColor(Color565::Black);
	  Graphics::Rect(lengthX - 10, (lengthY - size) / 2 + PlayerSpeed * player1.y - PlayerSpeed, 10, PlayerSpeed, true);
		Graphics::Rect(lengthX - 10, (lengthY + size) / 2 + PlayerSpeed * player1.y + PlayerSpeed, 10, -PlayerSpeed, true);

		Graphics::ChangeColor(Color565::White);
		Graphics::Rect(0, (lengthY - size) / 2 + PlayerSpeed * player2.y, 10, size, true);
		Graphics::ChangeColor(Color565::Black);
		Graphics::Rect(0, (lengthY - size) / 2 + PlayerSpeed * player2.y - PlayerSpeed, 10, PlayerSpeed, true);
		Graphics::Rect(0, (lengthY + size) / 2 + PlayerSpeed * player2.y + PlayerSpeed, 10, -PlayerSpeed, true);

		Graphics::ChangeColor(Color565::Black);
		Graphics::Circle(ball.x, ball.y, radius, true);

    /*ball.x = ball.x + ball_speed.x;
    ball.y = ball.y + ball_speed.y;*/
    
		BallSpeed = PlayerSpeed + 2 + (player1.x + player2.x) / 2;
		if (BallSpeed > 12)
			BallSpeed = 12;
		ball.x = ball.x + BallSpeed * cos(phi * 3.14 / 180);
		ball.y = ball.y + BallSpeed * sin(phi * 3.14 / 180);
    
		Graphics::ChangeColor(Color565::White);
		Graphics::Circle(ball.x, ball.y, radius, true);

		/*char score[6];
		sprintf(score, "%d  %d", player2.x, player1.x);
		Graphics::ChangeColor(Color565::White);
		Graphics::Rect(lengthX / 2 - 20, lengthY - 20, 40, 20);
		Graphics::ChangeColor(Color565::Red);
		Graphics::Text(score, lengthX / 2 - 20, lengthY - 20, lengthX / 2 + 20, lengthY);*/
	}
};

#endif
