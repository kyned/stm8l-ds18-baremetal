#ifndef __ONEWIRE_DRVR_H
#define __ONEWIRE_DRVR_H

#include "main.h"

/*                  ROM INSTRUCTIONS (1-Wire)     */
#define SEARCH ROM          0xF0
#define READ_ROM            0x33
#define MATCH_ROM           0x55
#define SKIP_ROM            0xCC

/*           FUNCTIONAL INSTRUCTIONS (1-Wire)     */
#define START_CONVERT       0x44
#define WRITE_MEMORY        0x4E
#define READ_MEMORY         0xBE

void onewire_delay(int delay_);

void onewire_reset(void);
bool onewire_presence();

void onewire_writebyte(char byte_);
void onewire_out_bit(bool bit_);
bool onewire_in_bit();
uint8_t onewire_readbyte();

#endif /* __ONEWIRE_DRVR_H */
