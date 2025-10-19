#include <stdio.h>
#include <string.h>

int main(void) {
    char num[100];
    char sign[3];
    int n,m;

    scanf("%s %d %d", &num, &n, &m);

    // sign bit

    sign[0] = (num[0] == '-') ? '1' : '0';
    sign[1] = '\0';

    // pure binary

    double temp_num = 0;
    sscanf(num, "%lf", &temp_num);

    long long numDec = 0;
    double numFrac = 0.0;
    char numFracStr[100];
    
    char *PointPos = strchr(num, '.');
    if (PointPos != NULL) {
        strcpy(numFracStr, PointPos + 1);
        strrev(numFracStr);
    } else {
        strcpy(numFracStr, "");
    }
    sscanf(num,"%lld", &numDec);
    long long numDecAbs = 0;
    numDecAbs = numDec * ((numDec > 0) - (numDec < 0));
    double tempNumAbs = 0.0;
    tempNumAbs = temp_num * ((temp_num > 0) - (temp_num < 0));

    numFrac = tempNumAbs - (int)(tempNumAbs);

    char numPureBinary[250];
    int i = 0;
    do {
        numPureBinary[i] = (numDecAbs % 2 == 0) ? '0' : '1';
        numDecAbs /= 2;
        i++;
    } while (numDecAbs != 0);
    numPureBinary[i] = '\0';
    strrev(numPureBinary);

    char nMan[250];
    strcpy(nMan, numPureBinary);

    numPureBinary[i] = '.';

    int j = i + 1;
    int temp_m = 0;
    temp_m = m;
    do {
        int bit = (int)(numFrac * 2);
        numPureBinary[j] = bit + '0';
        nMan[j - 1] = bit + '0';
        numFrac = (numFrac * 2) - bit;
        j++;
        temp_m--;
    } while (temp_m >= 0);
    numPureBinary[j] = '\0';
    nMan[j - 1] = '\0';

    // normalasing the mantissa and unbiased exp
                                                 
    int BinaryPointPos = -1;
    int BinaryOnePos = -1;
    int flag = 1;

    for (int k = 0; k < strlen(numPureBinary); k++) {
        BinaryOnePos = (numPureBinary[k] == '1' && flag == 1) ? k : BinaryOnePos;
        BinaryPointPos = (numPureBinary[k] == '.') ? k : BinaryPointPos;
        flag = (BinaryOnePos == -1) ? 1 : 0; 
    }

    int unbiasedExp = 0;
    if (BinaryPointPos > BinaryOnePos) {
        unbiasedExp = (BinaryPointPos - 1);
    } else {
        unbiasedExp = -(BinaryOnePos - BinaryPointPos);
    }

    // determening biased exponent

    int bias = 0;
    bias = (1 << (n - m - 2)) - 1;

    int biasedExp = 0;
    biasedExp = unbiasedExp + bias;

    char BinaryBiasedExp[100];
    for (int i = (n - m - 2); i >= 0; i--) {
        BinaryBiasedExp[i] = (biasedExp % 2 == 0) ? '0' : '1';
        biasedExp /= 2;
    }
    BinaryBiasedExp[n - m - 1] = '\0';

    char mantissa[250];
    char *nMantissaFOP = strchr(nMan, '1');
    if (nMantissaFOP == NULL) {
        memset(mantissa, '0', m);
        mantissa[m] = '\0';
    } else {
        strncpy(mantissa, nMantissaFOP + 1, m + 1);
        if (strlen(mantissa) < m) {
            for (int mn = m - BinaryOnePos + 1; mn < m; mn++) {
                mantissa[mn] = '0';
            }
        }
        mantissa[m] = '\0';
    }

    if (temp_num == 0.0) {
        memset(BinaryBiasedExp, '0', n - m - 1);
    }

    printf("%s %s %s\n", sign, BinaryBiasedExp, mantissa);

    return 0;
}
