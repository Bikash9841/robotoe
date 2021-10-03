
#include "linklist.h"

LinkList<int> playerInputValue;

class Player
{
  public:
    int boardLoc;               //board location from opencv through pyserial
    int inputPlace;               //place to put 'X' or '0'

    void extract_location() {
     
        while (Serial.available()) {
          boardLoc = Serial.parseInt();
          Serial.println("r");
          Serial.println(boardLoc);
        }
      inputPlace = boardLoc;
      playerInputValue.insert(inputPlace);
    }

    //take input and add every input to the list and display the board
    void takeInputAndAddToList()
    {
      extract_location();
    }
};

class winSet //class to store the winnning set of places in board
{

  public:
    LinkList<int> winSet2;
    LinkList<int> winSet3;
    LinkList<int> winSet1;
    LinkList<int> winSet4;
    LinkList<int> winSet5;
    LinkList<int> winSet6;
    LinkList<int> winSet7;
    LinkList<int> winSet8;

    //store set of winning place in winSet lists
    void processSet()
    {
      winSet1.insert(1);
      winSet1.insert(2);
      winSet1.insert(3);
      winSet2.insert(4);
      winSet2.insert(5);
      winSet2.insert(6);
      winSet3.insert(7);
      winSet3.insert(8);
      winSet3.insert(9);
      winSet4.insert(1);
      winSet4.insert(4);
      winSet4.insert(7);
      winSet5.insert(2);
      winSet5.insert(5);
      winSet5.insert(8);
      winSet6.insert(3);
      winSet6.insert(6);
      winSet6.insert(9);
      winSet7.insert(1);
      winSet7.insert(5);
      winSet7.insert(9);
      winSet8.insert(3);
      winSet8.insert(5);
      winSet8.insert(7);
    }
};
