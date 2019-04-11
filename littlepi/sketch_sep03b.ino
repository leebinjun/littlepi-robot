
#include <Servo.h>
#include "act.h"


Servo leftServoTap;
Servo leftServoFoot;
Servo rightServoTap;
Servo rightServoFoot;
/*Class four Servos*/

int act_array[100];

int LeftTap=6;
int LeftFoot=7;
int RightTap=8;
int RightFoot=9;
/*define the pins*/

int currentLeftTap,currentLeftFoot,currentRightTap,currentRightFoot;
int startLeftTap,startLeftFoot,startRightTap,startRightFoot;
/*updata the state of the servos*/

int actDo[5];
long timeAtlastAct;


const int leftTapCenter = 1500;
const int leftFootCenter = 1600;
const int rightTapCenter = 1500;
const int rightFootCenter = 1300;
/* store each action and the time*/


int defaultArr[5]={100,leftTapCenter,leftFootCenter,rightTapCenter,rightFootCenter};

 char k;
 String comD="";
 String comDo="";
 int v=0,loopvalue;
 
void setup()
{
 Serial.begin(9600);

  attachMyServo();
  defaultAct();
   toArrAct(standSt);
}

void loop()
{
  
  readSerial();


  loopAct(); 
  //while(1);
 }

 void readSerial()
 {
 	if(Serial.available())
  {
    k=Serial.read();
    if(k>='A'&&k<='Z')
        comD+=k;
    else if(k>='0' && k<='9')
       v=v*10+k-'0';
    else if(k=='>')
    {
      comDo=comD;
      if(v==0)
        loopvalue=1;
      else
        loopvalue=v;
      comD="";
      v=0;
    }
  }
 }
 void loopAct()
 {

  if(comDo=="FW")
  {
    do{
         toArrAct(walkFw);
  }while(--loopvalue);
      toArrAct(walkEnd);
    Serial.println("y");
  }
 else  if(comDo=="BW")
  {
    do{
          toArrAct(walkBw);
  }while(--loopvalue);

       toArrAct(walkEnd);
    Serial.println("y");
  }

  else if(comDo=="LT")
  {
    do{
        toArrAct(turnL);
    }while(--loopvalue);
    Serial.println("y");
  }
  else
  if(comDo=="RT")
  {
    do{
      toArrAct(turnR);
    }while(--loopvalue);
      Serial.println("y");
  }
 else
  if(comDo=="WX")
  {
    
    do{
      toArrAct(wobble);
    }while(--loopvalue);
  }
  else
  if(comDo=="WY")
  {
    do{
      toArrAct(wobbleL);
    }while(--loopvalue);
      Serial.println("y");
  }
  else
  if(comDo=="WZ")
  {
    
    do{
      toArrAct(wobbleR);
    }while(--loopvalue);
      Serial.println("y");
  }
  else
  if(comDo=="TX")
  {
    do{
      toArrAct(tapFeet);
    }while(--loopvalue);
      Serial.println("y");
  }
   else
  if(comDo=="TY")
  {
    do{
      toArrAct(tapLF);
    }while(--loopvalue);
      Serial.println("y");
  }
 else
  if(comDo=="TZ")
  {
    do{
      toArrAct(tapRF);
    }while(--loopvalue);
     Serial.println("y");
  }
  else
  if(comDo=="LX")
  {
    do{
      toArrAct(shakeL);
    }while(--loopvalue);
    Serial.println("y");
  }
  else
  if(comDo=="LY")
  {
    do{
      toArrAct(shakeLL);
    }while(--loopvalue);
     Serial.println("y");
  }
  else
  if(comDo=="LZ")
  {
    do{
      toArrAct(shakeRL);
    }while(--loopvalue);
     Serial.println("y");
  }
  else
  if(comDo=="SX")
  {
    do{
      toArrAct(shakeH);
    }while(--loopvalue);
    Serial.println("y");
  }
  else
  if(comDo=="ST")
  {

    do{
      toArrAct(standSt);
    }while(--loopvalue);
      Serial.println("y");
  }
 else
  if(comDo=="BX")
  {
    do{
      toArrAct(bounce);
    }while(--loopvalue);
    Serial.println("y");
  }
  else 
  if(comDo=="ZY")
  {
    do{
 
       toArrAct(bothBo);
    }while(--loopvalue);
    toArrAct(walkEnd); 
    Serial.println("y");
  }
  else 
  if(comDo=="TK")
  {
    do{
 
      toArrAct(taiSky);
    }while(--loopvalue);
    Serial.println("y");
  }
  else 
  if(comDo=="DZ")
  {
    do{
       toArrAct(onlyleg);
     }while(--loopvalue);
   Serial.println("y");
  }
  else if(comDo=="DE")
  {
    delay(1000);
  }
   else 
  if(comDo=="TB")
  {
    do{
 
       toArrAct(tapBw);
     }while(--loopvalue);
   Serial.println("y");
  }
    else 
  if(comDo=="US")
  {
    do{
   
       toArrAct(upSleg);
     }while(--loopvalue);
   Serial.println("y");
  }
  comDo="";
 }
  
 
 void defaultAct()
{
  currentLeftTap=leftTapCenter;
  currentLeftFoot=leftFootCenter;
  currentRightTap=rightTapCenter;
  currentRightFoot=rightFootCenter;
	updateAct();
  startLeftTap=leftTapCenter;
  startLeftFoot=leftFootCenter;
  startRightTap=rightTapCenter;
  startRightFoot=rightFootCenter;
}


 void attachMyServo()
{
  leftServoTap.attach(LeftTap,leftTapCenter-500,leftTapCenter+500);
  leftServoFoot.attach(LeftFoot,leftFootCenter-500,leftFootCenter+500);
  rightServoTap.attach(RightTap,rightTapCenter-500,rightTapCenter+500);
  rightServoFoot.attach(RightFoot,rightFootCenter-500,rightFootCenter+500);
}
/*function of attach four Servos*/


void toArrAct(const int *currAnim)
{

  int stepAnim=*currAnim;
  currAnim +=5;
  char flag_fram;
  timeAtlastAct=millis();
/*
  currentLeftTap=startLeftTap;
  currentLeftFoot=startLeftFoot;
  currentRightTap=startRightTap;
  currentRightFoot=startRightFoot;
  updateAct();*/

  while(stepAnim)
  {
   for(int i=0;i<5;i++)
     {
       actDo[i]=*(currAnim++);
     }
     currentLeftTap=actDo[1];
     currentLeftFoot=actDo[2];
     currentRightTap=actDo[3];
     currentRightFoot=actDo[4];
     flag_fram=1;

    while(flag_fram)
    {
     
      long currTime =millis();
  

      int timeBetweenF = currTime - timeAtlastAct;
       if(timeBetweenF >= actDo[0])
     {

      currentLeftTap=actDo[1];
      currentLeftFoot=actDo[2];
      currentRightTap=actDo[3];
      currentRightFoot=actDo[4];
      updateAct();
      startLeftTap=currentLeftTap;
      startLeftFoot=currentLeftFoot;
      startRightTap=currentRightTap;
      startRightFoot=currentRightFoot;

      timeAtlastAct=currTime;
      flag_fram=0;
     }
     float time_f = (currTime - timeAtlastAct)/(float)actDo[0];
     Serial.println(time_f);
     currentLeftTap=startLeftTap+(actDo[1]-startLeftTap)*time_f;
     currentLeftFoot=startLeftFoot+(actDo[2]-startLeftFoot)*time_f;
     currentRightTap=startRightTap+(actDo[3]-startRightTap)*time_f;
     currentRightFoot=startRightFoot+(actDo[4]-startRightFoot)*time_f;
     updateAct();
    }
    stepAnim--;
  }

}
/*function of analysis each action*/




void updateAct()
{
  leftServoTap.writeMicroseconds(currentLeftTap);
  leftServoFoot.writeMicroseconds(currentLeftFoot);
  rightServoTap.writeMicroseconds(currentRightTap);
  rightServoFoot.writeMicroseconds(currentRightFoot);

}
/*function of updata the act */


