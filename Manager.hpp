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
    Manager(Program ** programs, int count) : Program("Меню"), Programs(programs), Count(count), Active(this), ChooseNumber(0) { }

    virtual void Begin() override
    {
      Graphics::Begin();
    }

    virtual void End() override { }

    virtual void Process(Buttons * buttons) override
    {
      if (Active == this)
      {
        //Cдвиг окна выбора программы
        if      (buttons->Up)   ChooseNumber -= (ChooseNumber > 0)         ? 1 : 0;
        else if (buttons->Down) ChooseNumber += (ChooseNumber < Count - 1) ? 1 : 0;
        else if (buttons->Pick)
        {
          Active = Programs[ChooseNumber];
          Active->Begin();
          
          ChooseNumber = 0;
        }

        Draw(); //Отрисовка менеджера программ
      }
      else
      {
        if (buttons->Exit)
        {
          Active->End();
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
      Graphics::Clear();

      Graphics::ChangeColor(Color565::Orange);
      Graphics::Rect(0, 0, WINDOW_WIDTH, 50, true);

      //Graphics::Stroke(0, 0, 0);
      //Graphics::SetTextSize(2);
      Graphics::Text("Выберите игру", 0, 0, WINDOW_WIDTH, 50);

      uint8_t y = 50;
      for (uint8_t i = 0; i < Count; i++)
      {
        y += 10;
        
        Graphics::ChangeColor(0, 0, 0);
        Graphics::Rect(10, y, WINDOW_WIDTH - 20, 50);  

        if (i == ChooseNumber)
        {
          Graphics::ChangeColor(Color565::Gray);
          Graphics::Rect(12, y + 2, WINDOW_WIDTH - 24, 46, true);
          Graphics::ChangeColor(Color565::Black);
          Graphics::Rect(12, y + 2, WINDOW_WIDTH - 24, 46);
        }
        
        y += 50;
      }
    }
};

#endif
