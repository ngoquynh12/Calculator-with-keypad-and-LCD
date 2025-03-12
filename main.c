#include "main.h"
#include "keypad.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define MAX_SIZE 20

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Hàm reset máy tính
void reset_calculator(char *buffer, char *num, int *index, int *i, int *num_index, int *op_index, int *mode) {
    lcd_putc('\f');
    lcd_gotoxy(1, 1);
    printf(lcd_putc, " ");
    *index = *i = *num_index = *op_index = 0;
    *mode = 0; // Reset mode
    buffer[0] = num[0] = '\0';
}

// Hàm tính toán k?t qu?
double calculate_result(double *numbers, char *operators, int *num_index, int *op_index) {
    while (*op_index > 0) {
        char op = operators[--(*op_index)];
        double b = numbers[--(*num_index)];
        double a = numbers[--(*num_index)];
        switch (op) {
            case '+': a += b; break;
            case '-': a -= b; break;
            case '*': a *= b; break;
            case '/': 
                if (b == 0.0) {
                    lcd_putc('\f');
                    printf(lcd_putc, "Error: Div by 0");
                    delay_ms(2000);
                    lcd_putc('\f');
                    return 0;
                }
                a /= b; 
                break;
        }
        numbers[(*num_index)++] = a;
    }
    return numbers[0];
}

// Hàm x? l? ngo?c ??n
void process_parentheses(double *numbers, char *operators, int *num_index, int *op_index) {
    while (*op_index > 0 && operators[*op_index - 1] != '(') {
        char op = operators[--(*op_index)];
        double b = numbers[--(*num_index)];
        double a = numbers[--(*num_index)];
        switch (op) {
            case '+': a += b; break;
            case '-': a -= b; break;
            case '*': a *= b; break;
            case '/': a /= b; break;
        }
        numbers[(*num_index)++] = a;
    }
    (*op_index)--; // Lo?i b? '(' kh?i stack
}

// Hàm hi?n th? k?t qu? l??ng giác
void display_trig_result(char func, char *buffer) {
    double value = atof(buffer);
    double result = 0;
    switch (func) {
        case 's': result = sin(value * M_PI / 180); break;
        case 'c': result = cos(value * M_PI / 180); break;
        case 't': result = tan(value * M_PI / 180); break;
        case 'o': result = 1.0 / tan(value * M_PI / 180); break;
    }
    lcd_putc('\f');
    printf(lcd_putc, "%.5f", result);
    delay_ms(3000);
}

void main() {
    char key, buffer[17] = "", num[17] = "";
    int index = 0, i = 0, num_index = 0, op_index = 0;
    double numbers[MAX_SIZE] = {0.0};
    char operators[MAX_SIZE] = {0};
    int mode = 0; // 0 = Basic mode, 1 = Trig mode
    int debounce_delay = 100; // Debounce delay in milliseconds

    lcd_init();
    keypad_init();

    while (TRUE) {
        key = keypad_scan();
        if (key) {
            delay_ms(debounce_delay); // Debouncing
            if (keypad_press()) { // Check if key is still pressed
                if (key == 'C') {
                    reset_calculator(buffer, num, &index, &i, &num_index, &op_index, &mode);
                } else if (key == 'A') {
                    mode = 1 - mode;
                    lcd_putc('\f');
                    buffer[0] = '\0';
                    index = 0;
                } else if (mode == 0) { // Basic mode
                    if ((key >= '0' && key <= '9') || key == '.') {
                        if (i < 16) num[i++] = key;
                        if (index < 16) buffer[index++] = key;
                        num[i] = buffer[index] = '\0';
                        lcd_gotoxy(1, 1);
                        printf(lcd_putc, "%s", buffer);
                    } else if (key == '+' || key == '*' || key == '/' || key == '-') {
                        if (index == 0 && key == '-') {
                            // X? l? tr??ng h?p s? âm ? ??u
                            if (i < 16) num[i++] = key;
                            if (index < 16) buffer[index++] = key;
                            num[i] = buffer[index] = '\0';
                            lcd_gotoxy(1, 1);
                            printf(lcd_putc, "%s", buffer);
                        } else if (index > 0 && (buffer[index - 1] == '+' || buffer[index - 1] == '-' || buffer[index - 1] == '*' || buffer[index - 1] == '/')) {
                            if (key == '-' && (buffer[index - 1] == '*' || buffer[index - 1] == '/' || buffer[index-1] == '+' || buffer[index-1] == '-' )) {
                                // X? l? tr??ng h?p nh? 25*-5 (âm sau toán t?)
                                if (i < 16) num[i++] = key;
                                if (index < 16) buffer[index++] = key;
                                num[i] = buffer[index] = '\0';
                                lcd_gotoxy(1, 1);
                                printf(lcd_putc, "%s", buffer);
                            } else {
                                // Hi?n th? l?i n?u toán t? không h?p l?
                                lcd_putc('\f');
                                printf(lcd_putc, "Error: Invalid");
                                delay_ms(2000);
                                reset_calculator(buffer, num, &index, &i, &num_index, &op_index, &mode);
                            }
                        } else {
                            // X? l? toán t?
                            if (i > 0) {
                                numbers[num_index++] = atof(num);
                                i = 0;
                                num[0] = '\0';
                            }
                            while (op_index > 0 && (operators[op_index - 1] == '*' || operators[op_index - 1] == '/')) {
                                numbers[num_index - 2] = calculate_result(numbers, operators, &num_index, &op_index);
                            }
                            operators[op_index++] = key;
                            if (index < 16) {
                                buffer[index++] = key;
                                buffer[index] = '\0';
                                lcd_gotoxy(1, 1);
                                printf(lcd_putc, "%s", buffer);
                            }
                        }
                    } else if (key == '(') {
                        operators[op_index++] = key;
                        if (index < 16) {
                            buffer[index++] = key;
                            buffer[index] = '\0';
                            lcd_gotoxy(1, 1);
                            printf(lcd_putc, "%s", buffer);
                        }
                    } else if (key == ')') {
                        if (i > 0) {
                            numbers[num_index++] = atof(num);
                            i = 0;
                            num[0] = '\0';
                        }
                        process_parentheses(numbers, operators, &num_index, &op_index);
                        if (index < 16) {
                            buffer[index++] = key;
                            buffer[index] = '\0';
                            lcd_gotoxy(1, 1);
                            printf(lcd_putc, "%s", buffer);
                        }
                    } else if (key == '=') {
                        if (i > 0) {
                        numbers[num_index++] = strtod(num, NULL); // S? d?ng strtod thay v? atof
                        }
                        double result = calculate_result(numbers, operators, &num_index, &op_index);
                        lcd_putc('\f');
                        printf(lcd_putc, "%.5lf", result); // Hi?n th? chính xác t?i 10 ch? s? th?p phân
                        delay_ms(2000);
                        buffer[0] = '\0';
                        index = 0;
                }
                } else if (mode == 1) { // Trig mode
                    static char func;
                    if (key >= '0' && key <= '9') {
                        if (i < 16) num[i++] = key;
                        if (index < 16) buffer[index++] = key;
                        num[i] = buffer[index] = '\0';
                        lcd_gotoxy(1, 1);
                        printf(lcd_putc, "%s", buffer);
                    } else if (key == '+' || key == '-' || key == '*' || key == '/') {
                        func = (key == '+') ? 's' : (key == '-') ? 'c' : (key == '*') ? 't' : 'o';
                        lcd_putc('\f');
                        printf(lcd_putc, "%c(%s)", func, buffer);
                        display_trig_result(func, buffer);
                        buffer[0] = '\0';
                        index = 0;
                    }
                }
                while (keypad_scan() != 0); // Wait for key release
            }
        }
    }
}
