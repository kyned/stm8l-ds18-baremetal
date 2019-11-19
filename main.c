#include "main.h"
#include "onewire_drvr.h"


unsigned long int delay_;


void          USART_init(void);

int           integer_part_value(unsigned char*);
unsigned int  decimal_part_value(unsigned char*);

/** enable `printf` as an interface to USART1
 */
int putchar(int c)
{
  while(!(UART1_SR & UART_SR_TXE));
  UART1_DR = c;
  return(c);
}

void main(void) {

  /* Clock divider. Default value is 0x03. Now clock frequency is set 16MHz: */
  CLK_DIVR = 0x00;

  USART_init();

  for (;;) {

    for (delay_ = 0; delay_ < 450000; delay_++) {}

    if (!onewire_presence()) {
      continue;
    }

    /* commands: skip ROM and convert temperature */
    onewire_writebyte(SKIP_ROM);
    onewire_writebyte(START_CONVERT);

    /* converting temperature and saving it to the registers takes a while */
    for (delay_ = 0; delay_ < 650000; delay_++) {}

    if (!onewire_presence()) {
      continue;
    }

    /* commands: skip ROM and raturn converted values */
    onewire_writebyte(SKIP_ROM);
    onewire_writebyte(READ_MEMORY);

    unsigned char DS_registers_[2];

    DS_registers_[1] = onewire_readbyte();
    DS_registers_[0] = onewire_readbyte();

    printf("%d.%u\n\r", integer_part_value(DS_registers_),
                        decimal_part_value(DS_registers_));
  }
}

/** USART (USART1) setup
 */
void USART_init(void) {

  CLK_PCKENR1 |= (1 << 5);                         // Enable clock to USART1 

  UART1_CR2 = UART_CR2_TEN;                        // Allow TX and RX
  UART1_CR3 &= ~(UART_CR3_STOP1 | UART_CR3_STOP2); // 1 stop bit
  UART1_BRR2 = 0x0B; UART1_BRR1 = 0x08;            // 115200 baud

}

/** integer part of a temperature is stored in 8 bits split between 2 registers.
 * for detailed explanaition you may refer to DS18 reference manual.
 */
int integer_part_value(unsigned char *temperature_representation) {

  int resulting_value = 0x00;
  resulting_value |= ((temperature_representation[0] << 4) & 0xF0);  
  resulting_value |= ((temperature_representation[1] >> 4) & 0x0F);  

  return resulting_value;

}

/** by default decimal precision is 0.0625, value is stored in 4 bits.
 * for detailed explanaition you may refer to DS18 reference manual.
 */
unsigned int decimal_part_value(unsigned char *temperature_representation) {

  unsigned int resulting_value = 0x00;
  resulting_value |= (temperature_representation[1] & 0x0F);  
  resulting_value *= 625;

  return resulting_value;

}
