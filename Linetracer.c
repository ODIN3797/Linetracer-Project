#include "Arduino.h"

#include <EV3UARTSensorMega.h>
#include <func.h>
#include <BricktronicsMegashield.h>
#include <BricktronicsMotor.h>
#include <BricktronicsUltrasonic.h>
#include <BricktronicsLight.h>
#define CW 1
#define CCW 2
int MARK_LEFT = 0;
int MARK_RIGHT = 0;

BricktronicsUltrasonic u(BricktronicsMegashield::SENSOR_3);
BricktronicsLight ls_right(BricktronicsMegashield::SENSOR_2);
BricktronicsLight ls_left(BricktronicsMegashield::SENSOR_1);
BricktronicsMotor m1(BricktronicsMegashield::MOTOR_1);
BricktronicsMotor m2(BricktronicsMegashield::MOTOR_2);
BricktronicsMotor m5(BricktronicsMegashield::MOTOR_5);
EV3UARTSensor sensor(&Serial1);

int color = 0;
unsigned long lastMessage = 0;

int stndard_left = 0;
int stndard_right = 0;
int e = 0;
int f = 0;
int b = 0;
int distance = 0;
int p = 0;
int num1 = 0;
int num2 = 0;
int result = 0;
int result1 = 0;
int result2 = 0;
int result3 = 0;
int result4 = 0;
int look_at = 0;


void initialize()
{
   sensor.begin();
   ls_left.begin();
   ls_right.begin();
   m1.begin();
   m2.begin();
   m5.begin();
   u.begin();



}
void standard(int g, int h)
{
   e = g;
   f = h;
}

void start(void)
{
   move_up_count(1, 1);
}

int get_distance(void)
{
   int g = 0;

   distance = u.getDistance();
   Serial.println(u.getDistance());
   return distance;

}
// black is 0, white is 1
void move_up_count(int pow, int count)
{

   int result = 1;
   int pow_left = -pow;
   int pow_right = -pow+0.5;

   while (result < count + 1)
   {


      if (pow_left>255)
         pow_left = 255;
      if (pow_right>255)
         pow_right = 255;
      if (pow_left<-255)
         pow_left = -255;
      if (pow_right<-255)
         pow_right = -255;
      v_left(e);
      v_right(f);
      grasp(p,1);
      if (MARK_LEFT == 0 && MARK_RIGHT == 1)//need trun left
      {         
         pow_left--;
         pow_left--;
         pow_left--;
         


         m1.setFixedDrive(pow_left);
         m2.setFixedDrive(pow_right);
      }

      else if (MARK_LEFT == 1 && MARK_RIGHT == 0)//need turn right
      {
         pow_right--;
         pow_right--;
         pow_right--;


         m1.setFixedDrive(pow_left);
         m2.setFixedDrive(pow_right);
      }

      else if (MARK_LEFT == 1 && MARK_RIGHT == 1)
      {
         m1.setFixedDrive(-pow);
         m2.setFixedDrive(-pow+0.5);

      }
      else if (MARK_LEFT == 0 && MARK_RIGHT == 0)
      {

         int a = 0;
         while (a<1)
         {
            v_left(e);
            v_right(f);
            if (MARK_LEFT == 0 && MARK_RIGHT == 0)
            {
               m1.setFixedDrive(-pow);
               m2.setFixedDrive(-pow+0.5);

            }
            else if (MARK_LEFT == 1 && MARK_RIGHT == 1)
            {
               a = 2;
               result++;

            }
            else
            {

            }

         }


      }


      else
      {
      }

   }


   m1.setFixedDrive(0);
   m2.setFixedDrive(0);

}


void move_down_count(int pow, int count)
{

   int result = 1;
   int pow_left = 0;

   int pow_right = 0;

   pow_left = pow;
   pow_right = pow-0.5;
   while (result < count + 1)
   {



      if (pow_left>255)
         pow_left = 255;
      if (pow_right>255)
         pow_right = 255;
      if (pow_left<-255)
         pow_left = -255;
      if (pow_right<-255)
         pow_right = -255;
      v_left(e);
      v_right(f);
      grasp(p,1);
      if (MARK_LEFT == 0 && MARK_RIGHT == 1)//need trun left
      {
         pow_right++;
         pow_right++;
         pow_right++;


         m1.setFixedDrive(pow_left);
         m2.setFixedDrive(pow_right);
      }

      else if (MARK_LEFT == 1 && MARK_RIGHT == 0)//need turn right
      {
         pow_left++;
         pow_left++;
         pow_left++;


         m1.setFixedDrive(pow_left);
         m2.setFixedDrive(pow_right);
      }

      else if (MARK_LEFT == 1 && MARK_RIGHT == 1)
      {
         m1.setFixedDrive(pow);
         m2.setFixedDrive(pow-0.5);

      }
      else if (MARK_LEFT == 0 && MARK_RIGHT == 0)
      {

         int a = 0;
         while (a<1)
         {
            v_left(e);
            v_right(f);
            if (MARK_LEFT == 0 && MARK_RIGHT == 0)
            {
               m1.setFixedDrive(pow);
               m2.setFixedDrive(pow-0.5);

            }
            else if (MARK_LEFT == 1 && MARK_RIGHT == 1)
            {
               a = 2;
               result++;

            }
            else
            {
            }

         }


      }


      else
      {
      }

   }


   m1.setFixedDrive(0);
   m2.setFixedDrive(0);

}

void turn_robot(int spin, int sec)
{
   int g = 0;



   while (sec > g)
   {
      grasp(p,1);
      check_value_right();
      m1.setFixedDrive(spin);
      m2.setFixedDrive(-spin);

      delay(1);
      g++;
   }
   m1.brake();
   m2.brake();

}

void move_up_msec(int pow, int sec)
{
   int g = 0;


   while (sec > g)
   {
      grasp(p,1);
      check_value_right();

      m1.setFixedDrive(-pow);
      m2.setFixedDrive(-pow+0.3);

      delay(1);
      g++;
   }
   m1.brake();
   m2.brake();

}

void move_down_msec(int pow, int sec)
{
   int g = 0;


   while (sec > g)
   {
      m5.setFixedDrive(p);
      check_value_right();


      m1.setFixedDrive(pow);
      m2.setFixedDrive(pow);

      delay(1);
      g++;
   }
   m1.brake();
   m2.brake();

}

void grasp(int c, int sec)
{
   int g = 0;
   while(sec>g)
   {
      check_value_right();
      m5.setFixedDrive(c);

      delay(1);
      g++;

   }
   p = c;
}

int check_value_left(void)
{
   Serial.print(" - left value: ");
   Serial.println(ls_left.scaledValue());
   return ls_left.scaledValue();


}
int check_value_right(void)
{

   Serial.print(" - right value: ");
   Serial.println(get_value());
   return get_value();
}

int v_left(int standard_left)
{
   int value = 0;
   value = check_value_left();
   if (value< standard_left)
   {
      MARK_LEFT = 0;
   }

   if (value> standard_left)
   {
      MARK_LEFT = 1;
   }

   return  MARK_LEFT;

}


int v_right(int standard_right)
{
   int value = 0;
   value = check_value_right();
   if (value<standard_right)
   {
      MARK_RIGHT = 0;
   }
   if (value>standard_right)
   {
      MARK_RIGHT = 1;
   }

   return  MARK_RIGHT;

}
/* color value
*  value 0 null
*       1 black
*       2 blue
*       3 green
*       4 yellow
*       5 red
*       6 white
*       7 brown
*/

int get_color()
{
   sensor.check_for_data();
   int a = 0;
   float sample[sensor.sample_size()];
   sensor.fetch_sample(sample, 0);
   Serial.print("color is ");
   for (int i = 0; i<sensor.sample_size(); i++) {
      //Serial.print(sample[i]);
      //Serial.print(" ");

   }
   a = sample[0];
   return a;
   lastMessage = millis();

}

int get_value()
{
   sensor.check_for_data();
   int a = 0;

   float sample[sensor.sample_size()];
   sensor.fetch_sample(sample, 0);
   //Serial.print("value is ");
   for (int i = 0; i<sensor.sample_size(); i++) {
      //Serial.print(sample[i]);
      //   Serial.print(" ");      
   }
   a = sample[0];
   return a;
   lastMessage = millis();
}

void move_up_love(int pow)
{
   int result=0;
   while(result<1){
      if(get_distance()<20){
         turn_robot(130,600);
         move_up_count(pow,1);
         result++;
      }
      else{
         move_up_msec(pow,203);
      }
   }
}

void move_up_love1(int pow)
{
   int result=0;
   while(result<1){
      if(get_distance()<32){
         turn_robot(130,600);
         move_up_count(pow,1);
         result++;
      }
      else{
         move_up_count(pow,1);
      }
   }
}

void move_up_grasp(int pow)
{
   int result=0;
   while(result<1){
      if(get_distance()<32){
         move_up_count(pow,1);
         grasp(-130,2030);
         grasp(0,1);
         result++;
      }
      else{
         move_up_count(pow,1);
      }
   }
}

void move_up_grasp1(int pow)
{
   int result=0;
   while(result<1){
      if(get_distance()<32){
         move_up_count(pow,1);
         grasp(-130,2030);
         grasp(0,1);
         result++;
      }
      else{
         result++;
      }
   }
}

void move_up_love2(int pow)
{
   int result=0;
   while(result<1){
      if(get_distance()<20){
         result++;
      }
      else{
         move_up_msec(pow,203);
      }
   }
}

void move_up_love3(int pow)
{
   move_up_love2(pow);
   turn_robot(130,300);
   move_up_count(pow,1);
   turn_robot(-130,300);
}

void move_up_ziczic_right(int pow, int sec, int dis)
{
   int result=0;
   while(result<1){
      if(get_distance()<dis){
         turn_robot(-130,sec);
         result++;
      }
      else{
         move_up_msec(pow,203);
      }
   }
}

void move_up_ziczic_left(int pow, int sec, int dis)
{
   int result=0;
   while(result<1){
      if(get_distance()<dis){
         turn_robot(130,sec);
         result++;
         m1.setFixedDrive(0);
         m2.setFixedDrive(0);

      }
      else{
         move_up_msec(pow,203);
      }
   }
}

void move_up_stop(int pow, int sec, int dis)
{
   int c=0;
   if(get_distance() < 32)//B점에 전지판이 있을경우의 경로/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   {

      turn_robot(130, 350);//(너무 많이 돈다.)
      look_at++;
      while(result1 < 1)//찍찍라이트 시작/////////////////////////
      {

         if(get_distance() < 27)
         {
            turn_robot(-130,350);//(덜 돈다)
            result1 ++;
         }
         move_up_msec(100,100);
      }//찍찍 라이트 끝////////////////////////
      while(result2 < 3)//승환 함수 시작,와일 시작
      {
         move_up_msec(0,500);
         if(get_distance() < 27)
         {
            move_up_count(203,1);
            grasp(-130,130);
            grasp(0,1);
            turn_robot(-130,403);//반바퀴 회전
            move_up_count(203,result2 + 1);
            turn_robot(130,350);
            move_up_count(203,1);
            turn_robot(-130,350);//A지점 도착
            result2 = result2 + 3;
         }
         else
         {
            move_up_count(203,1);
            result2++;
         }
      }//와일 끝!!!!!!
      if(result2 == 3)
      {
         turn_robot(-130,403);//반바퀴 회전
         move_up_count(203,3);
         turn_robot(130,350);
         move_up_count(203,1);//A지점 도착
         while(result3 < 1)//찍찍레프트 시작/////////////////////////
         {
            if(get_distance() < 27)
            {
               turn_robot(130,350);//()
               result3 ++;
            }
            move_up_msec(100,100);
         }//찍찍 레프트 끝///////////////////////
         while(result4 < 3)//승환 함수 시작,와일 시작
         {
            move_up_msec(0,500);
            if(get_distance() < 32)
            {
               move_up_count(203,1);
               grasp(-130,130);
               grasp(0,1);
               turn_robot(130,403);//반바퀴 회전
               move_up_count(203,result4 + 1);
               turn_robot(-130,350);
               move_up_count(203,1);
               turn_robot(130,350);//A지점 도착
               result4 = result4 + 3;
            }
            else
            {
               move_up_count(203,1);
               result4++;
            }
         }//와일 끝!!!!!!
         if(result4 == 3)
         {
            turn_robot(130,403);//반바퀴 회전
            move_up_count(203,3);
            turn_robot(-130,350);
            move_up_count(203,1);//A지점 도착
            result1=0;
            while(result1 < 1)//찍찍라이트 시작/////////////////////////
            {
               if(get_distance() < 27)
               {
                  turn_robot(-130,350);
                  result1 ++;
               }
               move_up_msec(100,100);
            }//찍찍 라이트 끝////////////////////////
            move_up_count(203,2);
            turn_robot(-130,350);
            move_up_msec(0,500);
            if(get_distance() < 32)
            {
               move_up_count(203,1);
               grasp(-130,130);
               grasp(0,1);
               move_up_count(203,1);
               turn_robot(-130,350);
               move_up_count(203,2);
               turn_robot(-130,350);
               move_up_count(203,1);
               turn_robot(130,350);   
            }
            else 
            {
               move_up_count(203,1);
               turn_robot(-130,350);
               move_up_count(203,1);
               grasp(-130,130);
               grasp(0,1);
               move_up_count(203,1);
               turn_robot(-130,350);
               move_up_count(203,3);
               turn_robot(-130,350);
               move_up_count(203,1);
               turn_robot(130,350);            
            }
         }

      }



   }//B점에 전지판이 있을경우의 경로 끝!!!!!!!!!!!///////////////////////////////////////////
   else
   {
      move_up_count(203,1);
      move_up_msec(0,500);
      if(get_distance()<32)//C점에 있을때 한바퀴 돌아서 갖고 A점으로 오기
      {
         turn_robot(130,350);
         move_up_count(203,1);
         turn_robot(-130,350);
         move_up_count(203,1);
         move_up_count(203,1);
         turn_robot(-130,350);
         move_up_count(203,1);
         move_up_count(203,1);
         turn_robot(-130,350);
         move_up_count(203,1);
         move_up_count(203,1);
         turn_robot(-130,350);
         move_up_count(203,1);
         grasp(-130,130);
         grasp(0,1);
         turn_robot(130,350);
         move_up_count(203,1);
         c++;
      }
      else
      {
         turn_robot(130,350);
         move_up_msec(0,500);
         if(get_distance()<32)
         {
            turn_robot(-130,403);
            move_up_count(203,1);
            turn_robot(130,350);
            move_up_count(203,1);
            move_up_count(203,1);
            turn_robot(130,350);
            move_up_count(203,1);
            move_up_count(203,1);
            turn_robot(130,350);
            move_up_count(203,1);
            grasp(-130,130);
            grasp(0,1);
            turn_robot(130,350);
            move_up_count(203,1);
            turn_robot(-130,350);
            move_up_count(203,1);
            move_up_count(203,1);
            c++;
         }
         else
         {
            move_up_count(203,1);
            turn_robot(-130,350);
            move_up_msec(0,500);
            if(get_distance()<32)
            {
               turn_robot(-130,350);
               move_up_count(203,2);
               turn_robot(130,350);
               move_up_count(203,2);
               turn_robot(130,350);
               move_up_count(203,2);
               grasp(-130,130);
               turn_robot(-130,403);
               move_up_count(203,1);
               turn_robot(-130,350);
               move_up_count(203,3);
               c++;
            }
            else
            {  
               move_up_count(203,1);
               move_up_msec(0,500);
               if(get_distance()<32)
               {
                  turn_robot(-130,403);
                  move_up_count(203,1);
                  turn_robot(130,350);
                  move_up_count(203,2);
                  turn_robot(130,350);
                  move_up_count(203,2);
                  turn_robot(130,350);
                  move_up_count(203,1);
                  grasp(-130,130);
                  grasp(0,1);
                  turn_robot(130,350);
                  move_up_count(203,3);
                  c++;
               }
               else
               {
                  move_up_count(203,1);
                  turn_robot(-130,350);
                  move_up_msec(0,500);
                  if(get_distance()<32)
                  {
                     turn_robot(-130,350);
                     move_up_count(203,2);
                     turn_robot(130,350);
                     move_up_count(203,2);
                     turn_robot(130,350);
                     move_up_count(203,2);
                     grasp(-130,130);
                     grasp(0,1);
                     turn_robot(-130,403);
                     move_up_count(203,2);
                     turn_robot(-130,350);
                     move_up_count(203,1);
                     turn_robot(130,350);
                     move_up_count(203,1);
                     c++;
                  }
                  else
                  {
                     move_up_count(203,1);
                     move_up_msec(0,500); 
                     if(get_distance()<32)
                     {
                        turn_robot(130,403);
                        move_up_count(203,1);
                        turn_robot(130,350);
                        move_up_count(203,2);
                        turn_robot(130,350);
                        move_up_count(203,2);
                        turn_robot(130,350);
                        move_up_count(203,1);
                        grasp(-130,130);
                        grasp(0,1);
                        turn_robot(130,350);
                        move_up_count(203,1);
                        turn_robot(130,350);
                        move_up_count(203,2);
                        c++;
                     }
                     else
                     {
                        move_up_count(203,1);
                        turn_robot(-130,350);
                        move_up_msec(0,500);
                        if(get_distance()<32)
                        {
                           turn_robot(-130,350);
                           move_up_count(203,2);
                           turn_robot(130,350);
                           move_up_count(203,2);
                           turn_robot(130,350);
                           move_up_count(203,2);
                           grasp(-130,130);
                           grasp(0,1);
                           turn_robot(-130,403);
                           move_up_count(203,1);
                           turn_robot(130,350);
                           move_up_count(203,1);
                           c++;
                        }
                        else
                        {
                           move_up_count(203,1);
                           if(get_distance()<32)
                           {
                              turn_robot(130,456);
                              move_up_count(203,1);
                              turn_robot(130,350);
                              move_up_count(203,2);
                              turn_robot(130,350);
                              move_up_count(203,2);
                              turn_robot(130,350);
                              move_up_count(203,1);
                              grasp(-130,130);
                              grasp(0,1);
                              turn_robot(-130,350);
                              move_up_count(203,1);
                              c++;
                           }
                           else
                           {
                              c++;
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
}



void enter_back(int back)
{
   num2 = back;
}

void move_up_pjs(int pow)
{
   int result=0;
   int back=0;
   int line=0;
   while(result<1){
      if(get_distance()<32)
      {
         move_up_grasp1(pow);
         turn_robot(-130,403);
         move_up_count(pow,1);
         back++;
         enter_back(back);
         line=-1;
         enter_line(line);
         result++;
      }
      else{
         move_up_count(pow,1);
         if(get_distance()<32){
            move_up_grasp1(pow);
            turn_robot(-130,403);
            move_up_count(pow,2);
            back+=2;
            enter_back(back);
            line=-1;
            enter_line(line);
            result++;
         }
         else
         {
            move_up_count(pow,1);
            if(get_distance()<40){
               move_up_grasp1(pow);
               turn_robot(-130,403);
               move_up_count(pow,3);
               back+=3;
               enter_back(back);
               line=-1;
               enter_line(line);
               result++;
            }
            else{
               turn_robot(-130,403);
               move_up_count(pow,2);
               result++;
            }
         }
      }
   }
}

void enter_line(int line)
{
   num1 = line;
}

void move_up_pjs1(int pow)
{
   int result=0;
   int back=0;
   int line = 0;
   while(result<1){
      if(get_distance()<32)
      {
         move_up_grasp1(pow);
         turn_robot(-130,403);
         move_up_count(pow,1);
         back++;
         enter_back(back);
         line=1;
         enter_line(line);
         result++;
      }
      else{
         move_up_count(pow,1);
         if(get_distance()<32){
            move_up_grasp1(pow);
            turn_robot(-130,403);
            move_up_count(pow,2);
            back+=2;
            enter_back(back);
            line=1;
            enter_line(line);
            result++;
         }
         else
         {
            move_up_count(pow,1);
            if(get_distance()<40){
               move_up_grasp1(pow);
               turn_robot(-130,403);
               move_up_count(pow,3);
               back+=3;
               enter_back(back);
               line=1;
               enter_line(line);
               result++;
            }
            else{
               turn_robot(-130,403);
               move_up_count(pow,2);
               result++;
            }
         }
      }
   }
}

void move_up_pjs2(int pow)
{
   int result=0;
   int back=0;
   int line=0;
   while(result<1){
      if(get_distance()<32)
      {
         move_up_grasp1(pow);
         turn_robot(-130,403);
         move_up_count(pow,1);
         back+=2;
         enter_back(back);
         line=-1;
         enter_line(line);
         result++;
      }
      else{
         move_up_count(pow,1);
         if(get_distance()<32){
            move_up_grasp1(pow);
            turn_robot(-130,403);
            move_up_count(pow,2);
            back+=3;
            enter_back(back);
            line=-1;
            enter_line(line);
            result++;
         }
         else{
            turn_robot(-130,403);
            move_up_count(pow,2);
            result++;
         }
      }
   }
}


