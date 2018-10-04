//Serial Ports
#define UserSerial Serial
#define AXSerial Serial2
#define USBSerial Serial


//Libraries
#include<ax12Serial.h>   //KurtE's bioloid library https://github.com/KurtE/BioloidSerial
#include<BioloidSerial.h> //KurtE's bioloid library https://github.com/KurtE/BioloidSerial
#include<Commander.h>  //TrossenRobotics Commander Lib
#include <i2c_t3.h> //Teensy3.x I2C library to use WIRE1

#define ServoI2C Wire1


#define MOVE_MODE_WALK 0
#define MOVE_MODE_SWERVE 1
#define MOVE_MODE_OTHER 2
uint8_t MoveMode = MOVE_MODE_WALK;

//GaitGenControlVars
int GaitPeriod = 5000; //walk period
int GaitMoveX = 0;
int GaitMoveY = 0;
int GaitStepHeight = 0;
float GaitMoveZrot = 0;
int GaitBodyX = 0;
int GaitBodyY = 0;
int GaitBodyZ = 0;
float GaitBodyPitch = 0;
float GaitBodyRoll = 0;
float GaitBodyYaw = 0;



int pan;
int tilt;

int CamPan = 0;//Unused by GG
int CamTilt = 0;//Unused by GG




//Defines for BioloidSerial
#define NumServos 16
BioloidControllerEx bioloid = BioloidControllerEx();

//Limits and id for each motor in the design in order  min, max, ID
//ServoLimits
const int DXLServoLimits[6][3][3] = {
  {{600,2400,0},{600,2400,1},{600,2400,2}},
  {{600,2400,3},{600,2400,4},{600,2400,5}},
  {{600,2400,6},{600,2400,7},{600,2400,8}},
  {{600,2400,9},{600,2400,10},{600,2400,11}},
  {{600,2400,12},{600,2400,13},{600,2400,14}},
  {{600,2400,15},{600,2400,16},{600,2400,17}}

};
  
float LegDynamixels[6][3]{//holds servo position
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0}};
  

//Initial Positions of legs, used in GaitGen
//coordinates are mirrored relative to global ones, +x is right, +y is forward
//Leg 0 (front left)
#define Leg0InitX -120
#define Leg0InitY 120
#define Leg0InitZ -100
//Leg1 (front right)
#define Leg1InitX 120
#define Leg1InitY 120
#define Leg1InitZ -100
//Leg2 (back right)
#define Leg2InitX 120
#define Leg2InitY -120
#define Leg2InitZ -100
//Leg3 (back left)
#define Leg3InitX -120
#define Leg3InitY -120
#define Leg3InitZ -100
//Leg4 (mid Left)
#define Leg4InitX -120
#define Leg4InitY 0
#define Leg4InitZ -100
//Leg5 (mid Right)
#define Leg5InitX -120
#define Leg5InitY 0
#define Leg5InitZ -100

//Dimensions used in leg calculations
#define CoxaLength 50
#define FemurLength 93
#define TibiaLength 97

//Dimensions used to convert to local leg coords
#define CogX 52 // distance that the legs are in left and right of the COG
#define CogY 65 // distance that the legs are in front and behind the COG
#define CogW 70 // distance that the side legs are from the COG

//Variable used to output from functions
unsigned long Tim1;
int GaitGenOut[6][3]; // For GaitGen
int BodyModOut[6][3]; // for BodyMod
int LegCoordsOut[6][3];// For LegCoordsOut
float LegCalculateOut[6][4];// For LegCalculateOut
