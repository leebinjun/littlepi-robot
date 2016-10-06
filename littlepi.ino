#include <Servo.h>
//#include "act.h"

Servo leftServoLeg;
Servo leftServoFoot;
Servo rightServoLeg;
Servo rightServoFoot;
/*Class four Servos*/

const int walkFw[] = {
8,0,0,0,0,
300,1500,1450,1500,1150,
300,1650,1450,1650,1150,
300,1650,1600,1650,1300,
300,1650,1750,1650,1450,
300,1500,1750,1500,1450,
300,1350,1750,1350,1450,
300,1350,1600,1350,1300,
300,1350,1450,1350,1150};
const int walkEnd[] = {
2,0,0,0,0,
300,1500,1450,1500,1150,
300,1500,1600,1500,1300};
const int standSt[] = {
1,0,0,0,0,
300,1500,1600,1500,1300};

int act_array[100];

int LeftLeg = 6;
int LeftFoot = 7;
int RightLeg = 8;
int RightFoot = 9;
/*define the pins*/

int currentLeftLeg, currentLeftFoot, currentRightLeg, currentRightFoot;
int startLeftLeg, startLeftFoot, startRightLeg, startRightFoot;
/*updata the state of the servos*/

int actDo[5];
long timeAtlastAct;

const int leftLegCenter = 1500;
const int leftFootCenter = 1500;
const int rightLegCenter = 1500;
const int rightFootCenter = 1500;
/* store each action and the time*/

int defaultArr[5] = {100, leftLegCenter, leftFootCenter, rightLegCenter, rightFootCenter};

char k;
String com="";
int v=0, loopvalue;

void readSerial()
{
    if(Serial.available())
    {
        k = Serial.read();
        Serial.println(k);
        if (k >= 'A' && k <= 'Z')
        {
            com += k;
        }
        else if (k>='0' && k<='9')
        {
            v = v*10+k-'0';
        }
        else if (k == '>')
        {
            if (v == 0)
            {
                loopvalue = 1;
            }
            else
            {
                loopvalue = v;
            }
            v = 0;
         }
    }
}

//switch-case
void loopAct()
{
    if (com == "FW")
    {
        do{
            toArrAct(walkFw);
        }while(--loopvalue);
        toArrAct(walkEnd);
        //Serial.println("y");
    }
    com = "";
}

void defaultAct()
{
    currentLeftLeg = leftLegCenter;
    currentLeftFoot = leftFootCenter;
    currentRightLeg = rightLegCenter;
    currentRightFoot = rightFootCenter;
    updateAct();
    startLeftLeg = leftLegCenter;
    startLeftFoot = leftFootCenter;
    startRightLeg = rightLegCenter;
    startRightFoot = rightFootCenter;
}

void attachMyServo()
{
    leftServoLeg.attach(LeftLeg, leftLegCenter-500, leftLegCenter+500);
    leftServoFoot.attach(LeftFoot, leftFootCenter-500, leftFootCenter+500);
    rightServoLeg.attach(RightLeg, rightLegCenter-500, rightLegCenter+500);
    rightServoFoot.attach(RightFoot, rightFootCenter-500, rightFootCenter+500);
}
/*function of attach four Servos*/

void toArrAct(const int *currAnim)
{
    int stepAnim=*currAnim;
    char flag_fram;
    /*
    Serial.print("stepAnim:");
    Serial.println(stepAnim);
    */
    //while(1);
    currAnim +=5;
    Serial.print("currAnim:");
    Serial.println(*currAnim);
  
    timeAtlastAct=millis();
    /*
    currentLeftLeg=startLeftLeg;
    currentLeftFoot=startLeftFoot;
    currentRightLeg=startRightLeg;
    currentRightFoot=startRightFoot;
    updateAct();*/

    while(stepAnim)
    {
        //Serial.println("helllllllll!");
        for (int i = 0; i < 5; i++)
        {
            actDo[i] = *(currAnim++);
            //Serial.println(actDo[i]);
        }
        currentLeftLeg = actDo[1];
        //Serial.println(currentLeftLeg);
        currentLeftFoot = actDo[2];
        currentRightLeg = actDo[3];
        currentRightFoot = actDo[4];
        flag_fram = 1;

        while (flag_fram)
        {
            long currTime = millis();
            int timeBetweenF = currTime - timeAtlastAct;
            /*
            Serial.print("timeBetweenF:");
            Serial.println(timeBetweenF);
            Serial.print("actDo[0]:");
            Serial.println(actDo[0]);
            */
            //while (1);
        
            if (timeBetweenF >= actDo[0])
            {
                currentLeftLeg = actDo[1];
                currentLeftFoot = actDo[2];
                currentRightLeg = actDo[3];
                currentRightFoot = actDo[4];
                updateAct();
                startLeftLeg = currentLeftLeg;
                startLeftFoot = currentLeftFoot;
                startRightLeg = currentRightLeg;
                startRightFoot = currentRightFoot;
  
                timeAtlastAct = currTime;
                flag_fram = 0;
            }
            float time_f = (currTime - timeAtlastAct)/(float)actDo[0];
            //Serial.println(time_f);
            currentLeftLeg = startLeftLeg+(actDo[1]-startLeftLeg)*time_f;
            currentLeftFoot = startLeftFoot+(actDo[2]-startLeftFoot)*time_f;
            currentRightLeg = startRightLeg+(actDo[3]-startRightLeg)*time_f;
            currentRightFoot = startRightFoot+(actDo[4]-startRightFoot)*time_f;
            updateAct();
        }
        stepAnim--;
    }
}
/*function of analysis each action*/

void updateAct()
{
    leftServoLeg.writeMicroseconds(currentLeftLeg);
    leftServoFoot.writeMicroseconds(currentLeftFoot);
    rightServoLeg.writeMicroseconds(currentRightLeg);
    rightServoFoot.writeMicroseconds(currentRightFoot);
}
/*function of updata the act */

void setup()
{
    Serial.begin(9600);
    attachMyServo();
    defaultAct();
    toArrAct(standSt);
    //Serial.println("ok!");
}

void loop()
{ 
    readSerial();
    loopAct(); 
    //while(1); 
}


