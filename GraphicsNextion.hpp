#ifndef GRAPHICS
#define GRAPHICS

#include <SoftwareSerial.h>

#include "Color.hpp"

#define WINDOW_WIDTH  240
#define WINDOW_HEIGHT 320

class Graphics
{
  public:
  //private:
    static SoftwareSerial NextionSerial;

    static Color DrawColor;

    static void CommandEnd()
    {
      for (int i = 0; i < 3; i++) NextionSerial.write(0xff);
    }
    
  //public:
    static void Begin()
    {
      NextionSerial.begin(9600);
      //DrawColor = Color::White;
    }

    static void Clear()
    {
      NextionSerial.print("cls WHITE");
      CommandEnd();
    }

    static void Stroke(uint8_t r, uint8_t g, uint8_t b)
    {
        //DrawColor = Color(r, g, b);
    }

    static void Text(const String text, uint8_t x, uint8_t y) { }

    static void SetTextSize(uint8_t text_size) { }

    static void Background(uint8_t r, uint8_t g, uint8_t b) { }
  
    static void Point(uint16_t x, uint16_t y) { }

    static void Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) 
    {
      String command = "line ";
      command += x1;
      command += ",";
      command += y1;
      command += ",";
      command += x2;
      command += ",";
      command += y2;
      command += ",";
      command += "BLACK";
      //command += DrawColor.ToNumber();

      NextionSerial.print(command);
      
      CommandEnd();
    }

    static void Rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, bool fill = false)
    {
      String command;
      
      if (fill)
      {
        command = "fill ";
        command += x;
        command += ",";
        command += y;
        command += ",";
        command += width;
        command += ",";
        command += height;
        command += ",";
        command += "BLACK";
        //command += DrawColor.ToNumber();

        NextionSerial.print(command);
        
        /*NextionSerial.print("fill ");
        
        NextionSerial.print(x);
        NextionSerial.print(",");
        
        NextionSerial.print(y);
        NextionSerial.print(",");

        NextionSerial.print(width);
        NextionSerial.print(",");
        
        NextionSerial.print(height);
        NextionSerial.print(",");

        NextionSerial.print("BLACK");*/
        CommandEnd();
      }
      else
      {
        command = "draw ";
        command += x;
        command += ",";
        command += y;
        command += ",";
        command += x + width;
        command += ",";
        command += y + height;
        command += ",";
        command += "BLACK";
        //command += DrawColor.ToNumber();

        NextionSerial.print(command);
        
        /*NextionSerial.print("draw ");
        
        NextionSerial.print(x);
        NextionSerial.print(",");
        
        NextionSerial.print(y);
        NextionSerial.print(",");

        NextionSerial.print(x + width);
        NextionSerial.print(",");
        
        NextionSerial.print(y + height);
        NextionSerial.print(",");

        NextionSerial.print("BLACK");*/
        CommandEnd();
      }
    }

    static void Square(uint16_t x, uint16_t y, uint16_t size, bool fill = false)
    {
      Rect(x, y, size, size, fill);
    }

    static void Circle(uint16_t x, uint16_t y, uint16_t radius, bool fill = false) { }
};

SoftwareSerial Graphics::NextionSerial = SoftwareSerial(8, 9);

#endif
