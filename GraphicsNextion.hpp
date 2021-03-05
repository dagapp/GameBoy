#ifndef GRAPHICS
#define GRAPHICS

#include <SoftwareSerial.h>

#define WINDOW_WIDTH  240
#define WINDOW_HEIGHT 320

class Graphics
{
  public:
  //private:
    static SoftwareSerial NextionSerial;

    static void CommandEnd()
    {
      for (int i = 0; i < 3; i++) NextionSerial.write(0xff);
    }
    
  //public:
    static void Begin()
    {
      NextionSerial.begin(9600);
    }

    static void Clear()
    {
      NextionSerial.print("cls WHITE");
      CommandEnd();
    }

    static void Stroke(int r, int g, int b) { }

    static void Text(const char * text, int x, int y) { }

    static void SetTextSize(int text_size) { }

    static void Background(int r, int g, int b) { }
  
    static void Point(int x, int y) { }

    static void Line(int x1, int y1, int x2, int y2) { }

    static void Rect(int x, int y, int width, int height, bool fill = false)
    {
      if (fill)
      {
        NextionSerial.print("fill ");
        
        NextionSerial.print(x);
        NextionSerial.print(",");
        
        NextionSerial.print(y);
        NextionSerial.print(",");

        NextionSerial.print(width);
        NextionSerial.print(",");
        
        NextionSerial.print(height);
        NextionSerial.print(",");

        NextionSerial.print("BLACK");
        CommandEnd();
      }
      else
      {
        NextionSerial.print("draw ");
        
        NextionSerial.print(x);
        NextionSerial.print(",");
        
        NextionSerial.print(y);
        NextionSerial.print(",");

        NextionSerial.print(x + width);
        NextionSerial.print(",");
        
        NextionSerial.print(y + height);
        NextionSerial.print(",");

        NextionSerial.print("BLACK");
        CommandEnd();
      }
    }

    static void Circle(int x, int y, int radius, bool fill = false) { }
};

SoftwareSerial Graphics::NextionSerial = SoftwareSerial(8, 9);

#endif
