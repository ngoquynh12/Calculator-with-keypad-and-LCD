#ifndef KEYPAD_H
#define KEYPAD_H

// Ð?nh ngh?a các hàng c?a bàn phím
#define row_1 input(PIN_B0)
#define row_2 input(PIN_B1)
#define row_3 input(PIN_B2)
#define row_4 input(PIN_B3)
#define row_5 input(PIN_B4)

// Ð?nh ngh?a các c?t c?a bàn phím
#define col_1 PIN_D0
#define col_2 PIN_D1
#define col_3 PIN_D2
#define col_4 PIN_D3

// B?ng ánh x? các k? t? c?a bàn phím
char keypad[5][4] = {
    {'+', '-', '*', '/'},      // Hàng ð?u tiên ch?a các toán t?
    {'1', '2', '3', 'A'},      // Hàng 2 ch?a các s? và k? t?
    {'4', '5', '6', '.'},      
    {'7', '8', '9', 'C'},      
    {'(', '0', ')', '='}       // Hàng cu?i cùng: thêm d?u `=` vào c?t 3
};

// Hàm kh?i t?o bàn phím
void keypad_init(void) {
    output_bit(col_1, 1);
    output_bit(col_2, 1);
    output_bit(col_3, 1);
    output_bit(col_4, 1);
}

// Hàm ki?m tra xem có phím nào ðý?c nh?n không
int1 keypad_press(void) {
    // T?t t?t c? các c?t
    output_bit(col_1, 0);
    output_bit(col_2, 0);
    output_bit(col_3, 0);
    output_bit(col_4, 0);

    // Ki?m tra xem có hàng nào ðý?c kích ho?t (phím nh?n)
    if (row_1 == 0 || row_2 == 0 || row_3 == 0 || row_4 == 0 || row_5 == 0) {
        return 1;
    }
    return 0;
}

// Hàm kích ho?t c?t c? th?
void keypad_check(char tencot) {
    // B?t t?t c? các c?t
    output_bit(col_1, 1);
    output_bit(col_2, 1);
    output_bit(col_3, 1);
    output_bit(col_4, 1);

    // T?t c?t ðý?c ch?n
    switch (tencot) {
        case 1: output_bit(col_1, 0); break;
        case 2: output_bit(col_2, 0); break;
        case 3: output_bit(col_3, 0); break;
        case 4: output_bit(col_4, 0); break;
    }
}

// Hàm quét phím và tr? v? k? t? nh?n
char keypad_scan(void) {
    char tencot;

    // Ki?m tra n?u có phím ðý?c nh?n
    if (keypad_press()) {
        delay_ms(50);  // Ch?ng d?i phím
        if (keypad_press()) {  // Ki?m tra l?i phím nh?n
            for (tencot = 0; tencot < 4; tencot++) {
                // Kích ho?t t?ng c?t m?t
                keypad_check(tencot + 1);

                // Ki?m tra t?ng hàng
                if (row_1 == 0) return keypad[0][tencot];
                if (row_2 == 0) return keypad[1][tencot];
                if (row_3 == 0) return keypad[2][tencot];
                if (row_4 == 0) return keypad[3][tencot];
                if (row_5 == 0) return keypad[4][tencot];
            }
        }
    }
    return 0;  // Không có phím nào ðý?c nh?n
}

#endif

