
#include "winpoll.h"

#include "kinematics.h"
#include "scServo.h"

#define HUM_ID 1
#define RAD_ID 2
int velocity = 1000;
SCServo hum, rad;
float p1_x = 0, p1_y = 0, n1_x = 0, n1_y = 0;
float len_hum = 7.15;
float len_rad = 8.9;
Kinematics chess;

bool command_flag = true;

void mapping()
{
  chess.q1 = map(chess.q1, 255, -69, 0, 1023);
  chess.q2 = map(chess.q2, 135, -141, 0, 1023);
}


void arm_run()
{
  delay(500);
  hum.WritePos(HUM_ID, chess.q1, velocity);
  delay(500);
  rad.WritePos(RAD_ID, chess.q2, velocity);
}


void initial()
{
  float q_1 = 0;
  float q_2 = 90;


  q_1 = map(q_1, 255, -69, 0, 1023);
  q_2 = map(q_2, 135, -141, 0, 1023);

  delay(500);

  hum.WritePos(HUM_ID, q_1, velocity);

  delay(500);

  rad.WritePos(RAD_ID, q_2, velocity);

}
void initial1()
{
  float q_1 = 0;
  float q_2 = 0;

  q_1 = map(q_1, 255, -69, 0, 1023);
  q_2 = map(q_2, 135, -141, 0, 1023);

  delay(500);

  hum.WritePos(HUM_ID, q_1, velocity);

  delay(500);

  rad.WritePos(RAD_ID, q_2, velocity);

}

void chess_command(int x)
{

  float p_x, p_y;

  if (x == 0) {

    initial();
  }
  else if (x == 1) {
       p_x = -2.13;
       p_y = 10.8;
   

  }
  else if (x == 2) {
      p_x = 0;
        p_y = 10.8;
     
  }
  else if (x == 3) {
       p_x = 2.13;
       p_y = 10.8;
     
  }  else if (x == 4) {
        p_x = -2.13;
        p_y = 7.13;
    
  }
  else if (x == 5) {
        p_x = 0;
        p_y = 7.13;
     
  }
  else if (x == 6) {
       p_x = 2.13;
        p_y = 7.13;
    
  }
  else if (x == 7) {
        p_x = -2.13;
        p_y = 5;
   
  }
  else if (x == 8) {
       p_x = 0;
       p_y = 5;
     
  }
  else if (x == 9) {
        p_x = 2.13;
        p_y = 5;
     
  }
  else {
    delay(1);
  }

   chess.update(p_x, p_y);

    mapping();
    arm_run();
  delay(5000);

  //  initial();

}

void setup()
{
  hum.init(57600);
  rad.init(57600);
  chess.init(len_hum, len_rad);
  //  initial();

  Serial.begin(57600);
  pinMode(LED_BUILTIN,OUTPUT);
  w.processSet(); //it process and store the winning set of values fot tic tac toe

}

Player p;
Cpu c;

void loop()
{

  while (!isGameOver)
  {
   delay(2000);
    Serial.println("nextdata");
//    digitalWrite(LED_BUILTIN,LOW);
    p.takeInputAndAddToList();

    checkWhoWins();
    if (isGameOver)
    {
      break;
    }
    c.takeInputAndAddToList();

    chess_command(c.inputPlace);
    Serial.println(c.inputPlace);

    //check if anyone wins
    checkWhoWins();
  }
}
