#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main() {
    FILE* file = fopen("./../data.bin", "wb");
    if (file == NULL) return 1;

    printf("\n\nWRITE\n\n");

    const char* a = "0";
    const char* b = "101";
    const char* c = "100";

    const char* combined = "000000101101101100100100000001011001001010001000";

    for (int i = 0; i < strlen(combined); i+=8) {
        char part[9];
        strncpy(part, combined + i, 8);
        part[8] = '\0';

        unsigned char number = strtol(part, NULL, 2);

        printf("%s: %d\n", part, number);
        fputc(number, file);
    }

    // $: xxd -b data.bin
    // 00000000: 00000010 11011011 00100100 00000101 10010010 10001000  ..$...

    fclose(file);

    printf("\n\nREAD\n\n");

    file = fopen("./../data.bin", "rb");
    if (file == NULL) return 1;

    // Trzeba zapisać w nagłówku ile będzie liczb po 8 bitów
    for (int i = 0; i < 6; i++) {
        unsigned char number;
        fread(&number, sizeof(unsigned char), 1, file);

        for (int bit = 8; bit; --bit) {  // count from 8 to 1
            putchar(number & (1 << (bit - 1)) ? '1' : '0');
        }

        printf(": %d\n", number);
    }

    fclose(file);
    return 0;
}
