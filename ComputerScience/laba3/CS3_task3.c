#include <stdio.h>
#include <string.h>

int main(void) {
    char x[100];
    int x_intPart = 0;
    int x_fracPart = 0;
    int x_fracPartLen= 0;
    int x_intPart_10cc = 0;
    double x_fracPart_10cc = 0;
    char x_intPart_Mcc[100];
    char x_fracPart_Mcc[100];
    char tx_fracPart[100];
    int k,m;
    int flagZero = 0;

    scanf("%s %d %d", &x, &k, &m);

    // Запись нецелой части числа во временную переменную.

    char *pointPos = strchr(x, '.');        
    // Поиск позиции точки во введенной строке.
    strcpy(tx_fracPart, pointPos + 1);      
    // Копирование всего, что идет после точки во временную переменную.
    strrev(tx_fracPart);                    
    // Переворачивание содержимого временной переменной.
    x_fracPartLen = strlen(tx_fracPart);   
    
    // Перевод целой и нецелой части числа из строк в числа.

    sscanf(x, "%d", &x_intPart);
    sscanf(tx_fracPart, "%d", &x_fracPart);

    // Для последующих комментариев используем пример 123.456 8 2

    // Перевод целой части числа X_k.сс в 10сс.

    int pow_buff1 = 0;
    do {
        int powerInt = 1;
        for (int i = 0; i < pow_buff1; i++) {
            powerInt *= k;
        }
        x_intPart_10cc += (x_intPart % 10) * powerInt; 
        // (3 × 8^0) + (2 × 8^1) +(1 × 8^2)
        x_intPart /= 10;                            
        // 123 -> 12 -> 1 -> 0
        pow_buff1++;                                
    } while (x_intPart != 0);

    // Перевод нецелой части числа X_k.сс в 10сс.

    double powerFrac = 1.0;
    while (x_fracPart != 0) {
        for (int j = 0; j < x_fracPartLen; j++) {
            powerFrac /= k;
            x_fracPart_10cc += (x_fracPart % 10) * powerFrac; 
            // (4 × 8^(-1)) + (5 × 8^(-2)) + (6 × 8^(-3))
            x_fracPart /= 10;                              
            // 456 -> 45 -> 4 -> 0                                 
        }                                                  
    }

    // Перевод целой части числа X_k.cc в Mсс.

    int ind1 = 0;
    do {
        x_intPart_Mcc[ind1] = x_intPart_10cc % m + '0'; 
        // 83 % 2 = 1,
        // + '0' для перевода в строку посредством записи ASCII кода числа.
        ind1++; 
        x_intPart_10cc /= m;                            
        // 83 -> 41 -> 20 -> 10 -> 5 -> 2 -> 1 -> 0
    } while (x_intPart_10cc != 0);

    x_intPart_Mcc[ind1] = '\0';
    strrev(x_intPart_Mcc); 
    // Переворачиваем строку с записанными остатками.

    // Перевод нецелой части числа X_k.cc в Mсс.
    
    for (int k = 0; k < x_fracPartLen; k++) {
        x_fracPart_Mcc[k] = (int)(x_fracPart_10cc * m) + '0'; 
        // (int)(0.589 * 2) = 1 и т.д; (int) - для перевода в целочисленный тип             
        x_fracPart_10cc = (x_fracPart_10cc * m) \
        - (int)(x_fracPart_10cc * m); 
        // (0.589 * 2) - 1 = 0.179 и т.д
    }
    x_fracPart_Mcc[x_fracPartLen] = '\0';

    printf("%s.%s", x_intPart_Mcc, x_fracPart_Mcc);
    return 0;
}