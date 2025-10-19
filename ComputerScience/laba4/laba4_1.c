#include <stdio.h>
#include <string.h>

int main(void) {
    char n[100];
    char ans[100];
    int s;
    scanf("%s %d", &n, &s); // Ввод числа и разрядности сетки
    int temp_s = s;
    long long temp_n1 = 0;
    sscanf(n, "%lld", &temp_n1);
    long long temp_n2 = temp_n1 * ((temp_n1 > 0) - (temp_n1 < 0)); // Временные переменные для будущих расчетов
    int len = 0;
    while (temp_n2 != 0 || temp_s > 0) {
        ans[len] = (temp_n2 % 2) + '0'; // Перевод числа в 2сс в заданной сетке
        temp_n2 /= 2;
        temp_s--;
        len++;
    }
    ans[len] = '\0';
    strrev(ans);
    ans[0] = (n[0] == '-') ? '1' : '0'; // Определение 1 бита числа в зависимости от знака
    if ((-((1LL << s - 1) - 1) <= temp_n1) && (temp_n1 <= (1LL << s - 1) - 1)) { // Проверка на то, что число входит в заданную сетку
        printf("%s", ans);
    } else {
        printf("ошибка");
    }    
    return 0;
}