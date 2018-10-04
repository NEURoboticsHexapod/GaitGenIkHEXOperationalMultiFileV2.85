


/*
  Quadraped Gait generator leg test
 uses globals for leg transitions and should not be run on multithreaded chips. Also uses floats.
 X Axis is to the Front
 Y Axis is to the right
 Z Axis is to the top
 
 +X
 ^    Front
 |
 |   0  ^  1
 |4__\\| |//___5
 |   //| |\\
 |   3  v  2
 o---------->+Y
 
 This code runs on commander packets and moves based on that.
 
 example packets
 (0xff, 0x80, 0x80, 0x80, 0x80, 0x0, 0x0, 0xff),(255, 128, 128, 128, 128, 0, 0, 255), This is standard, all joysticks centered and no buttons or extended byte.
 (0xff, 0xeb, 0x80, 0x80, 0x80, 0x0, 0x0, 0x94),(255, 235, 128, 128, 128, 0 ,0, 148), This is left stick up, all other values centered or zero.
 
 
 */










