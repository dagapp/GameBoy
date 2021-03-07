#include "Buttons.hpp"
#include "Manager.hpp"
#include "Snake.hpp"
#include "Tetris.hpp"

//Создание объектов программ
Snake  snake;
Tetris tetris;

#define COUNT 2 //-----------------------------------------------//Поменять в соответсвии с количеством программ !!!

Program ** programs = new Program * [COUNT] { &snake, &tetris }; //Массив программ - не забыть инициализировать !!
Manager manager(programs, COUNT) ; //----------------------------//Менеджер программ (сам является программой)

#define LEFT  2
#define UP    3
#define RIGHT 4
#define DOWN  5
#define PICK  6
#define EXIT  7

#include <SoftwareSerial.h>

void setup() 
{
  manager.Begin();

  //Назначение пинов для кнопок
  pinMode( LEFT, INPUT);
  pinMode(   UP, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode( DOWN, INPUT);
  pinMode( PICK, INPUT);
  pinMode( EXIT, INPUT);

  //Начало чтения COM-порта (виртуального)
  Serial.begin(115200);
}

void loop() 
{
  //Создание структуры хранящей состояние кнопок в данный момент
  static Buttons buttons;

  //Запись в структуру buttons
  buttons.Left  = digitalRead( LEFT);
  buttons.Up    = digitalRead(   UP);
  buttons.Right = digitalRead(RIGHT);
  buttons.Down  = digitalRead( DOWN);
  buttons.Pick  = digitalRead( PICK);
  buttons.Exit  = digitalRead( EXIT);

  //buttons.Print(); //--------//Вывод состояния кнопок (тяжёлый)

  manager.Process(&buttons); //Отправка состояния кнопок в программный менеджер
}
