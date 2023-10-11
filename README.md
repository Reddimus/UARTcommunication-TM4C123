
# UART Communication on TM4C123GH6PM

## Overview

This project provides a simple device driver for UART communication between boards running on the TM4C123GH6PM microcontroller. The project aims to facilitate computer-to-board communication using UART. The mini-project has a terminal interface that allows the user to send and receive data from the board. The project only has mode 1 that allows

Note: src/inc folder contains the source code and header files used for the UART device driver. The folders are only used for organization purposes. The entire project can be found in the Keilv5_proj folder.

V-1.1 update: The project now has a terminal interface that allows the user to send and receive data from the board. The project only has mode 1 that allows the user to change the color of the onboard LED and the brightness of the onboard LED.

### Features

- UART Initialization
- Data Transmission
- Data Reception
- Board to Board Communication via UART1

### Dependencies

- TM4C123GH6PM microcontroller
- Keil uVision IDE
- Tera Term VT

### How to Run

1. Clone the repository.
2. Open the Keilv5_proj folder project in Keil uVision 5.
3. Build the project.
4. Turn on TM4C123GH6PM board 1 and upload the compiled code to your TM4C123GH6PM board 1.
5. Communicate with the board using a tera terminal like interface with BAUD rate 57600.
    - Select Mode 1 to change the color of the onboard LED and brightness of the onboard LED.

## Hardware and GPIO Ports

### GPIO_PORTF Table

| Pin  | Usage                     |
|:----:|:-------------------------:|
| PF4  | Onboard Switch 1          |
| PF3  | Onboard LED 3 (Green)     |
| PF2  | Onboard LED 2 (Blue)      |
| PF1  | Onboard LED 1 (Red)       |
| PF0  | Onboard Switch 2          |

