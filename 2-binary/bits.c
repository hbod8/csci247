/* 
 * CS:APP Data Lab 
 * 
 * Harry Saliba
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  /* brief description of how your implementation works */
  int Funct(arg1, arg2, ...) {
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   *
   * exploit ability of shifts to compute powers of 2
   */
  int pow2plus1(int x) {
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   *
   * exploit ability of shifts to compute powers of 2 
   */
  int pow2plus4(int x) {
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 * 
 * bayes theorem
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 * 
 *  Step1: (n << 3), shift n left 3 to multiply by 8.
 *  Step2: x >> (n << 3), shift x to the correct byte position such that the byte we want is in the least significant position.
 *  step3: (x >> (n << 3)) & 0xff, clip any undesired bytes by only selecting the last byte.
 */
int getByte(int x, int n) {
  return (x >> (n << 3)) & 0xff;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 * 
 *  By first arithmetically shifting the bytes then removing the repeated bit with a mask logical shift can be achived.
 */
int logicalShift(int x, int n) {
  unsigned int mask = 0xffffffff;
  return ((x >> n) & (mask >> n));
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 * 
 *  shift every place into the first and add to y, y = bit count
 *  @TODO reduce ops
 */
int bitCount(unsigned int x) {
  int y = 0;
  y += (x & 0x80000000) >> 31;
  y += (x & 0x40000000) >> 30;
  y += (x & 0x20000000) >> 29;
  y += (x & 0x10000000) >> 28;

  y += (x & 0x08000000) >> 27;
  y += (x & 0x04000000) >> 26;
  y += (x & 0x02000000) >> 25;
  y += (x & 0x01000000) >> 24;

  y += (x & 0x00800000) >> 23;
  y += (x & 0x00400000) >> 22;
  y += (x & 0x00200000) >> 21;
  y += (x & 0x00100000) >> 20;

  y += (x & 0x00080000) >> 19;
  y += (x & 0x00040000) >> 18;
  y += (x & 0x00020000) >> 17;
  y += (x & 0x00010000) >> 16;

  y += (x & 0x00008000) >> 15;
  y += (x & 0x00004000) >> 14;
  y += (x & 0x00002000) >> 13;
  y += (x & 0x00001000) >> 12;
  
  y += (x & 0x00000800) >> 11;
  y += (x & 0x00000400) >> 10;
  y += (x & 0x00000200) >> 9;
  y += (x & 0x00000100) >> 8;

  y += (x & 0x00000080) >> 7;
  y += (x & 0x00000040) >> 6;
  y += (x & 0x00000020) >> 5;
  y += (x & 0x00000010) >> 4;

  y += (x & 0x00000008) >> 3;
  y += (x & 0x00000004) >> 2;
  y += (x & 0x00000002) >> 1;
  y += (x & 0x00000001);
  return y;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 * 
 *  Twos complement of x, combined with x, sign only, add one
 */
int bang(int x) {
  int bits = ((~x + 1) | x) >> 31;
  return bits + 1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 0x80000000;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 * 
 *   First, see how much data will be held in n
 *    Then, reomve bits of n
 */
int fitsBits(int x, int n) {
  int space = 32 + (~n + 1);
  return !(x ^ ((x << space) >> space));
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward result
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 * 
 *  @TODO
 */
int divpwr2(int x, int n) {
  // / rounds to result
  return (x >> n) + (~(~x & 0x80000000) >> 31);
  // return x >> n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 * 
 *  Two's complement
 */
int negate(int x) {
  return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 * 
 *  move the signed bit to the ones place
 */
int isPositive(unsigned int x) {
  return !((x & 0x80000000) >> 31 | !x);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 * 
 *  first, check signed bit
 *  then, if opposite signs then you know if true
 *  and, find difference.
 */
int isLessOrEqual(int x, int y) {
  int signedBit = !(x >> 31) ^ !(y >> 31);
  int opposite = signedBit & (x >> 31);
  int difference = !signedBit & !((y + (~x + 1)) >> 31);
  return opposite | difference;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 * 
 *  For each case where the most significant bit is greater than a power of two, make the result larger.
 * 
 *  @TODO this seems very crude if/else
 */
int ilog2(int x) {
  unsigned int result = 0, a;
  a = ((~((x >> 16) + 0xffffffff)) >> 27) & 0x10;
  result |= a, x = x >> a;
  a = ((~((x >>  8) + 0xffffffff)) >> 28) &  0x8;
  result |= a, x = x >> a;
  a = ((~((x >>  4) + 0xffffffff)) >> 29) &  0x4;
  result |= a, x = x >> a;
  a = ((~((x >>  2) + 0xffffffff)) >> 30) &  0x2;
  result |= a, x = x >> a;
  return (result | (x >> 1));
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  // printf("%x\n", uf);
  // int sign = uf >> 31;
  // int expAndMan = uf & 0X7fffffff;
  // printf("sign:%x\n", ((~sign & 1) << 31));
  // printf("%x\n", expAndMan);
  // printf("res:%x\n\n", ((~sign & 1) << 31) ^ expAndMan);
  // return ((~sign & 1) << 31) ^ expAndMan;
  return 2;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  int sign = (uf >> 31) << 31;
  int exp = (uf & 0x7f800000);
  int man = (uf & 0x007);
  int doubleMan = (man << 1); //loosy
  return (sign | exp) | doubleMan;
}
