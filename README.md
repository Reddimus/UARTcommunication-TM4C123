
# UART Communication on TM4C123GH6PM

## Overview

This project provides a simple device driver for UART communication between boards running on the TM4C123GH6PM microcontroller. The project aims to facilitate computer-to-board communication using UART. The mini-project has a terminal interface that allows the user to send and receive data from the board. The project only has mode 1 that allows

Note: src/inc folder contains the source code and header files used for the UART device driver. The folders are only used for organization purposes. The entire project can be found in the Keilv5_proj folder.

V-1.1 update: The project now has a terminal interface that allows the user to send and receive data from the board. The project only has mode 1 that allows the user to change the color of the onboard LED and the brightness of the onboard LED.

V-1.2 update: The project now cycles through colors in a round robin fashion order when Switch 2 is pressed and relays each change to PC serial terminal 1. When a color is picked and shared with MCU2 via SW1, both MCU 1 will enter an idle state, awaiting color codes from MCU 2 and vice versa. This exchange between MCUs is a continuous process. To terminate Mode 2, send a ^ symbol from PC serial terminal 1.

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

### GPIO_PORTA Table

| Pin  | Usage                     |
|:----:|:-------------------------:|
| PA1  | UART0 Tx (Transmit)       |
| PA0  | UART0 Rx (Receive)        |

### GPIO_PORTD Table

| Pin  | Usage                     |
|:----:|:-------------------------:|
| PD7  | UART2 Tx (Transmit)       |
| PA6  | UART2 Rx (Receive)        |

### GPIO_PORTC Table

| Pin  | Usage                     |
|:----:|:-------------------------:|
| PC7  | UART3 Tx (Transmit)       |
| PC6  | UART3 Rx (Receive)        |


# Mode 1: PC ↔ MCU1 LED Control

In Mode 1, only MCU1 and PC serial terminal 1 partake in the communication process. 

## Baud Rate Specifications:
- Communication between MCU1 and PC serial terminal 1: `57600`

## System State:
- MCU2 remains in an idle state.
- PC serial terminal 2 consistently displays its starting message.
- PC serial terminal 1 exhibits the "Mode 1 menu".

## Menu Details:

### Option 1:
1. Once option `1` is chosen from the Mode 1 menu, MCU1 begins communication by prompting PC serial terminal 1 to choose an LED color for display on MCU_1.
   - Available color choices:
     - `r`: Red
     - `g`: Green
     - `b`: Blue
     - `p`: Purple
     - `y`: Yellow
     - `w`: White
     - `d`: Dark
2. Upon user input of a color letter (followed by a carriage return):
   - MCU1 updates its LEDs to the specified color.
   - A confirmation message returns to PC serial terminal 1. 
     - For instance, if `r` is selected, the message will be: 
       ```
       Red LED is on
       ```
   - The Mode 1 menu reappears on PC serial terminal 1.

### Option 2:
1. On selection of option `2` from the Mode 1 menu, a new prompt appears on PC serial terminal 1 asking for a decimal number.
2. This entered number determines the duty cycle, ranging from `0%` to `100%`.
3. A PWM (Pulse-Width Modulation) signal, based on the duty cycle, is generated. This signal controls the brightness of the current LED(s).
4. A confirmation message is then sent to PC serial terminal 1, after which the Mode 1 menu re-emerges.

### Option 3:
1. By selecting option `3` from the Mode 1 menu, the system concludes Mode 1 operations.
2. PC serial terminal 1 then displays its main menu.

# Mode 2 Communication System

In Mode 2, all four members of the communication system are actively involved. 

## Baud Rate Specifications:
- PC serial terminal 1 ↔ MCU1, MCU2 ↔ PC serial terminal 2: `57600`
- MCU1 ↔ MCU2: `38400`

## Communication Ports:
- MCU1 uses `UART2` to communicate with MCU2.
- MCU2 uses `UART3` to communicate with MCU1.

## Initiation:
MCU1 will initiate the communication. To terminate the mode at any given time, a user can input the symbol `^` at PC serial terminal 1. MCU1's UART0 RX interrupt will capture this termination request.

## Operation:

### On Entering Mode 2:
Both PC terminals will display messages, setting the initial context for the user.

### Step 1:
- Use `SW2` on MCU1 to cycle through colors on a color wheel in a round robin fashion.
- On every color change, PC serial terminal 1 should update to show:

### Step 2:
- Once a color is selected on MCU1 and sent to MCU2 by pressing `SW1`, MCU1 enters an idle state. It awaits a color code from MCU2.
- Both PC serial terminals will display updated messages to reflect this change.

### Step 3:
- For MCU2, every LED color change should update PC serial terminal 2 to display the current color.

### Step 4:
- After MCU2 selects its color and sends it to MCU1 via the `SW1` button, MCU2 then goes idle, awaiting a color code from MCU1.

These steps (1 to 4) are repeated continuously during the operation of Mode 2. 

To exit Mode 2, sending a `^` symbol from PC serial terminal 1 to MCU1 will suffice. Remember that MCU1 UART0 RX interrupt is required to detect this termination request.

### Post Termination:
After Mode 2 concludes:
1. All LEDs on both MCUs are turned off.
2. The two PC serial terminals return to the main menu.