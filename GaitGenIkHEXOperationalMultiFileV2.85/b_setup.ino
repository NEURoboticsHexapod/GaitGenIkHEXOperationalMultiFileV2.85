void setup(){
  
  

  UserSerial.begin(38400);
  UserSerial.println("Started");
  //Setup Dynamixels
  AXSerial.begin(9600);
  GaitGenControlReset();
}
