#ifndef GRAPHICS
#define GRAPHICS

#include <SoftwareSerial.h>

#include "Color.hpp"

#define NEXTION_TX 8
#define NEXTION_RX 9

#define WINDOW_WIDTH  240
#define WINDOW_HEIGHT 320

enum XAllign
{
  Left, XCentered, Right
};

enum YAllign
{
  Top, YCentered, Bottom
};

class Graphics
{
  public:
  //private:
    static SoftwareSerial NextionSerial;

    static Color565 Color;

    static void CommandEnd()
    {
      for (int i = 0; i < 3; i++) NextionSerial.write(0xff);
    }
    
  //public:
    static void Begin()
    {
      NextionSerial.begin(9600);
      Color = Color565::White;
      Clear();
    }

    static void Clear(uint8_t r = R_MAX, uint8_t g = G_MAX, uint8_t b = B_MAX)
    {
      String command = "cls ";
      command += Color565(r, g, b).ToNumber();
      NextionSerial.print(command);

      CommandEnd();
    }

    static void Stroke(uint8_t r = R_MAX, uint8_t g = G_MAX, uint8_t b = B_MAX) //---//Выбрать подхлдящее название
    {
        Color = Color565(r, g, b);
    }
    
    static void ChangeColor(uint8_t r = R_MAX, uint8_t g = G_MAX, uint8_t b = B_MAX) //Среди этих двух функций
    {
        Color = Color565(r, g, b);
    }

    static void ChangeColor(Color565 color)
    {
        Color = color;
    }

    static void Text(const String text, uint16_t x = 0, uint16_t y = 0, uint16_t width = WINDOW_WIDTH, uint16_t height = WINDOW_HEIGHT, Color565 fore = Color565::Black, uint8_t font = 1, XAllign x_all = XCentered, YAllign y_all = YCentered) 
    {
        String command = "";
        
        command += "xstr ";
        command += x;
        command += ",";
        command += y;
        command += ",";
        command += width;
        command += ",";
        command += height;
        command += ",";
        command += font;
        command += ",";
        command += fore.ToNumber();
        command += ",";
        command += Color565::White.ToNumber();
        command += ",";
        command += x_all;
        command += ",";
        command += y_all;
        command += ",";
        command += 3;
        command += ",\"";
        command += text;
        command += "\"";

        CommandEnd();
    }

    static void SetTextSize(uint8_t text_size) { }

    static void Background(uint8_t r = R_MAX, uint8_t g = G_MAX, uint8_t b = B_MAX) { }
  
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
      command += Color.ToNumber();

      NextionSerial.print(command);
      CommandEnd();
    }

    static void Rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, bool fill = false)
    {
      String command = "";
      
      if (fill)
      {
        command += "fill ";
      }
      else
      {
        command += "draw ";

        width  += x;
        height += y;
      }
      
      command += x;
      command += ",";
      command += y;
      command += ",";
      command += width;
      command += ",";
      command += height;
      command += ",";
      command += Color.ToNumber();
      
      NextionSerial.print(command);
      CommandEnd();
    }

    static void Square(uint16_t x, uint16_t y, uint16_t size, bool fill = false)
    {
      Rect(x, y, size, size, fill);
    }

    static void Circle(uint16_t x, uint16_t y, uint16_t radius, bool fill = false) 
    {
      String command = "cir";

      if (fill)
      {
        command += "s ";
      }
      else
      {
        command += " ";
      }
      
      command += x;
      command += ",";
      command += y;
      command += ",";
      command += radius;
      command += ",";
      command += Color.ToNumber();

      NextionSerial.print(command);
      CommandEnd();
    }
};

SoftwareSerial Graphics::NextionSerial = SoftwareSerial(NEXTION_TX, NEXTION_RX);
Color565 Graphics::Color;

#endif
