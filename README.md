
# UART Communication on TM4C123GH6PM

## Overview

This project provides a simple device driver for UART communication between boards running on the TM4C123GH6PM microcontroller. The project aims to facilitate board-to-board communication using UART1. The mini-project sends a signal from one board to another to turn on an LED.

Note: src/inc folder contains the source code and header files used for the UART device driver. The folders are only used for organization purposes. The entire project can be found in the Keilv5_proj folder.

V-0.2 updates: 
- Added a list of colors in order: DARK, RED, BLUE, GREEN
- Added a state/index variable to keep track of the current color across boards

### Features

- UART Initialization
- Data Transmission
- Data Reception
- Board to Board Communication via UART1

### Dependencies

- TM4C123GH6PM microcontroller
- Keil uVision IDE

### How to Run

1. Clone the repository.
2. Open the Keilv5_proj folder project in Keil uVision 5.
3. Build the project.
4. Turn on TM4C123GH6PM board 1 and upload the compiled code to your TM4C123GH6PM board 1.
5. Turn off TM4C123GH6PM board 1.
6. Turn on TM4C123GH6PM board 2 and upload the compiled code to your TM4C123GH6PM board 2.
7. Turn on both boards.
8. Connect PB1 and PB0 of board 1 to PB0 and PB1 of board 2 respectively for UART communication.
    - See schematic for more details.
9. Press SW2 to switch between colors on board.
10. Press SW1 to send the current color to the other board.
    - current color/state will be synced across boards
11. Repeat steps 9 and 10 to change the color of the LED on board 2.
### Files

- `startup.s`: Startup code for Keil's uVision.
- `tm4c123gh6pm.h`: Register definitions for TM4C123GH6PM.
- `UART.c`: Device driver for UART.
- `UART.h`: Header file for UART device driver.
- `UARTB2BRxInt.c`: Example program for board-to-board communication.

## Hardware and GPIO Ports

### GPIO_PORTF Table

| Pin  | Usage                     |
|:----:|:-------------------------:|
| PF4  | Onboard Switch 1          |
| PF3  | Onboard LED 3 (Green)     |
| PF2  | Onboard LED 2 (Blue)      |
| PF1  | Onboard LED 1 (Red)       |
| PF0  | Onboard Switch 2          |

### GPIO_PORTB Table
| Pin  | Usage                     |
|:----:|:-------------------------:|
| PB1  | UART1 Rx (Receive)        |
| PB0  | UART1 Tx (Transmit)       |
