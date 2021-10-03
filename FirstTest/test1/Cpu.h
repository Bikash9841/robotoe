
#include "Player.h"
#include "time.h"


LinkList<int> cpuInputValue;

class Cpu : public Player
{
  public:

    void takeInputAndAddToList()
    {
      /*random no. generation for cpu*/
      srand(time(0));
      inputPlace = (rand() % 9) + 1;

      while (cpuInputValue.contains(inputPlace) || playerInputValue.contains(inputPlace) || inputPlace > 9)
      {
        inputPlace = (rand() % 9) + 1;
      }
      cpuInputValue.insert(inputPlace);
    }
};
