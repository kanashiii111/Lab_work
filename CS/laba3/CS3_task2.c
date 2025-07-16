#include <stdio.h>

int main(void) {
    int n, pos;
    int ans = 0;
    scanf("%d %d", &n, &pos);
    int i = 0;
    do {
        ans = (i == pos) ? n % 2 : ans;
        i++;
        n /= 2;
    } while (n != 0);
    printf("%d", ans);
    return 0;
}