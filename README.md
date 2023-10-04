
# UART Communication on TM4C123GH6PM

## Overview

This project provides a simple device driver for UART communication between boards running on the TM4C123GH6PM microcontroller. The project aims to facilitate board-to-board communication using UART1.

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
2. Open the Keilv5_proj folder project in Keil uVision.
3. Build the project.
4. Upload the compiled code to your TM4C123GH6PM board.
5. Connect another board via UART1 for testing.

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
