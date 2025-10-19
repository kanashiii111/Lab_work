#include <stdio.h>
#include <string.h>

int main(void) {
    char n[100];
    char ans[100];
    int s;
    scanf("%s %d", &n, &s);
    int temp_s = s;
    long long temp_n1 = 0;
    sscanf(n, "%lld", &temp_n1);
    long long temp_n2 = temp_n1 * ((temp_n1 > 0) - (temp_n1 < 0));
    int len = 0;
    while (temp_n2 != 0 || temp_s > 0) {
        ans[len] = (n[0] == '-') ? ((temp_n2 + 1) % 2) + '0' : ((temp_n2) % 2) + '0'; // Инверсия бит если число < 0
        temp_n2 /= 2;
        temp_s--;
        len++;
    }
    ans[len] = '\0';
    strrev(ans);
    if (n[0] == '-') {
        int carry = 1;
        for (int i = len - 1; i >= 0 ; i--) { // Прибавление 1 к битам, если число отрицательное
            if (ans[i] == '1' && carry == 1) {
                ans[i] = '0';
            } else if (ans[i] == '0' && carry == 1) {
                ans[i] = '1';
                carry = 0;
            }
        }
    }
    if ((-(1LL << s - 1) <= temp_n1) && (temp_n1 <= (1LL << s - 1) - 1)) { // Проверка на то, входит ли число в сетку
        printf("%s", ans);
    } else {
        printf("ошибка");
    }    
    return 0;
}