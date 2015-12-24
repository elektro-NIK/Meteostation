#define F_CPU         16000000UL
#define EEPROM_ADDR   0x50
#define RTC_ADDR      0x68

#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "MAX7219.h"
#include "I2C.h"
#include "DS1307.h"

#define SEG_DP        7
#define SEG_A         6
#define SEG_B         5
#define SEG_C         4
#define SEG_D         3
#define SEG_E         2
#define SEG_F         1
#define SEG_G         0

const uint8_t digs[] PROGMEM = {
  1<<SEG_A | 1<<SEG_B | 1<<SEG_C | 1<<SEG_D | 1<<SEG_E | 1<<SEG_F | 0<<SEG_G,
  0<<SEG_A | 1<<SEG_B | 1<<SEG_C | 0<<SEG_D | 0<<SEG_E | 0<<SEG_F | 0<<SEG_G,
  1<<SEG_A | 1<<SEG_B | 0<<SEG_C | 1<<SEG_D | 1<<SEG_E | 0<<SEG_F | 1<<SEG_G,
  1<<SEG_A | 1<<SEG_B | 1<<SEG_C | 1<<SEG_D | 0<<SEG_E | 0<<SEG_F | 1<<SEG_G,
  0<<SEG_A | 1<<SEG_B | 1<<SEG_C | 0<<SEG_D | 0<<SEG_E | 1<<SEG_F | 1<<SEG_G,
  1<<SEG_A | 0<<SEG_B | 1<<SEG_C | 1<<SEG_D | 0<<SEG_E | 1<<SEG_F | 1<<SEG_G,
  1<<SEG_A | 0<<SEG_B | 1<<SEG_C | 1<<SEG_D | 1<<SEG_E | 1<<SEG_F | 1<<SEG_G,
  1<<SEG_A | 1<<SEG_B | 1<<SEG_C | 0<<SEG_D | 0<<SEG_E | 0<<SEG_F | 0<<SEG_G,
  1<<SEG_A | 1<<SEG_B | 1<<SEG_C | 1<<SEG_D | 1<<SEG_E | 1<<SEG_F | 1<<SEG_G,
  1<<SEG_A | 1<<SEG_B | 1<<SEG_C | 1<<SEG_D | 0<<SEG_E | 1<<SEG_F | 1<<SEG_G,
  1<<SEG_A | 1<<SEG_B | 1<<SEG_C | 0<<SEG_D | 1<<SEG_E | 1<<SEG_F | 1<<SEG_G,
  0<<SEG_A | 0<<SEG_B | 1<<SEG_C | 1<<SEG_D | 1<<SEG_E | 1<<SEG_F | 1<<SEG_G,
  1<<SEG_A | 0<<SEG_B | 0<<SEG_C | 1<<SEG_D | 1<<SEG_E | 1<<SEG_F | 0<<SEG_G,
  0<<SEG_A | 1<<SEG_B | 1<<SEG_C | 1<<SEG_D | 1<<SEG_E | 0<<SEG_F | 1<<SEG_G,
  1<<SEG_A | 0<<SEG_B | 0<<SEG_C | 1<<SEG_D | 1<<SEG_E | 1<<SEG_F | 1<<SEG_G,
  1<<SEG_A | 0<<SEG_B | 0<<SEG_C | 0<<SEG_D | 1<<SEG_E | 1<<SEG_F | 1<<SEG_G
};

void Init() {
  MAX7219_Init();
  TWI_Init();
}

int main() {
  Init();
  MAX7219_Clr_Scr();
  sei();
  uint8_t time[3], date[4];
  while(1) {
    Read_Date(date);
    MAX7219_Write(8, pgm_read_byte(&(digs[date[1]>>4])));
    MAX7219_Write(7, pgm_read_byte(&(digs[date[1]&0x0F])) | 1<<SEG_DP);
    MAX7219_Write(6, pgm_read_byte(&(digs[date[2]>>4])));
    MAX7219_Write(5, pgm_read_byte(&(digs[date[2]&0x0F])) | 1<<SEG_DP);
    MAX7219_Write(4, pgm_read_byte(&(digs[2])));
    MAX7219_Write(3, pgm_read_byte(&(digs[0])));
    MAX7219_Write(2, pgm_read_byte(&(digs[date[3]>>4])));
    MAX7219_Write(1, pgm_read_byte(&(digs[date[3]&0x0F])));
    _delay_ms(2000);
    MAX7219_Clr_Scr();
    for(uint8_t i=0; i<10; i++) {
      Read_Time(time);
//       MAX7219_Write(7, pgm_read_byte(&(digs[time[2]>>4])));
//       MAX7219_Write(6, pgm_read_byte(&(digs[time[2]&0x0F])));
//       MAX7219_Write(5, pgm_read_byte(&(digs[time[1]>>4])));
//       MAX7219_Write(4, pgm_read_byte(&(digs[time[1]&0x0F])));
//       MAX7219_Write(3, pgm_read_byte(&(digs[time[0]>>4])));
//       MAX7219_Write(2, pgm_read_byte(&(digs[time[0]&0x0F])));
      MAX7219_Write(6, pgm_read_byte(&(digs[time[2]>>4])));
      MAX7219_Write(5, pgm_read_byte(&(digs[time[2]&0x0F])));
      MAX7219_Write(4, pgm_read_byte(&(digs[time[1]>>4])));
      MAX7219_Write(3, pgm_read_byte(&(digs[time[1]&0x0F])));
      // ------------- Blink:
      MAX7219_Write(5, pgm_read_byte(&(digs[time[2]&0x0F])) | 1<<SEG_DP);
      _delay_ms(500);
      MAX7219_Write(5, pgm_read_byte(&(digs[time[2]&0x0F])));
      _delay_ms(500);
    }
  }
}