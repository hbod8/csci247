#include <stdio.h>

void convertBinary(int in, char out[]);
void convertHex(int in, char out[]);
/* Main
* argc, argv   Command line arguments.
* return       zero for success, non-zero for failure
*
* This is the main entry point for the program.  It all starts here. 
*/
int main(int argc, char* argv[]) {
    printf("%s says, \"Hello, World!\"\n", argv[0]);

    char out[33];
    convertBinary(1, out);
    convertHex(1, out);

    puts(out);

    return 0;
}
/* convertBinary
 * in, input number in decimal
 * out, output char array
 */
void convertBinary(int in, char out[]) {
    printf("I'm the convert binary function!\n");
}
/* convertHex
 * in, input number in decimal
 * out, output char array
 */
void convertHex(int in, char out[]) {
    printf("I'm the convert hexadecimal function!\n");
}