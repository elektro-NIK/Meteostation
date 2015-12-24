#ifndef __MAX7219_h__
#define __MAX7219_h__

#include<avr/io.h>
/*@{*/ // User defined constants
#define NUM_DIGS        8             // Number of digits
#define BRIGH_LVL       0

#define DDR_CS          DDRC
#define PORT_CS         PORTC
#define PIN_CS          PINC
#define CS              PC1
#define DDR_DIN         DDRC
#define PORT_DIN        PORTC
#define PIN_DIN         PINC
#define DIN             PC0
#define DDR_CLK         DDRC
#define PORT_CLK        PORTC
#define PIN_CLK         PINC
#define CLK             PC2
/*@}*/
/*@{*/ // Constant for inside library use
#define NO_OP           0x00
#define DIGIT0          0x01
#define DIGIT1          0x02
#define DIGIT2          0x03
#define DIGIT3          0x04
#define DIGIT4          0x05
#define DIGIT5          0x06
#define DIGIT6          0x07
#define DIGIT7          0x08
#define DECODE_MODE     0x09
  #define DECODE_NO         0x00
  #define DECODE_0          0x01
  #define DECODE_3_0        0x0F
  #define DECODE_7_0        0xFF
#define INTENSITY       0x0A          // 0x00...0x0F
  #define MIN_BRIGH         0x00
  #define MAX_BRIGH         0x0F
#define SCAN_LIMIT      0x0B          // 0x00...0x07 (from 0 to SCAN_LIMIT digits)
#define SHUTDOWN        0x0C
  #define SHUTDOWN_ON       0x00
  #define SHUTDOWN_OFF      0x01
#define TEST            0x0F
  #define TEST_OFF          0x00
  #define TEST_ON           0x01
/*@}*/

void MAX7219_Init ();
void MAX7219_Normal_Mode();
void MAX7219_Set_Num_Digs(uint8_t digs);
void MAX7219_Set_Brightness(uint8_t bright);
void MAX7219_Write(uint8_t Adress, uint8_t Data);
void MAX7219_Clr_Scr();

#endif // __MAX7219_h__