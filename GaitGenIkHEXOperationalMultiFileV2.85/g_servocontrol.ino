// Constants that will be included in every packet sent to the microcontroller.
const byte HEADER_CONST = 170;
const byte DEVICE_ID = 12;
const byte COMMAND_ID = 04;

// map values to the servos, test for boundries and write to servos
void DXLServoMap() {
  // Iterate through each leg.
  for (int i = 0; i < 6; i++) {
    // Iterate through each servo on each leg.
    for (int j = 0; j < 3; j++) {
      // Calculate the desired degree position of the servo.
      int deg = LegDynamixels[i][j] * (180 / 3.14159);
      // Map the degree value of the servo to a microsecond value.
      int servoPos = map(deg, -150, 150, 0, 1024);

      if (servoPos > DXLServoLimits[i][j][0] && servoPos < DXLServoLimits[i][j][1]) {
        // If the servo is within the limits, write the move command to the servo.
        servoWrite(DXLServoLimits[i][j][2], ServoPos);
        UserSerial.println("Wrote to servo " + j + " on leg " + i);
      } else {
        // If the servo is not within the limits, do nothing.
        UserSerial.println("Servo " + j + " on leg " + i + " out of limits");
      }
    }
  }
}

// Writes a packet to move a servo with the ID [servoID] to position [pos].
// Position represents a pulse length in microseconds.
void servoWrite(int servoID, int pos) {
  // The header for the communication protocol.
  // Represents the start of a packet.
  byte header = HEADER_CONST;
  // Identifies the target microcontroller.
  byte device = DEVICE_ID;
  // Identifies the type of command being sent to the microcontroller.
  // In this case, the constant 0x04 represents a set servo position command.
  byte comm = COMMAND_ID;
  // Identifies the servo that is being manipulated.
  // Constraining to [0, 999] ensures a valid servo.
  // TODO: Change this to ensure that we are moving a valid servo.
  byte servo = constrain(servoID, 0, 999);
  // The lower 7 bits of the position.
  byte lower = 0;
  // The upper 7 bits of the position.
  byte upper = 0;
  // The scaled position.
  unsigned long scaledPos = pos * 4;
  UserSerial.println(ScalePos);

  // Write the position bits.
  for (int i = 0; i < 7; i++) {
    bitWrite(lower, i, bitRead(scaledPos, i));
    bitWrite(upper, i, bitRead(scaledPos, i + 7));
  }

  // Write the packet to the console for debugging purposes.
  UserSerial.println(header);
  UserSerial.println(device);
  UserSerial.println(comm);
  UserSerial.println(servo);
  UserSerial.println(lower);
  UserSerial.println(upper);

  // Write the packet to the hardware serial port.
  AXSerial.write(header);
  AXSerial.write(device);
  AXSerial.write(comm);
  AXSerial.write(servo);
  AXSerial.write(lower);
  AXSerial.write(upper);
}


