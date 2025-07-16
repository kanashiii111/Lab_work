#include <stdio.h>
#include <string.h>

void output(int n, int size) {
    for (int j = 0; j < n; j++) {
        int tSize = size;
        int tj = j;
        int bits[size];
        int index = 0;
        do {
            bits[index++] = (tj % 2 == 0) ? 0 : 1;
            tj /= 2;
            tSize--;
        } while(tj != 0 || tSize != 0);

        for (int k = index - 1; k >= 0; k--) {
            printf("%d", bits[k]);
        }
        printf(" ");
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    int size;
    for (int i = 1; i <= n; i++) {
        if (n <= (1 << i)) {
            size = i;
            break;
        }
    }
    output(n, size);
    return 0;
}