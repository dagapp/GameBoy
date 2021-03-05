#ifndef MANAGER
#define MANAGER

#include "Program.hpp"

class Manager : public Program
{
  private:
    Program ** Programs;
    uint8_t Count;

    Program * Active;

    uint8_t ChooseNumber;

  public:
    Manager(Program ** programs, int count) : Programs(programs), Count(count), Active(this), ChooseNumber(0)
    {
      Graphics::Begin();  
    }

    /*void Begin(Program ** programs, int count)
    {
      Programs = programs;
      Count = count;
      Active = this;
      ChooseNumber = 0;

      Graphics::Begin();
    }*/

    virtual void Process(Buttons * buttons) override
    {
      if (Active == this)
      {
        //Cдвиг окна выбора программы
        if (buttons->Up)   ChooseNumber -= (ChooseNumber > 0)         ? 1 : 0;
        if (buttons->Down) ChooseNumber += (ChooseNumber < Count - 1) ? 1 : 0;

        Draw(); //Отрисовка менеджера программ
      }
      else
      {
        if (buttons->Exit)
        {
          Active = this;
        }
        else
        {
          Active->Process(buttons);
        }
      }
    }

    virtual void Draw() override
    {
      //Отрисовка менеджера программ

      Graphics::Stroke(255, 255, 255);
      Graphics::Rect(0, 0, WINDOW_WIDTH, 50, true);

      Graphics::Stroke(0, 0, 0);
      Graphics::SetTextSize(2);
      Graphics::Text("Выберите игру", 0, 0);

      int y = 50;
      for (int i = 0; i < Count; i++)
      {
        y += 5;

        if (i == ChooseNumber)
        {
          Graphics::Stroke(255, 255, 255);
          Graphics::Rect(10, y + 5, WINDOW_WIDTH - 20, 10);        

          Graphics::Stroke(0, 0, 0);
          //Graphics::Text(Programs[i]->GetName(), 10, y + 5);
        }
        else
        {
          Graphics::Stroke(255, 255, 255);
          Graphics::Rect(5, y, WINDOW_WIDTH - 5, 20);        

          Graphics::Stroke(0, 0, 0);
          //Graphics::Text(Programs[i]->GetName(), 5, y);
        }
        
        y += 20;
      }

      Graphics::Clear();
    }
};

#endif
