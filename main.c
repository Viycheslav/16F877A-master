#include "main.h"

volatile unsigned char flag = 0;

void __interrupt() ISR(void) {
    if (INTCONbits.T0IF) {          // Проверяем флаг TMR0
        INTCONbits.T0IF = 0;        // Сбрасываем флаг
        flag = 1;                   // Поднимаем свой флаг
    }
}

int main(void) {
    TRISB0 = 0;
    PORTB = 0;

    // TMR0: предделитель 1:256
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS  = 0b111;     // 1:256
    INTCONbits.T0IE = 1;            // Разрешаем прерывание TMR0
    INTCONbits.GIE  = 1;            // Глобальное разрешение
    int f=0;
    f=my_func(5);
    while (1) {
        if (flag) {
            flag = 0;
            RB0 = !RB0;              // Инвертируем светодиод
        }
    }

    return 0;
}
