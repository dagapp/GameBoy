#ifndef BUTTONS
#define BUTTONS

struct Buttons
{
  bool Left  : 1;
  bool Up    : 1;
  bool Right : 1;
  bool Down  : 1;
  bool Pick  : 1;
  bool Exit  : 1;

  void Print()
  {
    Serial.print("Left: ");
    Serial.print(Left);
    
    Serial.print("; Up: ");
    Serial.print(Up);
    
    Serial.print("; Right: ");
    Serial.print(Right);
    
    Serial.print("; Down: ");
    Serial.print(Down);
    
    Serial.print("; Pick: ");
    Serial.print(Pick);
    
    Serial.print("; Exit: ");
    Serial.println(Exit);
  }
};

#endif
