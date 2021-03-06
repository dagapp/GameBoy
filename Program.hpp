#ifndef PROGRAM
#define PROGRAM

#include "GraphicsNextion.hpp"

#include "Buttons.hpp"

class Program
{
  private:
    String Name;
  
  public:
    virtual Program(String name) : Name(name) { };
  
    virtual void Process(Buttons * buttons) = 0; //Обработка кнопок программой
    virtual void Draw() = 0; //Отрисовка окна программы

    String GetName() const
    {
      return Name;
    }
};

#endif
