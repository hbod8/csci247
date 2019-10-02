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
*/
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage();
    }
    else if ( strcmp("-x", argv[1]) == 0 ) {
        // printf("Ah ha! You want me to convert to hex! Wouldn't it be cool if I could do that?\n");
        int input[100];
        while(scanf("%d", input) != EOF) {
            convertHex(input[0]);
        }
    }
    else if ( strcmp("-b", argv[1]) == 0 ) {
        // printf("Ah ha! You want me to convert to binary! Wouldn't it be cool if I could do that?\n");
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
 * out, output char array
 */
void convertBinary(int in) {
    // printf("I'm the convert binary function!\n");
    // TODO: Figure out how to count the number of binary digits.  Clauson on whiteboard way? or shifts & 1? Probably the later bc its in the rubric.
    char bin[] = {'0', '1'};
    char num[100];
    int i = 0;
    int a = in;
    // printf("should be: %x\n", in);
    while (a > 0) {
        num[i] = bin[(in >> i) & 0x01]; // 00000001 <- SHIFT THIS!
        // printf("%c", bin[(in >> i) & 0x01]);
        i = i + 1;
        a = a / 2;
    }
    while (i > 0) {
        if (i % 4 == 0) {
            printf(" ");
        }
        i = i - 1;
        printf("%c", num[i]);
        // printf("(%x)", num[i]);
    }
    printf("\n");
}
/* convertHex
 * in, input number in decimal
 * out, output char array
 */
void convertHex(int in) {
    // printf("I'm the convert hexadecimal function!\n");
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    char num[100]; // if the digits exceed 100, there be dragons :(
    int i = 0;
    int a = in; // bad things happen if you exceed 2147483647
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
 * Simply prints the usage for the program
 */
void printUsage() {
    printf("Usage: ./convert [-x|-b]\n");
}