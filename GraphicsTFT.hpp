#ifndef GRAPHICS
#define GRAPHICS

#include <TFT.h>
#include <SPI.h>

#define CS 10
#define DC  9
#define RST 8

#define WINDOW_WIDTH  240
#define WINDOW_HEIGHT 320

class Graphics
{
  private:
    static TFT Screen;

    static void Transpose(int * x, int * y)
    {
      int t = *y;
      
      *y = WINDOW_WIDTH - *x;
      *x = t;
    }
    
  public:
    static void Begin()
    { 
      Screen.begin();
      Screen.background(0, 0, 0);
    }

    static void Stroke(int r, int g, int b)
    {
      Screen.stroke(r, g, b);
    }

    static void Text(const char * text, int x, int y)
    {
      Screen.text(text, x, y);
    }

    static void SetTextSize(int text_size)
    {
      Screen.setTextSize(text_size);
    }

    static void Background(int r, int g, int b)
    {
      Screen.background(r, g, b);
    }
  
    static void Point(int x, int y)
    {
      Transpose(&x, &y);
      Screen.point(x, y);
    }

    static void Line(int x1, int y1, int x2, int y2)
    {
      Transpose(&x1, &y1);
      Transpose(&x2, &y2);
      Screen.line(x1, y1, x2, y2);
    }

    static void Rect(int x, int y, int width, int height, bool fill = false)
    {
      x += width;
      Transpose(&x, &y);

      if (fill)
      {
        for (int i = x; i < height; i++)
        {
          for (int j = y; j < width; j++)
          {
            Screen.point(i, j);
          }
        }
      }
      else
      {
        Screen.rect(x, y, height, width);
      }
    }

    static void Circle(int x, int y, int radius, bool fill = false)
    {
      Transpose(&x, &y);
      if (fill)
      {
        for (int i = x - radius; i < x + radius; i++) //Возможно, не оптимизируется
        {
          for (int j = y - radius; j < y + radius; j++) //Аналогично
          {
            if (i * i + j * j <= radius * radius)
            {
              Screen.point(i, j);
            }
          }
        }
      }
      else
      {
        Screen.circle(x, y, radius);
      }
    }
};

TFT Graphics::Screen = TFT(CS, DC, RST);

#endif
