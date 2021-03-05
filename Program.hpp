#ifndef PROGRAM
#define PROGRAM

#include "Graphics.hpp"

#include "Buttons.hpp"

class Program
{
  private:
    //char * Name;
  
  public:
    //virtual Program(char * name) : Name(name) { };
  
    virtual void Process(Buttons * buttons) = 0; //Обработка кнопок программой
    virtual void Draw() = 0; //Отрисовка окна программы

    /*char * GetName() const
    {
      return Name;
    }*/
};

#endif
