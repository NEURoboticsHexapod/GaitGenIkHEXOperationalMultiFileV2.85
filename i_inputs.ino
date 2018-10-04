
//Defines for Reading Commander
Commander command = Commander();
#define Right1   0
#define Right2   1
#define Right3   2
#define Left4    3
#define Left5    4
#define Left6    5
#define RightTop 6
#define LeftTop  7

//What input is which----------------------------------------
//Move Mode(for analog)---------------
#define MOVELR lookH
#define MOVEFB lookV
#define MOVEYAW walkH
#define MOVEUD walkV
//      CamPan  First half of EXT (in = 0) = 0 (in > 0) -= 8
//      CamTilt  Second half of EXT (in = 0) = 0 (in > 0) -= 8
//Body Mode(for analog)----------------
#define BODYLR lookH
#define BODYFB lookV 
#define BODYYAW walkH
#define BODYPITCH walkV
//      BODYHEIGHT first half of .ext (in = 0) = 0 (in > 0) = 8
//      BODYROLL  second half of .ext (in = 0) = 0 (in > 0) = 8
//Buttons(mode independant)
#define ANALOGMODEBIT RightTop
#define ANALOGHOLDBIT LeftTop
#define MOVEWALKBIT Right1
#define MOVESWERVEBIT Right2
#define MOVEOTHERBIT Right3


//reminder of variables for gait generation control
/*
  //All variables range from -127 to 127 under normal situations
  GaitPeriod       how long one cycle takes
  GaitMoveX        how far to step each cycle
  GaitMoveY        how far to step each cycle
  GaitStepHeight   how far to lift for each step
  GaitMoveZrot     how far to rotate each cycle
  GaitBodyX        how far the body should be translated relative to the legs/direction of travel
  GaitBodyY        how far the body should be translated relative to the legs/direction of travel
  GaitBodyZ        how far the body should be translated vertically from the default height
  GaitBodyPitch     how far the body should be rotated relative to the legs/direction of travel
  GaitBodyRoll     how far the body should be rotated relative to the legs/direction of travel
  GaitBodyYaw     how far the body should be rotated relative to the legs/direction of travel
*/

boolean AnalogInMode = 0;
boolean AnalogHold = 0;
boolean MoveWalk = 0;
boolean MoveSwerve = 0;
boolean MoveOther = 0;

//ReadCommanderData
void GetCommander(){
  //Read Buttons
  if(command.ReadMsgs() > 0){
    uint8_t Buttons = command.buttons;
    AnalogInMode = bitRead(Buttons, ANALOGMODEBIT);
    AnalogHold = bitRead(Buttons, ANALOGHOLDBIT);
    MoveWalk = bitRead(Buttons, MOVEWALKBIT);
    MoveSwerve = bitRead(Buttons, MOVESWERVEBIT);
    MoveOther = bitRead(Buttons, MOVEOTHERBIT);
    //insert other buttons here
    
    
    //Read Extended Byte
    uint8_t Extended = command.ext;
    uint8_t FirstHalfExtTemp = Extended;//will become x's (xxxx0000) of Extended
    FirstHalfExtTemp &= B11110000;//Clear lower nibble
    int8_t FirstHalfExt = FirstHalfExtTemp/16;//Shift upper nibble to lower nibble
    if (FirstHalfExt  != 0){
      FirstHalfExt -= 8;
    }  
    uint8_t SecondHalfExtTemp = Extended;//will become 0's (xxxx0000) of Extended
    SecondHalfExtTemp &= B00001111;//Clear upper nibble
    int8_t SecondHalfExt = SecondHalfExtTemp;
    if (SecondHalfExt != 0){
      SecondHalfExt -= 8;
    }
    
    //Set move mode
    if(MoveWalk == 1){
      MoveMode = MOVE_MODE_WALK;
    }
    else if(MoveSwerve == 1){
      MoveMode = MOVE_MODE_SWERVE;
    }
    else if(MoveOther == 1){
      MoveMode = MOVE_MODE_OTHER;
    }
    
    //apply holds
    if (AnalogHold == 0){
      GaitMoveY = 0;
      GaitMoveX = 0;
      GaitMoveZrot = 0;
      CamPan = 0;
      CamTilt = 0;
      GaitBodyY = 0;
      GaitBodyX = 0;
      GaitBodyYaw = 0;
      GaitBodyPitch = 0;
      GaitBodyRoll = 0;
      GaitBodyZ = 0;
    }
    //Check Mode (body or move)
    if (AnalogInMode == 0){//MoveMode
      GaitMoveY = command.MOVELR;
      GaitMoveX = command.MOVEFB;
      GaitMoveZrot = command.MOVEYAW;
      GaitStepHeight = command.MOVEUD;
      CamPan = map(FirstHalfExt,-7,7,-127,127);
      CamTilt = map(SecondHalfExt,-7,7,-127,127);
    }
    else if (AnalogInMode == 1){
      GaitBodyY = command.BODYLR;
      GaitBodyX = command.BODYFB;
      GaitBodyYaw = command.BODYYAW;
      GaitBodyPitch = command.BODYPITCH;
      GaitBodyZ = map(FirstHalfExt,-7,7,-127,127);
      GaitBodyRoll = map(SecondHalfExt,-7,7,-127,127);
    }
    
    
    //Scale the outputs --- now done in functuions
    
    
  }  
}

