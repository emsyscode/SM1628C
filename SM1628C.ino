//Driver of display of 7 segments used on DVD players cheaps
/****************************************************/
/* This is only one example of code structure       */
/* OFFCOURSE this code can be optimized, but        */
/* the idea is let it so simple to be easy catch    */
/* where can do changes and look to the results     */
/****************************************************/

#define DSP_in 7// If 0 write LCD, if 1 read of LCD
#define DSP_clk 8 // if 0 is a command, if 1 is a data0
#define DSP_stb 9 // Must be pulsed to LCD fetch data of bus

#define AdjustPins    PIND // before is C, but I'm use port C to VFC Controle signals, if you change the selection of pins, adjuste this port!

/*Global Variables Declarations*/
unsigned char hours = 0;
unsigned char minutes = 0;
unsigned char minute = 0;
unsigned char secs=0;
unsigned char seconds=0;
unsigned char milisec = 0;

unsigned char memory_secs=0;
unsigned char memory_minutes=0;

unsigned char number;
unsigned char numberA0;
unsigned char numberA1;
unsigned char numberB0;
unsigned char numberB1;
unsigned char numberC0;
unsigned char numberC1;
unsigned char numberD0;
unsigned char numberD1;
unsigned char numberE0;
unsigned char numberE1;
unsigned char numberF0;
unsigned char numberF1;

unsigned char digit=0;
unsigned char grid=0;
unsigned char gridSegments = 0b00000011; // Here I define the number of GRIDs and Segments I'm using

boolean flag=true;
boolean flagSecs=false;

unsigned int segORL[16];
 
 //The next lines is the creation of 0 to F chars bit by bit!
unsigned int segNum0[] ={
//0        (0-----3-     ------21) // Digit position
         (0b10000010),(0b00000011), // "f" of all digits and symbol repeat // Symbol MP3
         (0b10000010),(0b00000011), // "e" of all digits and symbol wheel // Symbol CD
         (0b10000010),(0b00000011), // "d" of all digits and symbol wheel // Symbol pause
         (0b10000010),(0b00000011), // "c" of all digits // Symbol DVD
         (0b10000010),(0b00000011), // "b" of all digits// Symbol VDC
         (0b00000000),(0b00000000), // "g" of all digits// Symbol play
         (0b10000010),(0b00000011)  // "a" of all digits // Symbol ":"
};
unsigned int segNum1[] ={
//1        (0-----3-     ------21) // Digit position
         (0b00000000),(0b00000000), // "f" of all digits and symbol repeat // Symbol MP3
         (0b00000000),(0b00000000), // "e" of all digits and symbol wheel // Symbol CD
         (0b00000000),(0b00000000), // "d" of all digits and symbol wheel // Symbol pause
         (0b10000010),(0b00000011), // "c" of all digits // Symbol DVD
         (0b10000010),(0b00000011), // "b" of all digits// Symbol VDC
         (0b00000000),(0b00000000), // "g" of all digits// Symbol play
         (0b00000000),(0b00000000)  // "a" of all digits // Symbol ":"
};
unsigned int segNum2[] ={         
//2        (0-----3-     ------21) // Digit position
         (0b00000000),(0b00000000), // "f" of all digits and symbol repeat // Symbol MP3
         (0b10000010),(0b00000011), // "e" of all digits and symbol wheel // Symbol CD
         (0b10000010),(0b00000011), // "d" of all digits and symbol wheel // Symbol pause
         (0b00000000),(0b00000000), // "c" of all digits // Symbol DVD
         (0b10000010),(0b00000011), // "b" of all digits// Symbol VDC
         (0b10000010),(0b00000011), // "g" of all digits// Symbol play
         (0b10000010),(0b00000011)  // "a" of all digits // Symbol ":"
};
unsigned int segNum3[] ={
//3        (0-----3-     ------21) // Digit position
         (0b00000000),(0b00000000), // "f" of all digits and symbol repeat // Symbol MP3
         (0b00000000),(0b00000000), // "e" of all digits and symbol wheel // Symbol CD
         (0b10000010),(0b00000011), // "d" of all digits and symbol wheel // Symbol pause
         (0b10000010),(0b00000011), // "c" of all digits // Symbol DVD
         (0b10000010),(0b00000011), // "b" of all digits// Symbol VDC
         (0b10000010),(0b00000011), // "g" of all digits// Symbol play
         (0b10000010),(0b00000011)  // "a" of all digits // Symbol ":"
};
unsigned int segNum4[] ={
//4        (0-----3-     ------21) // Digit position
         (0b10000010),(0b00000011), // "f" of all digits and symbol repeat // Symbol MP3
         (0b00000000),(0b00000000), // "e" of all digits and symbol wheel // Symbol CD
         (0b00000000),(0b00000000), // "d" of all digits and symbol wheel // Symbol pause
         (0b10000010),(0b00000011), // "c" of all digits // Symbol DVD
         (0b10000010),(0b00000011), // "b" of all digits// Symbol VDC
         (0b10000010),(0b00000011), // "g" of all digits// Symbol play
         (0b00000000),(0b00000000)  // "a" of all digits // Symbol ":"
};
unsigned int segNum5[] ={
//5        (0-----3-     ------21) // Digit position
         (0b10000010),(0b00000011), // "f" of all digits and symbol repeat // Symbol MP3
         (0b00000000),(0b00000000), // "e" of all digits and symbol wheel // Symbol CD
         (0b10000010),(0b00000011), // "d" of all digits and symbol wheel // Symbol pause
         (0b10000010),(0b00000011), // "c" of all digits // Symbol DVD
         (0b00000000),(0b00000000), // "b" of all digits// Symbol VDC
         (0b10000010),(0b00000011), // "g" of all digits// Symbol play
         (0b10000010),(0b00000011)  // "a" of all digits // Symbol ":"
};
unsigned int segNum6[] ={
//6        (0-----3-     ------21) // Digit position
         (0b10000010),(0b00000011), // "f" of all digits and symbol repeat // Symbol MP3
         (0b10000010),(0b00000011), // "e" of all digits and symbol wheel // Symbol CD
         (0b10000010),(0b00000011), // "d" of all digits and symbol wheel // Symbol pause
         (0b10000010),(0b00000011), // "c" of all digits // Symbol DVD
         (0b00000000),(0b00000000), // "b" of all digits// Symbol VDC
         (0b10000010),(0b00000011), // "g" of all digits// Symbol play
         (0b10000010),(0b00000011)  // "a" of all digits // Symbol ":"
};
unsigned int segNum7[] ={
//7        (0-----3-     ------21) // Digit position
         (0b00000000),(0b00000000), // "f" of all digits and symbol repeat // Symbol MP3
         (0b00000000),(0b00000000), // "e" of all digits and symbol wheel // Symbol CD
         (0b00000000),(0b00000000), // "d" of all digits and symbol wheel // Symbol pause
         (0b10000010),(0b00000011), // "c" of all digits // Symbol DVD
         (0b10000010),(0b00000011), // "b" of all digits// Symbol VDC
         (0b00000000),(0b00000000), // "g" of all digits// Symbol play
         (0b10000010),(0b00000011)  // "a" of all digits // Symbol ":"
};
unsigned int segNum8[] ={
//8        (0-----3-     ------21) // Digit position
         (0b10000010),(0b00000011), // "f" of all digits and symbol repeat // Symbol MP3
         (0b10000010),(0b00000011), // "e" of all digits and symbol wheel // Symbol CD
         (0b10000010),(0b00000011), // "d" of all digits and symbol wheel // Symbol pause
         (0b10000010),(0b00000011), // "c" of all digits // Symbol DVD
         (0b10000010),(0b00000011), // "b" of all digits// Symbol VDC
         (0b10000010),(0b00000011), // "g" of all digits// Symbol play
         (0b10000010),(0b00000011)  // "a" of all digits // Symbol ":"
};
unsigned int segNum9[] ={
//9        (0-----3-     ------21) // Digit position
         (0b10000010),(0b00000011), // "f" of all digits and symbol repeat // Symbol MP3
         (0b00000000),(0b00000000), // "e" of all digits and symbol wheel // Symbol CD
         (0b00000000),(0b00000000), // "d" of all digits and symbol wheel // Symbol pause
         (0b10000010),(0b00000011), // "c" of all digits // Symbol DVD
         (0b10000010),(0b00000011), // "b" of all digits// Symbol VDC
         (0b10000010),(0b00000011), // "g" of all digits// Symbol play
         (0b10000010),(0b00000011)  // "a" of all digits // Symbol ":"
};
unsigned int segNumA[] ={
//A        (0-----3-     ------21) // Digit position
         (0b10000010),(0b00000011), // "f" of all digits and symbol repeat // Symbol MP3
         (0b10000010),(0b00000011), // "e" of all digits and symbol wheel // Symbol CD
         (0b00000000),(0b00000000), // "d" of all digits and symbol wheel // Symbol pause
         (0b10000010),(0b00000011), // "c" of all digits // Symbol DVD
         (0b10000010),(0b00000011), // "b" of all digits// Symbol VDC
         (0b10000010),(0b00000011), // "g" of all digits// Symbol play
         (0b10000010),(0b00000011)  // "a" of all digits // Symbol ":"
};
unsigned int segNumB[] ={
//B        (0-----3-     ------21) // Digit position
         (0b10000010),(0b00000011), // "f" of all digits and symbol repeat // Symbol MP3
         (0b10000010),(0b00000011), // "e" of all digits and symbol wheel // Symbol CD
         (0b10000010),(0b00000011), // "d" of all digits and symbol wheel // Symbol pause
         (0b10000010),(0b00000011), // "c" of all digits // Symbol DVD
         (0b00000000),(0b00000000), // "b" of all digits// Symbol VDC
         (0b10000010),(0b00000011), // "g" of all digits// Symbol play
         (0b00000000),(0b00000000)  // "a" of all digits // Symbol ":"
};
unsigned int segNumC[] ={
//C        (0-----3-     ------21) // Digit position
         (0b10000010),(0b00000011), // "f" of all digits and symbol repeat // Symbol MP3
         (0b10000010),(0b00000011), // "e" of all digits and symbol wheel // Symbol CD
         (0b10000010),(0b00000011), // "d" of all digits and symbol wheel // Symbol pause
         (0b00000000),(0b00000000), // "c" of all digits // Symbol DVD
         (0b00000000),(0b00000000), // "b" of all digits// Symbol VDC
         (0b00000000),(0b00000000), // "g" of all digits// Symbol play
         (0b10000010),(0b00000011)  // "a" of all digits // Symbol ":"
};
unsigned int segNumD[] ={
//D        (0-----3-     ------21) // Digit position
         (0b00000000),(0b00000000), // "f" of all digits and symbol repeat // Symbol MP3
         (0b10000010),(0b00000011), // "e" of all digits and symbol wheel // Symbol CD
         (0b10000010),(0b00000011), // "d" of all digits and symbol wheel // Symbol pause
         (0b10000010),(0b00000011), // "c" of all digits // Symbol DVD
         (0b10000010),(0b00000011), // "b" of all digits// Symbol VDC
         (0b10000010),(0b00000011), // "g" of all digits// Symbol play
         (0b00000000),(0b00000000)  // "a" of all digits // Symbol ":"
};
unsigned int segNumE[] ={
//E        (0-----3-     ------21) // Digit position
         (0b10000010),(0b00000011), // "f" of all digits and symbol repeat // Symbol MP3
         (0b10000010),(0b00000011), // "e" of all digits and symbol wheel // Symbol CD
         (0b10000010),(0b00000011), // "d" of all digits and symbol wheel // Symbol pause
         (0b00000000),(0b00000000), // "c" of all digits // Symbol DVD
         (0b00000000),(0b00000000), // "b" of all digits// Symbol VDC
         (0b10000010),(0b00000011), // "g" of all digits// Symbol play
         (0b10000010),(0b00000011)  // "a" of all digits // Symbol ":"
};
unsigned int segNumF[] ={
//F        (0-----3-     ------21) // Digit position
         (0b10000010),(0b00000011), // "f" of all digits and symbol repeat // Symbol MP3
         (0b10000010),(0b00000011), // "e" of all digits and symbol wheel // Symbol CD
         (0b00000000),(0b00000000), // "d" of all digits and symbol wheel // Symbol pause
         (0b00000000),(0b00000000), // "c" of all digits // Symbol DVD
         (0b00000000),(0b00000000), // "b" of all digits// Symbol VDC
         (0b10000010),(0b00000011), // "g" of all digits// Symbol play
         (0b10000010),(0b00000011)  // "a" of all digits // Symbol ":"
};
//
void SM1628C_init(void){
  delayMicroseconds(200); //power_up delay
  // Note: Allways the first byte in the input data after the STB go to LOW is interpret as command!!!

  // Configure VFD display (grids)
  cmd_with_stb(gridSegments); // cmd 1 // SM1628 is driver of 6 up to 7 grids
  delayMicroseconds(1);
  // Write to memory display, increment address, normal operation
  cmd_with_stb(0b01000000);//(BIN(01000000));
  delayMicroseconds(1);
  // Address 00H - 15H ( total of 11*2Bytes=176 Bits)
  cmd_with_stb(0b11000000);//(BIN(01100110)); 
  delayMicroseconds(1);
  // set DIMM/PWM to value
  cmd_with_stb((0b10001000) | 7);//0 min - 7 max  )(0b01010000)
  delayMicroseconds(1);
}
void cmd_without_stb(unsigned char a){
  // send without stb
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 1; //our bitmask
  
  data=a;
  //This don't send the strobe signal, to be used in burst data send
         for (mask = 00000001; mask>0; mask <<= 1) { //iterate through bit mask
           digitalWrite(DSP_clk, LOW);
                 if (data & mask){ // if bitwise AND resolves to true
                    digitalWrite(DSP_in, HIGH);
                 }
                 else{ //if bitwise and resolves to false
                   digitalWrite(DSP_in, LOW);
                 }
          delayMicroseconds(5);
          digitalWrite(DSP_clk, HIGH);
          delayMicroseconds(5);
         }
   //digitalWrite(DSP_clk, LOW);
}
void cmd_with_stb(unsigned char a){
  // send with stb
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 1; //our bitmask
  
  data=a;
  
  //This send the strobe signal
  //Note: The first byte input at in after the STB go LOW is interpreted as a command!!!
  digitalWrite(DSP_stb, LOW);
  delayMicroseconds(1);
         for (mask = 00000001; mask>0; mask <<= 1) { //iterate through bit mask
           digitalWrite(DSP_clk, LOW);
           delayMicroseconds(1);
                 if (data & mask){ // if bitwise AND resolves to true
                    digitalWrite(DSP_in, HIGH);
                 }
                 else{ //if bitwise and resolves to false
                   digitalWrite(DSP_in, LOW);
                 }
          digitalWrite(DSP_clk, HIGH);
          delayMicroseconds(1);
         }
   digitalWrite(DSP_stb, HIGH);
   delayMicroseconds(1);
}
void test_symbols_DSP(void){
  digitalWrite(DSP_stb, LOW);
      delayMicroseconds(1);
      //cmd_with_stb(gridSegments); // cmd 1 // SM1628C is a drive of 7 grids
      cmd_with_stb(0b01000000);//To set auto-increment
      cmd_with_stb(0b10000000); // cmd 2 //Normal operation; Set pulse as 1/16
             
                          digitalWrite(DSP_stb, LOW);
                          delayMicroseconds(1);
                            cmd_without_stb(0b11000000); // First register in memory position, auto-increment after write is set!
                            //               (3-----0-) // Position of GRIDs
                            //               (------12) // Position of GRIDs
                            cmd_without_stb(0b00000100); //GRD1 Byte 0x00: bit 1="f" digit 3  bit2=Symbol ":", bit 7="f" digit 0 á direita
                            cmd_without_stb(0b00000000); //GRD1 Byte 0x01: bit 0="f" digit 2, bit 1="f" digit 1
                            //
                            cmd_without_stb(0b00000100); //GRD2 Byte 0x02: bit 1="e" digit 3 s and symbol MP3, bit 7="e" digit 0
                            cmd_without_stb(0b00000000); //GRD2 Byte 0x03: bit 0="e" digit 2, bit 1="e" digit 1
                            //
                            cmd_without_stb(0b00000100); //GRD3 Byte 0x04: bit 1="d" digit 3, bit2 =symbol CD, bit 7="d" digit 0 
                            cmd_without_stb(0b00000000); //GRD3 Byte 0x05: bit 0="d" digit 2, bit 1="d" digit 1
                            //
                            cmd_without_stb(0b00000100); //GRD4 Byte 0x06: bit 1="c" digit 3, bit 2 =symbol Pause, bit 7="c" digit 0
                            cmd_without_stb(0b00000000); //GRD4 Byte 0x07: bit 0="c" digit 2, bit 1="c" digit 1
                            //
                            cmd_without_stb(0b00000100); //GRD5 Byte 0x08: bit 1="b" digit 3, bit 2=symbol DVD, bit 7="b" digit 0
                            cmd_without_stb(0b00000000); //GRD5 Byte 0x09: bit 0="b" digit 2, bit 1="b" digit 1
                            //
                            cmd_without_stb(0b00000100); //GRD6 Byte 0x0A: bit 1="g" digito 3, bit 2=symbol  VCD , bit 7="g" digito 0
                            cmd_without_stb(0b00000000); //GRD6 Byte 0x0B: bit 0="g" digito 2, bit 1="g" digito 1
                            //
                            cmd_without_stb(0b00000100); //GRD7 Byte 0x0C: bit 1="a" digito 3, bit 2=symbol  Play , bit 7="a" digito 0 
                            cmd_without_stb(0b00000000); //GRD7 Byte 0x0D: bit 0="a" digito 2, bit 1="a" digito 1
                            //
                            digitalWrite(DSP_stb, HIGH);
                            cmd_with_stb((0b10001000) | 7); //cmd 4
                            delay(200);
}
void test_numbers_DVD(void){
  for (uint8_t x=0; x < 2; x++){
    digit=x;
 
          for (int i=0; i< 10;i++){
              delayMicroseconds(1);
              //cmd_with_stb(gridSegments); // cmd 1 // SM1628C is a driver of 7 grids
              cmd_with_stb(0b01000000);//To set auto-increment
              cmd_with_stb(0b10000000); // cmd 2 //Normal operation; Set pulse as 1/16
              digitalWrite(DSP_stb, LOW);
              delayMicroseconds(1);
              cmd_without_stb(0b11000000); // Grids of display... they have done the swap of this pins with segments
              //                    
                                switch (i) {
                                  case 0: 
                                  for(int v=0; v<14; v++){
                                          cmd_without_stb(segNum0[v]);
                                    }break;
                                  case 1: 
                                  for(int v=0; v<14; v++){
                                          cmd_without_stb(segNum1[v]);
                                        }break;
                                  case 2:
                                  for(int v=0; v<14; v++){
                                          cmd_without_stb(segNum2[v]);
                                        } break;
                                  case 3: 
                                  for(int v=0; v<14; v++){
                                          cmd_without_stb(segNum3[v]);
                                        }break;
                                  case 4: 
                                  for(int v=0; v<14; v++){
                                          cmd_without_stb(segNum4[v]);
                                        }break;
                                  case 5:
                                  for(int v=0; v<14; v++){
                                          cmd_without_stb(segNum5[v]);
                                        }break;
                                  case 6: 
                                  for(int v=0; v<14; v++){
                                          cmd_without_stb(segNum6[v]);
                                        }break;
                                  case 7: 
                                  for(int v=0; v<14; v++){
                                          cmd_without_stb(segNum7[v]);
                                        }break;
                                  case 8: 
                                  for(int v=0; v<14; v++){
                                          cmd_without_stb(segNum8[v]);
                                        }break;
                                  case 9:
                                  for(int v=0; v<14; v++){
                                          cmd_without_stb(segNum9[v]);
                                        } break;
                                  default:break;
                                }  
                  digitalWrite(DSP_stb, HIGH);
                  cmd_with_stb((0b10001000) | 7); //cmd 4
                 delay(400);
          }
  }
}
void write_panel_DVD( uint8_t digit, uint8_t grid){
  uint8_t i=digit; //Number to be writed on display
  uint8_t g=grid; //Position of digit where we want write.
  uint8_t  wd0 = 0x00;
  uint8_t  wd1 = 0x00;
  //  
  switch (g) {
    case 0: 
  //            (0-----3-          ------21) // Digit position
       { wd0=(0b10000000); wd1=(0b00000000); break;}
    case 2:
  //            (0-----3-          ------21) // Digit position
        { wd0=(0b00000000); wd1=(0b00000001); break;}
    case 1:
  //            (0-----3-          ------21) // Digit position
        { wd0=(0b00000000); wd1=(0b00000010); break;}
    case 3:
  //            (0-----3-          ------21) // Digit position
        { wd0=(0b00000010); wd1=(0b00000000); break;}
    case 4: 
  //            (0-----3-          ------21) // Digit position
        { wd0=(0b10000000); wd1=(0b00000000); break;}
    case 6:
  //            (0-----3-          ------21) // Digit position
        { wd0=(0b00000000); wd1=(0b00000001); break;}
    case 5:
  //            (0-----3-          ------21) // Digit position
        { wd0=(0b00000000); wd1=(0b00000010); break;}
    case 7:
  //            (0-----3-          ------21) // Digit position
        { wd0=(0b00000010); wd1=(0b00000000); 
          Serial.println(g, BIN);     
          break; }
  default: wd0=(0b10000000); wd1=(0b00000000); break; //This is to accept values big as 7, as default to get the values from 8 to F.
  }
                                switch (i) {
                                  case 0:{ 
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNum0[v] & wd0);
                                          segORL[v+1] = (segNum0[v+1] & wd1);
                                        }break;}
                                  case 1:{ 
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNum1[v] & wd0);
                                          segORL[v+1] = (segNum1[v+1] & wd1);
                                        }break;}
                                  case 2:{
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNum2[v] & wd0);
                                          segORL[v+1] = (segNum2[v+1] & wd1);
                                        }break;}
                                  case 3: {
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNum3[v] & wd0);
                                          segORL[v+1] = (segNum3[v+1] & wd1);
                                        }break;}
                                  case 4: {
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNum4[v] & wd0);
                                          segORL[v+1] = (segNum4[v+1] & wd1);
                                        }break;}
                                  case 5:{
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNum5[v] & wd0);
                                          segORL[v+1] = (segNum5[v+1] & wd1);
                                        }break;}
                                  case 6: {
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNum6[v] & wd0);
                                          segORL[v+1] = (segNum6[v+1] & wd1);
                                        }break;}
                                  case 7: {
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNum7[v] & wd0);
                                          segORL[v+1] = (segNum7[v+1] & wd1);
                                        }break;}
                                  case 8: {
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNum8[v] & wd0);
                                          segORL[v+1] = (segNum8[v+1] & wd1);
                                        }break;}
                                  case 9:{
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNum9[v] & wd0);
                                          segORL[v+1] = (segNum9[v+1] & wd1);
                                        }break;}

                                  case 0xA:{
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNumA[v] & wd0);
                                          segORL[v+1] = (segNumA[v+1] & wd1);
                                        }break;}
                                  case 0xB: {
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNumB[v] & wd0);
                                          segORL[v+1] = (segNumB[v+1] & wd1);
                                        }break;}
                                  case 0xC: {
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNumC[v] & wd0);
                                          segORL[v+1] = (segNumC[v+1] & wd1);
                                        }break;}
                                  case 0xD: {
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNumD[v] & wd0);
                                          segORL[v+1] = (segNumD[v+1] & wd1);
                                        }break;}
                                  case 0xE:{
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNumE[v] & wd0);
                                          segORL[v+1] = (segNumE[v+1] & wd1);
                                        }break;}
                                  case 0xF:{
                                  for(int v=0; v<14; v=v+2){
                                          segORL[v] = (segNumF[v] & wd0);
                                          segORL[v+1] = (segNumF[v+1] & wd1);
                                        }break;}
                                  default:break;
                                } 
                                //
                                  delayMicroseconds(1);
                                  //cmd_with_stb(gridSegments); // cmd 1 // SM1628C is a driver of 7 grids
                                  cmd_with_stb(0b01000000);//To set auto-increment
                                  cmd_with_stb(0b10000000); // cmd 2 //Normal operation; Set pulse as 1/16
                                  digitalWrite(DSP_stb, LOW);
                                  delayMicroseconds(1);
                                  cmd_without_stb(0b11000000); // Grids of display... they have done the swap of this pins with segments
                                        for(int v=0; v<14; v=v+2){
                                          cmd_without_stb(segORL[v]);
                                          cmd_without_stb(segORL[v+1]);
                                          //Serial.println(segORL[v], BIN);
                                        }
                                  digitalWrite(DSP_stb, HIGH);
                                  delayMicroseconds(1);
                                  cmd_with_stb((0b10001000) | 7); //cmd 4
                                  delay(3);//This is the delay of refreshing display!!! This depending also if read keys or other present on loop!!!

                                  // for(int v=0; v<14; v++){
                                  //       segORL[v]=0b00000000;
                                  //       }  
}
void clear_VFD(void){
  /*
  Here I clean all registers 
  Could be done only on the number of grid
  to be more fast. The 7 * 2 bytes = 14 registers
  */
      for (int n=0; n < 14; n++){  // important be 14, if not, bright the half of wells./this on the VFD of 6 grids)
        //cmd_with_stb(gridSegments); // cmd 1 // SM1628C is fixed to 7 grids
      cmd_with_stb(0b01000000);//To set auto-increment
      cmd_with_stb(0b10000000); //cmd 2 //Normal operation; Set pulse as 1/16
      digitalWrite(DSP_stb, LOW);
      delayMicroseconds(1);
            cmd_without_stb((0b11000000) | n); // cmd 3 //wich define the start address (00H to 15H)
            cmd_without_stb(0b00000000); // Data to fill table of 7 grids * 15 segm = 80 bits on the table
            //
            //cmd_with_stb((0b10001000) | 7); //cmd 4
            digitalWrite(DSP_stb, HIGH);
            delayMicroseconds(1);
     }
}
void setup() {
  // put your setup code here, to run once:

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  seconds = 0x00;
  minutes =0x00;
  hours = 0x00;

  /*CS12  CS11 CS10 DESCRIPTION
  0        0     0  Timer/Counter1 Disabled 
  0        0     1  No Prescaling
  0        1     0  Clock / 8
  0        1     1  Clock / 64
  1        0     0  Clock / 256
  1        0     1  Clock / 1024
  1        1     0  External clock source on T1 pin, Clock on Falling edge
  1        1     1  External clock source on T1 pin, Clock on rising edge
  */
  // initialize timer1 
  cli();           // disable all interrupts
  //initialize timer1 
  //noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;// This initialisations is very important, to have sure the trigger take place!!!
  
  TCNT1  = 0;
  
  // Use 62499 to generate a cycle of 1 sex 2 X 0.5 Secs (16MHz / (2*256*(1+62449) = 0.5
  OCR1A = 62498;            // compare match register 16MHz/256/2Hz
  //OCR1A = 1500; // only to use in test, increment seconds to fast!
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= ((1 << CS12) | (0 << CS11) | (0 << CS10));    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  // Note: this counts is done to a Arduino 1 with Atmega 328... Is possible you need adjust
  // a little the value 62499 upper or lower if the clock have a delay or advance on hours.
    
  //  a=0x33;
  //  b=0x01;

  CLKPR=(0x80);
  //Set PORT
  DDRD = 0xFF;  // IMPORTANT: from pin 0 to 7 is port D, from pin 8 to 13 is port B
  PORTD=0x00;
  DDRB =0xFF;
  PORTB =0x00;

  SM1628C_init();

  clear_VFD();

  //only here I active the enable of interrupts to allow run the test of VFD
  //interrupts();             // enable all interrupts
  sei();
}
/******************************************************************/
/************************** Update Clock **************************/
/******************************************************************/
void send_update_clock(void){
    if (secs >=60){
      secs =0;
      minutes++;
      minute++;
    }
    if (minutes >=60){
      minutes =0;
      minute =0;
      hours++;
    }
    if (hours >=24){
      hours =0;
    }
    //*************************************************************
    numberA0=(secs%10);
    numberB0=(secs/10);
    //*************************************************************
    numberC0=(minute%10);
    numberD0=(minute/10);
    //**************************************************************
    numberE0=(hours%10);
    numberF0=(hours/10);
    //**************************************************************
}
void updateDisplay(void){
  //This point here is important, because they used the grid numbers: 7,5,4,3 & 2. 
  //By this reason you need write to the memory correct positions.
  //This assign of grid and memory id, is done in the first switch of function: write_panel_DVD( digit, grid) !!!
    grid=0;
    write_panel_DVD( numberA0, grid);// This is seconds Units, I comment because only have 4 digits display.
    grid=1;
    write_panel_DVD( numberB0, grid);// This is seconds Dozen, I comment because only have 4 digits display.
    grid=2;
    write_panel_DVD( numberC0, grid);// 
    grid=3;
    write_panel_DVD( numberD0, grid);// 
    // grid=2;
    // write_panel_DVD( numberE0, grid);// This is hours Units, I comment because only have 4 digits display.
    // grid=3;
    // write_panel_DVD( numberF0, grid);// This is hours Dozen, I comment because only have 4 digits display.
}
void adjustHMS(){
 // Important is necessary put a pull-up resistor to the VCC(+5VDC) to this pins (3, 4, 5)
 // if dont want adjust of the time comment the call of function on the loop
  /* Reset Seconds to 00 Pin number 3 Switch to GND*/
    if((AdjustPins & 0x08) == 0 )
    {
      _delay_ms(200);
      secs=00;
    }
    
    /* Set Minutes when SegCntrl Pin 4 Switch is Pressed*/
    if((AdjustPins & 0x10) == 0 )
    {
      _delay_ms(200);
      if(minutes < 59)
      minutes++;
      else
      minutes = 0;
    }
    /* Set Hours when SegCntrl Pin 5 Switch is Pressed*/
    if((AdjustPins & 0x20) == 0 )
    {
      _delay_ms(200);
      if(hours < 23)
      hours++;
      else
      hours = 0;
    }
}
void readButtons(){
  int inPin = 7;     // pushbutton connected to digital pin 7
  int val = 0;       // variable to store the read value
  
  byte array[8] = {0,0,0,0,0,0,0,0};

  unsigned char mask = 1; //our bitmask

  array[0] = 1;

  digitalWrite(DSP_stb, LOW);
  delayMicroseconds(2);
  cmd_without_stb(0b01000010); // cmd 2 //10=Read Keys; 00=Wr DSP;
  delayMicroseconds(2);
      
  pinMode(7, INPUT);  // Important this point! Here I'm changing the direction of the pin to INPUT data.
  delayMicroseconds(2);
  //PORTD != B01010100; // this will set only the pins you want and leave the rest alone at
  //their current value (0 or 1), be careful setting an input pin though as you may turn 
  //on or off the pull up resistor  
  //This don't send the strobe signal, to be used in burst data send
         for (int z = 0; z < 4; z++){
             //for (mask=0b00000001; mask > 0; mask <<= 1) { //iterate through bit mask
                   for (int h =8; h > 0; h--) {
                      digitalWrite(DSP_clk, HIGH);  // Remember wich the read data happen when the clk go from LOW to HIGH! Reverse from write data to out.
                      delayMicroseconds(2);
                     val = digitalRead(inPin);
                           if (val & mask){ // if bitwise AND resolves to true
                             //Serial.print(val);
                            //data =data | (1 << mask);
                            array[h] = 1;
                           }
                           else{ //if bitwise and resolves to false
                            //Serial.print(val);
                           // data = data | (1 << mask);
                           array[h] = 0;
                           }
                    digitalWrite(DSP_clk, LOW);
                    delayMicroseconds(2);
                   } 
             
              Serial.print(z);  // All the lines of print is only used to debug, comment it, please!
              Serial.print(" - " );
                        
                                  for (int bits = 7 ; bits > -1; bits--) {
                                      Serial.print(array[bits]);
                                   }                   
                        if (z==0){
                            if(array[5] == 1){
                             flagSecs = !flagSecs;  // This change the app to hours or seconds
                            }
                        }
                        
                        if (z==0){
                            if(array[7] == 1){
                              digitalWrite(10, !digitalRead(10));
                          }
                        }
                        
                        if (z==3){
                           if(array[7] == 1){
                             //digitalWrite(VFD_onRed, !digitalRead(VFD_onRed));
                             //digitalWrite(VFD_onGreen, !digitalRead(VFD_onGreen));
                            }
                          }                        
                  Serial.println();
          }  // End of "for" of "z"
      Serial.println();  // This line is only used to debug, please comment it!

  digitalWrite(DSP_stb, HIGH);
  delayMicroseconds(2);
  cmd_with_stb((0b10001000) | 7); //cmd 4
  delayMicroseconds(2);
  pinMode(7, OUTPUT);  // Important this point! Here I'm changing the direction of the pin to OUTPUT data.
  delay(1); 
}
void loop() {
  // You can comment untill while cycle to avoid the test running.
  for(uint8_t s =0; s < 17; s++){
    write_panel_DVD(s,  s);// Here we send the digit and the grid position to writ to display!
   delay(1200);
  }
  // 
  test_symbols_DSP();
  delay(1500);
  test_numbers_DVD();
  delay(1000);
  clear_VFD();
  delay(200);
  // I decide use the dinamic refreshing, but you can do it at static mode, change code to it
  // you will need draw all segments one time and send the burst of all bytes! 
       while(1){
              //if (flag==false){
                send_update_clock();
                //delay(100);
                readButtons(); //Uncomment if want use buttons on panel, proceed with Id position!
                //delay(100);
                updateDisplay();
                flag=true;
             //}
       }
}
ISR(TIMER1_COMPA_vect)   {  //This is the interrupt request
      secs++;
      flag = false;
} 
