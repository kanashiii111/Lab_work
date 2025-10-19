#include <stdio.h>

int main(void) {
    long long int n; 
    int count = 0;
    scanf("%lld", &n);
    do {
        count += (n % 2 == 0);
        n /= 2;
    } while (n != 0);
    printf("%d", count);
    return 0;
}