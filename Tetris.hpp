#ifndef TETRIS
#define TETRIS

#include "Program.hpp"
#include "Point.hpp"

#define CELL  24
#define FIELD 10

#define FIGURE_SIZE   5
#define FIGURES_COUNT 7

#define TICK_LIMIT 1000

class Figure
{
  public:
  //private:
    bool Cells[FIGURE_SIZE][FIGURE_SIZE];
    Color565 * Color;

  //public:
    Figure(uint32_t config, Color565 * color) : Color(color)
    {
      /* Фигура представляется массивом 5x5 с указанием нахождения самой фигуры в каждой из этих клеток
       * _____________________
       * |_0_|_0_|_0_|_0_|_0_|
       * |_0_|_0_|_0_|_0_|_0_|  
       * |_0_|_0_|_1_|_0_|_0_| - массив для фигуры J
       * |_0_|_0_|_1_|_0_|_0_|
       * |_0_|_1_|_1_|_0_|_0_|
       * 
       * Для инициализации фигуры используется 4-байтовое число, кодирующее массив таким образом:
       * Делается проход по массиву (сверху-слева вправо-вниз) и в каждую ячейку записывается бит числа (от младшего к старшему)
       * При этом опорная клетка фигуры (вокруг которой происходит вращение) находится в центре
       * Таким образом фигуру J кодирует число 0b0000000000001000010001100 или 0x621000 или 6426624
       */
      for (int i = 0; i < FIGURE_SIZE; i++)
      {
        for (int j = 0; j < FIGURE_SIZE; j++)
        {
          Cells[i][j] = config & 1;
          config >>= 1;
        }
      }
    }
  
    void Rotate()
    {
      bool temp;
      
      /*for (int i = 0; i < FIGURE_SIZE; i++)
      {
        for (int j = 0; j < FIGURE_SIZE; j++)
        {
          temp = Cells[i][j];
          Cells[i][j] = Cells[j][2 - i];
          Cells[j][2 - i] = temp;
        }
      }*/
    }

    Color565 * GetColor()
    {
      return Color;
    }
  
    static Figure J;
    static Figure I;
    static Figure O;
    static Figure L;
    static Figure Z;
    static Figure T;
    static Figure S;
  
    static Figure * const Figures[FIGURES_COUNT];
};

Figure Figure::J(6426624,  &Color565::Blue);
Figure Figure::I(4329600,  &Color565::Cian);
Figure Figure::O(202752,   &Color565::Yellow);
Figure Figure::L(12718080, &Color565::Cian);
Figure Figure::Z(399360,   &Color565::Red);
Figure Figure::T(462848,   &Color565::Purple);
Figure Figure::S(208896,   &Color565::Green);

Figure * const Figure::Figures[7] = { &Figure::J, &Figure::I, &Figure::O, &Figure::L, &Figure::Z, &Figure::T, &Figure::S};

class Tetris : public Program
{
  private:
    Color565 *** Field;
    
    Figure * FigureCurrent;
    Point    FigurePos;

    void DropNewFigure()
    {
        FigureCurrent = Figure::Figures[random(FIGURES_COUNT)];
        FigurePos     = Point(random(FIELD - FIGURE_SIZE), 0);
    }

  public:
    Tetris() : Program("Тетрис"), Field(nullptr) { }

    virtual void Begin() override
    {
      //Инициализация поля белым цветом
      Field = new Color565 ** [FIELD];
      for (int i = 0; i < FIELD; i++) 
      {
        Field[i] = new Color565 * [FIELD + FIGURE_SIZE];
        for (int j = 0; j < FIELD + FIGURE_SIZE; j++)
        {
          Field[i][j] = &Color565::White;
        }
      }

      DropNewFigure();
    }

    virtual void End() override
    {
      for (int i = 0; i < FIELD; i++) delete [] Field[i];
      delete [] Field;
    }
    
    virtual void Process(Buttons * buttons) override
    {
      static uint16_t tick_count = 0;

      if (tick_count == TICK_LIMIT)
      {
        if      (buttons->Left)  FigurePos.X -= (FigurePos.X > 0)         ? 1 : 0;
        else if (buttons->Right) FigurePos.X += (FigurePos.X < FIELD - 1) ? 1 : 0;
        else if (buttons->Pick)  FigureCurrent->Rotate();
        else if (buttons->Down)  FigurePos.Y++;

        if (FigurePos.Y < FIELD - FIGURE_SIZE) FigurePos.Y++;
        else 
        {
          DropNewFigure();
        }

        tick_count = 0;
      
        Draw();
      }
      else
      {
        tick_count++;
      }
    }

    virtual void Draw() override
    {
      Graphics::Clear();

      Graphics::ChangeColor(Color565::Black);
      Graphics::Line(0, FIELD * CELL, WINDOW_WIDTH, FIELD * CELL);

      /*for (int i = 0; i < FIELD; i++)
      {
        for (int j = FIGURE_SIZE; j < FIELD + FIGURE_SIZE; j++)
        {
          Graphics::ChangeColor(*Field[i][j]);
          Graphics::Square(i * CELL, (j - FIGURE_SIZE) * CELL, CELL, true);
        }
      }*/

      Graphics::ChangeColor(*(FigureCurrent->Color));

      for (int i = 0; i < FIGURE_SIZE; i++)
      {
        for (int j = 0; j < FIGURE_SIZE; j++)
        {
          if (FigureCurrent->Cells[i][j]/* && FigurePos.Y >=*/)
          {
            Graphics::Square((FigurePos.X + j) * CELL, (FigurePos.Y + i) * CELL, CELL, true);
          }
        }
      }
    }
};

#endif
