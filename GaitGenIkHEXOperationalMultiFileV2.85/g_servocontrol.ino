//map values to the servos, test for boundries and write to servos
void DXLServoMap(){
  for (int i = 0; i < 6; i++){//Iterate through the legs
    for (int j = 0; j < 3; j++){//Iterate through the servos on each leg
      int DegreeAngle = LegDynamixels[i][j] * (180/3.14159);
      int ServoPos = map(DegreeAngle, -150, 150, 0, 1024);
      if ((ServoPos > DXLServoLimits[i][j][0])&&(ServoPos < DXLServoLimits[i][j][1])){// Servo is within limits
        ServoWrite(DXLServoLimits[i][j][2],ServoPos);
        UserSerial.print("G");
      }
      else{//Servo not in limits
        //Do nothing
        UserSerial.print("B");
      }
      //UserSerial.print(ServoLimits[i][j][2]);
      //UserSerial.print(" ");
      //UserSerial.println(ServoPos);
    }
  }
}
//-----------------------------------------------------------------




//-----------------------------------------------------------------
//Write to Servos
void ServoWrite(int ServoID, int Pos){//ServoControl Goes Here
  byte Header = 170; //Header that opens the command and allows autobaudrate to be set
  byte Device = 12; //Identifier for the maestro in case of chaining Default 12
  byte TruncatedCommand = 04;//0x04 represents the command to set servo position
  byte Servoplace = constrain(ServoID,0,999);//127);//the location of the servo on the controller
  byte Data1 = 0;//This holds the lower 7 bits of the position
  byte Data2 = 0;//This holds the upper 7 bits of the position
  unsigned long ScalePos = Pos*4;
  UserSerial.println(ScalePos);
  for (int i = 0; i < 7; i++){
    bitWrite(Data1,i,bitRead(ScalePos,i));
  }
  for (int i = 0; i < 7; i++){
    bitWrite(Data2,i,bitRead(ScalePos,(i+7)));
  }
  //Write the packet
  UserSerial.println(Header);
  UserSerial.println(Device);
  UserSerial.println(TruncatedCommand);
  UserSerial.println(Servoplace);
  UserSerial.println(Data1);
  UserSerial.println(Data2);
  
  
  AXSerial.write(Header);
  AXSerial.write(Device);
  AXSerial.write(TruncatedCommand);
  AXSerial.write(Servoplace);
  AXSerial.write(Data1);
  AXSerial.write(Data2);
}


