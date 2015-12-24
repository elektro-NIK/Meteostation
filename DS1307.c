#include "DS1307.h"

void DS_Read_Data (uint8_t *ret, uint8_t addr, uint8_t size) {
  uint8_t msg[size+1];                                          // Buffer for transmition
  msg[0] = DS1307_ADDR<<1 | TWI_WRITE<<TWI_RW_BIT;              // SLA+W
  msg[1] = addr;                                                // Address
  TWI_Start_Transmition (msg, 2);                               // Write Addr in slave counter
  msg[0] = DS1307_ADDR<<1 | TWI_READ<<TWI_RW_BIT;               // SLA+R
  TWI_Start_Transmition (msg, size+1);                          // Read bytes from slave
  TWI_Get_Data(msg, size+1);                                    // Copy message to buffer
  for(uint8_t i=0; i<size; i++)                                 // Remove first byte (SLA)
    *(ret+i) = *(msg+i+1);
}

void DS_Write_Data (uint8_t *data, uint8_t addr, uint8_t size) {
  const uint8_t msg_size = size+2;                              // Define the massage size
  uint8_t msg[msg_size];                                        // Buffer for transmition
  msg[0] = DS1307_ADDR<<1 | TWI_WRITE<<TWI_RW_BIT;              // SLA+W
  msg[1] = addr;                                                // Address
  for(uint8_t i=0; i<size; i++)                                 // Copy data to buffer
    msg[i+2] = *(data+i);
  TWI_Start_Transmition (msg, msg_size);                        // Start transmition
}

uint8_t int2bcd(uint8_t in_t) {
  return in_t/10*16+in_t%10;                                    // Convert unsigned integer to BCD
}

void Read_Time (uint8_t *ret) {
  DS_Read_Data(ret, DS_SEC_ADDR, 3);
}

void Write_Time (uint8_t hour, uint8_t min, uint8_t sec) {
  uint8_t data[3] = {
    int2bcd(sec),
    int2bcd(min),
    int2bcd(hour)
  };
  DS_Write_Data(data, DS_SEC_ADDR, 3);
}

void Read_Date (uint8_t *ret) {
  DS_Read_Data(ret, DS_DAY_ADDR, 4);
}

void Write_Date (uint8_t year, uint8_t month, uint8_t date, uint8_t day) {
  uint8_t data[4] = {
    int2bcd(day),
    int2bcd(date),
    int2bcd(month),
    int2bcd(year)
  };
  DS_Write_Data(data, DS_DAY_ADDR, 4);
}

void SQW_OUT (uint8_t byte) {
  DS_Write_Data(&byte, DS_CTRL_ADDR, 1);
}
