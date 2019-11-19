#include "onewire_drvr.h"

#define    TIME_RESET       1200                    // ~520 us
#define    TIME_SLOT        200                     // ~ 90 us
#define    TIME_READ        10                      // ~  5 us
#define    TIME_INIT        25                      // ~ 12 us

#define    PD               (stm8_port_t*)0x500F    // GPIOD base

stm8_port_t* OW_port = PD; /* configured as `pseudo open-drain` */
uint8_t      OW_bit  =  1;

/** due to littleness of time intervals used by 1-wire protocol
 * instead of using hardware timer it's better to stick to while loops.
 */
void onewire_delay(int delay_) {
  while(delay_--);
}

void onewire_reset(void) {

  OW_port->DDR |= 1 << OW_bit;
  onewire_delay(TIME_RESET);
  OW_port->DDR &= ~(1 << OW_bit);

}

/** Checking for presence of 1-wire devices.
 */
bool onewire_presence() {

  bool presence_ = false;

  onewire_reset();
  onewire_delay(TIME_INIT);

  /* 10 attempts to catch presence of a device */
  int counter = 10;

  while(counter--) {
  onewire_delay(TIME_READ);
    if (!(OW_port->IDR & (1 << OW_bit))) {
      presence_ = true;
    }
  }
  onewire_delay(TIME_SLOT);
  return presence_;
}

uint8_t onewire_readbyte() {
  uint8_t byte_ = 0x00;
  int i;
  for (i = 0; i < 8; i++) {
    byte_ |= onewire_in_bit() << i;
    onewire_delay(TIME_INIT);
  }
  return byte_;
}

bool onewire_in_bit() {
  OW_port->DDR |= 1 << OW_bit;
  onewire_delay(TIME_INIT);
  OW_port->DDR &= ~(1 << OW_bit);
  onewire_delay(TIME_READ);

  if (OW_port->IDR & (1 << OW_bit)) {
    onewire_delay(TIME_SLOT - TIME_INIT - TIME_READ);  
    return true; 
  } else {
    onewire_delay(TIME_SLOT - TIME_INIT - TIME_READ);  
    return false;
  }
}

void onewire_writebyte(char byte_) {
  int i;
  for (i = 0; i < 8; i++) {
    onewire_delay(TIME_INIT);
    onewire_out_bit((bool)(byte_ & 0x01));
    byte_ >>= 1;
  }
}

void onewire_out_bit(bool bit_) {
  if (bit_) {  
    OW_port->DDR |= 1 << OW_bit;
    onewire_delay(TIME_INIT);
    OW_port->DDR &= ~(1 << OW_bit);
    onewire_delay(TIME_SLOT - TIME_INIT);
  } else {
    OW_port->DDR |= 1 << OW_bit;
    onewire_delay(TIME_SLOT);
    OW_port->DDR &= ~(1 << OW_bit);
  }
  onewire_delay(TIME_INIT);
}
