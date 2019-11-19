# STM8L-DS18-BAREMETAL

This project is an example of interfacing [DS18B20 temperature sensor](https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf) with the help of [stm8l-discovery](https://www.st.com/en/evaluation-tools/stm8l-discovery.html) board.
DS18 utilizes 1-wire protocol to interact with a master device. So, this repository consists of a simple implementation of 1-wire driver for **stm8l-discovery** board and the main program controlling the interaction process itself.

### Building
To build this project you have to have SDCC compiler installed on your laptop. **Makefie** is provided for convenience.
To download executable code to discovery board author tested and used [stm8flash](https://github.com/vdudouyt/stm8flash) utility. Make sure you have that utility installed and then run `make flash` after building the project.

### Additional notice
Since very few peripherals (`USART1` and `GPIOD pin 1` as a *data line*) are involved in the current implementation of the project, the author decided not to use **stm8l15x.h** header - part of *STM8L15x_StdPeriph_Driver* library provided by **ST** and addressed all corresponding registers in a bare-metal fashion. Reading/Reimplementing code that has been written in this manner also an interesting exercise itself, so if you're a student you may benefit from doing so even more than if you'd just downloaded a project utilizing mentioned earlier library.

## LICENCE
Feel free to use this source code however you want. 
If this code was useful for you in any way the author is surely happy.
