#include <stdio.h>
#include <string.h>

int main(void) {
    int s;
    char n[100];
    scanf("%s %d", &n, &s); // Ввод числа и разрядности сетки
    int temp_n;
    int temp1_n;
    sscanf(n, "%d", &temp_n);
    sscanf(n, "%d", &temp1_n); // Создание временных переменных для будущих операций
    int temp_s = s;
    char ans[100];
    int len = 0;
    while (temp_n != 0 || temp_s > 0) { // Перевод числа в 2сс в нужной сетке
        ans[len] = (temp_n % 2) + '0';
        temp_n /= 2;
        temp_s--;
        len++;
    }
    ans[len] = '\0';
    strrev(ans);
    if ((temp1_n <= (1LL << s) - 1) && (n[0] != '-')) { // Проверка на то, что число не превышает разрядность сетки и оно не отрицательное
        printf("%s", ans);
    } else {
        printf("ошибка");
    }
    return 0;
}
