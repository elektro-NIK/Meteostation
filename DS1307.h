#ifndef __DS1307_h__
#define __DS1307_h__

#define DS1307_ADDR               0x68
// Registers and bits positions:
#define DS_SEC_ADDR               0x00
#define DS_MIN_ADDR               0x01
#define DS_HOUR_ADDR              0x02
#define DS_DAY_ADDR               0x03
#define DS_DATE_ADDR              0x04
#define DS_MONTH_ADDR             0x05
#define DS_YEAR_ADDR              0x06
#define DS_CTRL_ADDR              0x07
#define DS_BEGIN_RAM              0x08
#define DS_END_RAM                0x3F
#define DS_SEC_MASK               0b01111111
#define DS_CH                     7
#define DS_OUT                    7
#define DS_SQWE                   4
#define DS_RS1                    1
#define DS_RS0                    0
#define DS_12_24                  6
#define DS_PM_AM                  5
// Bits values:
#define DS_12                     1
#define DS_24                     0
#define DS_PM                     1
#define DS_AM                     0
// Constants:
#define SQW_1                     (0<<DS_RS1 | 0<<DS_RS0 | 1<<DS_SQWE | 0<<DS_OUT)
#define SQW_4096                  (0<<DS_RS1 | 1<<DS_RS0 | 1<<DS_SQWE | 0<<DS_OUT)
#define SQW_8192                  (1<<DS_RS1 | 0<<DS_RS0 | 1<<DS_SQWE | 0<<DS_OUT)
#define SQW_32768                 (1<<DS_RS1 | 1<<DS_RS0 | 1<<DS_SQWE | 0<<DS_OUT)
#define OUT_0                     (0<<DS_RS1 | 0<<DS_RS0 | 0<<DS_SQWE | 0<<DS_OUT)
#define OUT_1                     (0<<DS_RS1 | 0<<DS_RS0 | 0<<DS_SQWE | 1<<DS_OUT)
#define SQW_OUT_DISABLE           (1<<DS_RS1 | 1<<DS_RS0 | 0<<DS_SQWE | 0<<DS_OUT)

#include <stdint.h>
#include "I2C.h"

void DS_Read_Data (uint8_t *ret, uint8_t addr, uint8_t size);
void DS_Write_Data (uint8_t *data, uint8_t addr, uint8_t size);
void Read_Time (uint8_t *ret);
void Write_Time (uint8_t hour, uint8_t min, uint8_t sec);
void Read_Date (uint8_t *ret);
void Write_Date (uint8_t year, uint8_t month, uint8_t date, uint8_t day);
void SQW_OUT (uint8_t byte);

#endif