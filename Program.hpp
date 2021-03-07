#ifndef PROGRAM
#define PROGRAM

#include "GraphicsNextion.hpp"

#include "Buttons.hpp"

class Program
{
  private:
    String Name;
  
  public:
    Program(String name) : Name(name) { };

    virtual void Begin() = 0; //-----------------//Начало работы программы (необходимо для эффективного использования памяти)
    virtual void End()   = 0; //-----------------//Конец работы программы
  
    virtual void Process(Buttons * buttons) = 0; //Обработка кнопок программой
    virtual void Draw() = 0; //------------------//Отрисовка окна программы

    String GetName() const
    {
      return Name;
    }
};

#endif
