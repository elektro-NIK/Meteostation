#include"MAX7219.h"

void MAX7219_Init() {
  DDR_CS  |= 1<<CS;
  DDR_DIN |= 1<<DIN;
  DDR_CLK |= 1<<CLK;
  MAX7219_Normal_Mode();
  MAX7219_Set_Num_Digs(NUM_DIGS);
  MAX7219_Set_Brightness(BRIGH_LVL);
}

void MAX7219_Normal_Mode() {
  MAX7219_Write(SHUTDOWN, SHUTDOWN_OFF);
  MAX7219_Write(TEST, TEST_OFF);
}

void MAX7219_Set_Num_Digs(uint8_t digs) {
  MAX7219_Write(SCAN_LIMIT, digs-1);
}

void MAX7219_Set_Brightness(uint8_t bright) {
  MAX7219_Write(INTENSITY, bright);
}

void MAX7219_Clr_Scr() {
  for(uint8_t i=1; i<=8; i++) {
    MAX7219_Write(i, 0x00);
  }
}

void MAX7219_Write(uint8_t Adress, uint8_t Data) {
  PORT_CS |= 1<<CS;
  for(uint8_t i=8; i>0; i--) {
    uint8_t mask = 1 << (i-1);
    PORT_CLK &= ~(1<<CLK);
    if(Adress & mask)
      PORT_DIN |= 1<<DIN;
    else
      PORT_DIN &= ~(1<<DIN);
    PORT_CLK |= 1<<CLK;
  }
  for(uint8_t i=8; i>0; i--) {
    uint8_t mask = 1 << (i-1);
    PORT_CLK &= ~(1<<CLK);
    if(Data & mask)
      PORT_DIN |= 1<<DIN;
    else
      PORT_DIN &= ~(1<<DIN);
    PORT_CLK |= 1<<CLK;
  }
  PORT_CS &= ~(1<<CS);
  PORT_CS |= 1<<CS;
}