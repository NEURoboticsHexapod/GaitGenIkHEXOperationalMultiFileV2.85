//This code covers the basic Gait Generator
void GaitGen(int Period, int Cycle, int Xtrans, int Ytrans, int Ztrans, float ZTurn){
    //Sale the inputs
    Xtrans =map(Xtrans,-127,127,-40,40);
    Ytrans =map(Ytrans,-127,127,-40,40);
    Ztrans =map(Ztrans,-127,127,0,20);
    ZTurn  =-map(ZTurn,-127,127,-50,50)/100;

  float Generator1 = ((4.0 *(abs((Cycle%Period)-(Period/2))-(Period/4)))/Period);
  float Generator2 = Generator1;
  int GeneratorZ = (-1*((abs((Cycle%Period)-(Period/2)))/((Cycle%Period)-(Period/2))));
  float Theta1 = (ZTurn * 3.14 / 4 *Generator1);
  
  //Type1 and Type two are added to legs to produce movement
  float Type1[3] = {
    (Xtrans*Generator1),(Ytrans*Generator1),(Ztrans*GeneratorZ)  };
  float Type2[3] = {
    (Xtrans*Generator2),(Ytrans*Generator2),(-Ztrans*GeneratorZ)  };


  //First pass does gait generation for translation
  int Output1[6][3] = {
    { //Leg 0 FL
      (Leg0InitX + Type1[0]),//X (Output[0][0])
      (Leg0InitY + Type1[1]),//Y (Output[0][1])
      (Leg0InitZ + Type1[2]) //Z (Output[0][2])

      },
    { //Leg 1 FR
      (Leg1InitX + Type2[0]),//X
      (Leg1InitY + Type2[1]),//Y
      (Leg1InitZ + Type2[2]) //Z
      },
    { //Leg 2 BR
      (Leg2InitX + Type2[0]),//X
      (Leg2InitY + Type2[1]),//Y
      (Leg2InitZ + Type2[2]) //Z
      },
    { //Leg 3 BL
      (Leg3InitX + Type1[0]),//X
      (Leg3InitY + Type1[1]),//Y
      (Leg3InitZ + Type1[2]) //Z
      },
    { //Leg 4 ML
      (Leg4InitX + Type2[0]),//X
      (Leg4InitY + Type2[1]),//Y
      (Leg4InitZ + Type2[2]) //Z
      },
    { //Leg 5 MR
      (Leg5InitX + Type1[0]),//X
      (Leg5InitY + Type1[1]),//Y
      (Leg5InitZ + Type1[2]) //Z
      },
  };


  //Second pass does gait rotate in place
  int Output2[6][3];
  Output2[0][0] = (Output1[0][0]*cos(Theta1)-Output1[0][1]*sin(Theta1));
  Output2[0][1] = (Output1[0][0]*sin(Theta1)+Output1[0][1]*cos(Theta1));
  Output2[0][2] = Output1[0][2];

  Output2[1][0] = (Output1[1][0]*cos(-Theta1)-Output1[1][1]*sin(-Theta1));
  Output2[1][1] = (Output1[1][0]*sin(-Theta1)+Output1[1][1]*cos(-Theta1));
  Output2[1][2] = Output1[1][2];

  Output2[2][0] = (Output1[2][0]*cos(Theta1)-Output1[2][1]*sin(Theta1));
  Output2[2][1] = (Output1[2][0]*sin(Theta1)+Output1[2][1]*cos(Theta1));
  Output2[2][2] = Output1[2][2];

  Output2[3][0] = (Output1[3][0]*cos(-Theta1)-Output1[3][1]*sin(-Theta1));
  Output2[3][1] = (Output1[3][0]*sin(-Theta1)+Output1[3][1]*cos(-Theta1));
  Output2[3][2] = Output1[3][2];
  
  Output2[4][0] = (Output1[4][0]*cos(-Theta1)-Output1[4][1]*sin(-Theta1));
  Output2[4][1] = (Output1[4][0]*sin(-Theta1)+Output1[4][1]*cos(-Theta1));
  Output2[4][2] = Output1[4][2];
  
  Output2[5][0] = (Output1[5][0]*cos(-Theta1)-Output1[5][1]*sin(-Theta1));
  Output2[5][1] = (Output1[5][0]*sin(-Theta1)+Output1[5][1]*cos(-Theta1));
  Output2[5][2] = Output1[5][2];

  //Update GaitGenOut
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 3; j++){
      GaitGenOut[i][j] = Output2[i][j];
    }
  }

  //Debug Print 
  //UserSerial.print("Generator 1 = ");
  //UserSerial.println(Generator1);
  //UserSerial.print("Generator 2 = ");
  //UserSerial.println(Generator2);
  //UserSerial.print("Generator Z = ");
  //UserSerial.println(GeneratorZ);
  //UserSerial.print("Type1 = ");
  //UserSerial.print(Type1[0]);
  //UserSerial.print(" ");
  //UserSerial.print(Type1[1]);
  //UserSerial.print(" ");
  //UserSerial.println(Type1[2]);
  //UserSerial.print("Type2 = ");
  //UserSerial.print(Type2[0]);
  //UserSerial.print(" ");
  //UserSerial.print(Type2[1]);
  //UserSerial.print(" ");
  //UserSerial.println(Type2[2]);



}
