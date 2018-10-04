void loop() {
  Tim1 = millis();
  //Debug print Statements
  //UserSerial.print("Time =");
  //UserSerial.println(Tim1);
  //Actual Calculations
  GetCommander();
  
  if(MoveMode == MOVE_MODE_WALK){
    GaitGen(GaitPeriod,Tim1,GaitMoveX,GaitMoveY,10+GaitStepHeight,GaitMoveZrot);
  }
  else if(MoveMode == MOVE_MODE_SWERVE){//needs to be implemented
  //SwerveSteer(GaitMoveX,GaitMoveY,GaitMoveZrot);
  }
  else if(MoveMode == MOVE_MODE_OTHER){
  }
    
  BodyMod(GaitBodyX,GaitBodyY,GaitBodyZ,GaitBodyPitch,GaitBodyRoll,GaitBodyYaw);
  
  LegCoords();
  LegCalculate();
  
  for(int i = 0; i < 6; i++){//Update LegDynamixels
    for(int j = 0; j < 3; j++){
      LegDynamixels[i][j] = LegCalculateOut[i][j];
    }
  }
  
  //sphericalCoords goes here
  
  DXLServoMap();
  //PWMServoMap();
  
  //Debug Print Statements
  Serial.print(Tim1);
  for (int i = 0; i < 4; i++){
    UserSerial.print("Leg ");
    UserSerial.println(i);
    UserSerial.print("X = ");
    UserSerial.println(GaitGenOut[i][0]);
    UserSerial.print("Y = ");
    UserSerial.println(GaitGenOut[i][1]);
    UserSerial.print("Z = ");
    UserSerial.println(GaitGenOut[i][2]);
    UserSerial.println("------");
    UserSerial.print("Coxa = ");
    UserSerial.println(LegCalculateOut[i][0]);
    UserSerial.print("Femur = ");
    UserSerial.println(LegCalculateOut[i][1]);
    UserSerial.print("Tibia = ");
    UserSerial.println(LegCalculateOut[i][2]);
    UserSerial.print("Tharsus = ");
    UserSerial.println(LegCalculateOut[i][3]);
    UserSerial.println("\n");
  }
  delay(100);

}
