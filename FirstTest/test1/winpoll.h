
#include "Cpu.h"

winSet w;

bool isGameOver = false;
void checkWhoWins()
{
  if (w.winSet1.containsAll(playerInputValue) ||
      w.winSet2.containsAll(playerInputValue) ||
      w.winSet3.containsAll(playerInputValue) ||
      w.winSet4.containsAll(playerInputValue) ||
      w.winSet5.containsAll(playerInputValue) ||
      w.winSet6.containsAll(playerInputValue) ||
      w.winSet7.containsAll(playerInputValue) ||
      w.winSet8.containsAll(playerInputValue))
  {
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println("player wins");
    isGameOver = true;
  }
  else if (w.winSet1.containsAll(cpuInputValue) ||
           w.winSet2.containsAll(cpuInputValue) ||
           w.winSet3.containsAll(cpuInputValue) ||
           w.winSet4.containsAll(cpuInputValue) ||
           w.winSet5.containsAll(cpuInputValue) ||
           w.winSet6.containsAll(cpuInputValue) ||
           w.winSet7.containsAll(cpuInputValue) ||
           w.winSet8.containsAll(cpuInputValue))
  {
    Serial.println("Cpu wins");
    isGameOver = true;
  }
  else if ((playerInputValue.length + cpuInputValue.length) >= 9)
  {
    //        cout << "\nGame Ties\n";/
    isGameOver = true;
  }
}
