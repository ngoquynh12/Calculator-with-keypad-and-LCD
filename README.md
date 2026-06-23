# Calculator with Keypad and LCD

## Overview

This project presents the design and implementation of an embedded calculator system using a PIC16F877A microcontroller, a 5×4 keypad, and a 16×2 LCD display.

The calculator allows users to perform basic arithmetic operations, evaluate expressions containing parentheses, and calculate trigonometric functions. Input is provided through a keypad while results are displayed in real time on an LCD screen.

The project was developed as part of the **Embedded System Design** course at Ho Chi Minh City University of Technology (HCMUT).

---

## Features

### Basic Arithmetic Operations
- Addition (+).
- Subtraction (-).
- Multiplication (*).
- Division (/).

### Advanced Functions
- Parentheses support.
- Expression evaluation with operator precedence.
- Decimal number calculations.
- Negative number handling.
- Trigonometric functions: Sine (sin), Cosine (cos), Tangent (tan) and Cotangent (cot).

### User Interface
- 5×4 matrix keypad input.
- 16×2 LCD display output.
- Error notification for invalid expressions.
- Clear function for resetting calculations.
- Mode switching between basic and trigonometric calculations.

---

## Hardware Components

| Component                 | Function             |
| ------------------------- | -------------------- |
| PIC16F877A                | Main microcontroller |
| 5×4 Matrix Keypad         | User input           |
| LCD1602                   | Result display       |
| 20 MHz Crystal Oscillator | System clock         |
| LM7805                    | Voltage regulator    |
| Push Button               | Reset function       |
| Resistors & Capacitors    | Supporting circuitry |
| 9V Power Supply           | System power source  |

---

## Software Features

### Expression Processing
The system supports:
- Multi-digit numbers
- Decimal numbers
- Nested arithmetic expressions
- Parentheses handling
- Operator precedence

Example:
```text
(5*2)+3
Result = 13
```
### Error Handling

Examples:
```text
3**3      -> ERROR
3//3      -> ERROR
5/0       -> Division by zero
```
### Trigonometric Functions
Examples:
```text
sin(30) = 0.50000
cos(60) = 0.50000
tan(45) = 1.00000
```

---

## Development Environment

### Hardware Design
- Proteus.

### Firmware Development
- CCS C Compiler.
- PIC16F877A.

### Programming Language
- Embedded C

---

## Results

The calculator successfully:
- Performs arithmetic calculations accurately.
- Handles decimal and negative numbers.
- Supports parentheses and operator precedence.
- Executes trigonometric functions.
- Displays results on LCD with five decimal places.
- Detects invalid expressions and reports errors.

The system demonstrates the integration of keypad input, LCD interfacing, mathematical expression parsing, and embedded programming using a PIC microcontroller.

---

## Team Members
- **Ngô Diễm Quỳnh** – 2212887
- **Nguyễn Trọng Tuấn** – 2213794
- **Trần Đoàn Minh Huy** – 2211280

Course: **Embedded System Design**

Ho Chi Minh City University of Technology (HCMUT)

Academic Year: 2024

---

## License

This project is intended for educational and academic purposes.
