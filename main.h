#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>
#include <stdio.h>

#define CLK_DIVR	    (*(volatile uint8_t *)0x50c0) // Clock divider.
#define CLK_PCKENR1	    (*(volatile uint8_t *)0x50c3) // Clock gating.

/** USART1 registers: 
 * For detailed explanation refer to STM8 datasheet/reference manual 
 * of the corresponding processor. 
 */
#define UART1_SR 	    (*(volatile uint8_t *)0x5230)
#define UART1_DR 	    (*(volatile uint8_t *)0x5231)
#define UART1_BRR1	    (*(volatile uint8_t *)0x5232)
#define UART1_BRR2	    (*(volatile uint8_t *)0x5233)
#define UART1_CR2 	    (*(volatile uint8_t *)0x5235)
#define UART1_CR3 	    (*(volatile uint8_t *)0x5236)

/* USART control bits: */
#define UART_CR2_TEN    (1 << 3)
#define UART_CR2_TIEN   (1 << 7)
#define UART_CR3_STOP1  (1 << 4)
#define UART_CR3_STOP2  (1 << 5)
#define UART_SR_TXE     (1 << 7)

/* GPIO port set of registers: */
typedef struct {
  volatile char ODR;
  volatile char IDR;
  volatile char DDR;
  volatile char CR1;
  volatile char CR2;
} stm8_port_t;

typedef enum { false, true } bool;

#endif /* __MAIN_H */
