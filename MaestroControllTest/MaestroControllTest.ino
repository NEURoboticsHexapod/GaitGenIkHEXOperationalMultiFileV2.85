// Test Code for Maestro ServoController

#define UserSerial Serial
#define MaestroSerial Serial2

void ServoWrite(byte ServoID, unsigned int Pos){
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
   
  MaestroSerial.write(Header);
  MaestroSerial.write(Device);
  MaestroSerial.write(TruncatedCommand);
  MaestroSerial.write(Servoplace);
  MaestroSerial.write(Data1);
  MaestroSerial.write(Data2);
}

void setup(){
  UserSerial.begin(9600);
  MaestroSerial.begin(9600);
  delay (2000);
  UserSerial.print("Started");
  UserSerial.print(", Enter a servoID followed by Position in microseconds (Middle 1500)");
  MaestroSerial.print(170);//allows the maestro to set baudrate
}

void loop(){
  UserSerial.print("|");
  if (UserSerial.available() > 1){//more than 2 bytes in the serial buffer
    byte ServoSelect = UserSerial.parseInt();
    unsigned int ServoPos = UserSerial.parseInt();
    UserSerial.print("\n");
    UserSerial.println(ServoSelect);
    UserSerial.println(ServoPos);
    ServoWrite(ServoSelect,ServoPos);
  }
  delay(100);
}
