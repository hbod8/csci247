#include <stdio.h>
#include <string.h>

void convertBinary(int in);
void convertHex(int in);
void printUsage();
/* Main
 * argc, argv   Command line arguments.
 * return       zero for success, non-zero for failure
 *
 * This is the main entry point for the program.  It all starts here.
 * The main use of this function is to prcess command-line input and keyboard input while keyboard input is not the end of file character.
 * -b -> binary converter
 * -x -> hexadecimal converter
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage();
    }
    else if ( strcmp("-x", argv[1]) == 0 ) {
        int input[100];
        while(scanf("%d", input) != EOF) {
            convertHex(input[0]);
        }
    }
    else if ( strcmp("-b", argv[1]) == 0 ) {
        int input[100];
        while(scanf("%d", input) != EOF) {
            convertBinary(input[0]);
        }
    }
    else {
        printUsage();
    }

    return 0;
}
/* convertBinary
 * in, input number in decimal
 * Converts user specified decimal number to a binary number, with spaces every nibble, and prints result to command-line.
 * It places every binary digit in an array to ensure the result is little endian. (could be more efficient if you read the largest bit then trim zeros)
 */
void convertBinary(int in) {
    char bin[] = {'0', '1'};
    char num[100];
    int i = 0;
    int a = in;
    while (a > 0) {
        num[i] = bin[(in >> i) & 0x01]; // 00000001
        i = i + 1;
        a = a / 2;
    }
    while (i > 0) {
        if (i % 4 == 0) {
            printf(" ");
        }
        i = i - 1;
        printf("%c", num[i]);
    }
    printf("\n");
}
/* convertHex
 * in, input number in decimal
 * Converts specified decimal number to hexadeimal number, and prints result to command line.
 * Doesnt print anything if the number is larger than the max int size of 2147483647.
 */
void convertHex(int in) {
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    char num[100];
    int i = 0;
    int a = in;
    printf("0x");
    while (a > 0) {
        num[i/4] = hex[(in >> i) & 0x0f]; // 00001111
        i = i + 4;
        a = a / 16;
    }
    while (i > 0) {
        i = i - 4;
        printf("%c,", num[i/4]);
    }
    printf("\n");
}
/* printUage
 * Simply prints the usage for the program in command line
 */
void printUsage() {
    printf("Usage: ./convert [-x|-b]\n");
}