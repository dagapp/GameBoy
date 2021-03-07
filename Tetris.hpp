#ifndef TETRIS
#define TETRIS

#include "Program.hpp"

#define CELL  24
#define FIELD 10

#define FIGURE_SIZE   3
#define FIGURES_COUNT 7

class Figure
{
  private:
    bool Cells[FIGURE_SIZE][FIGURE_SIZE];
    Color565 * Color;

  public:
    Figure(uint8_t config)
    {
      /* Фигура представляется массивом 3х3 с указанием нахождения самой фигуры в каждой из этих клеток
       * __________________
       * |__0__|__1__|__0__|
       * |__0__|__1__|__0__|  - массив для фигуры J
       * |__1__|__1__|__0__|
       * 
       * Для инициализации фигуры используется 1-байтовое число, кодирующее массив таким образом:
       * Делается проход по массиву (сверху-слева вправо-вниз) и в каждую ячейку записывается бит числа (от младшего к старшему),
       * при это нижняя-правая ячейка игнорируется и выставляется в ноль (потому что число 8-битное, а таблица состоит из 9 ячееек)
       */
      for (int i = 0; i < FIGURE_SIZE; i++)
      {
        for (int j = 0; j < FIGURE_SIZE; j++)
        {
          if (i == 2 && j == 2) 
          {
            Cells[i][j] = 0;
          }
          else
          {
            Cells[i][j] = config & 1;
            config >>= 1;
          }
        }
      }
    }
  
    void Rotate()
    {
      bool temp;
      
      for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < 3; j++)
        {
          temp = Cells[i][j];
          Cells[i][j] = Cells[j][2 - i];
          Cells[j][2 - i] = temp;
        }
      }
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

Figure Figure::J(210);
Figure Figure::I(73);
Figure Figure::O(27);
Figure Figure::L(201);
Figure Figure::Z(51);
Figure Figure::T(58);
Figure Figure::S(30);

Figure * const Figure::Figures[7] = { &Figure::J, &Figure::I, &Figure::O, &Figure::L, &Figure::Z, &Figure::T, &Figure::S};

class Tetris : public Program
{
  private:
    Color565 *** Field;
    Figure * CurrentFigure;

  public:
    Tetris() : Program("Тетрис"), Field(nullptr) { }

    virtual void Begin() override
    {
      //Инициализация поля белым цветом
      Field = new Color565 ** [FIELD + 3];
      for (int i = 0; i < FIELD; i++) 
      {
        Field[i] = new Color565 * [FIELD];
        for (int j = 0; j < FIELD; j++)
        {
          Field[i][j] = &Color565::White;
        }
      }
    }

    virtual void End() override
    {
      for (int i = 0; i < FIELD; i++) delete [] Field[i];
      delete [] Field;
    }
    
    virtual void Process(Buttons * buttons) override
    {
      
    }

    virtual void Draw() override
    {
      Graphics::Clear();

      
    }
};

#endif
