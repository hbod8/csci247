/* Ah, the game of life.  This is a cellular automation simulator.  The rules
 * are very simple.  The board is a grid.  Each grid square can hold at most one
 * cell.  For a cell to survive from generation to generation it needs two or
 * three neighbors.  Too many neighbors causes the cell to starve.  Too few
 * causes an incurable case of ennui.  All is not lost.  If a grid square has
 * exactly three neighbors, a new cell is born, which is kind of strange when
 * you think about it.
 *
 * There are lots of variations on this game.  Technically, this is Conway's
 * Game of Life and is a B3/S23 game.  That is, cells survive with two or three
 * neighbors and are born with exactly 3 neighbors.  This game can also be
 * extended into the real domain or more diminutions.  We, however, with stick
 * with Conway's original automation.
 *
 * Below is a very simple implementation.  This is your chance to apply some of
 * the loop optimization techniques we've been talking about in class: 
 *  1) Remove loop inefficiencies
 *  2) Reduce procedure calls
 *  3) Reduce unnecessary memory references
 *  4) Loop unrolling
 * There are, of course, more optimizations that you can apply.  For example,
 * moving sequentially through memory is more efficient than jumping around.
 * We'll see why in Chapter 9.  

 * C stores 2D arrays Column Major Order.  That is to say that cell
 * A[0][WIDTH-1] is right next to A[1][0] in memory.  If you notice the nested
 * loops in evolve (below) I'm incrementing the column index, i, more quickly
 * than the row index, j.  Try reversing these and see what happens.
 *
 * The experimental set-up is implemented in a library called liblife.a  Since
 * it has solutions, I'm providing it as a binary in my home directory:
 *   /home/clausoa/lib/liblife.a
 * The provided make files already links in this library.
 *
 * There are two ways to run the test program: with our without a window.
 * Without a window, the program runs the test cases against the provided
 * evolution methods as quickly as possible.  After about 100 generations, it
 * stops and reports the average performance of each method.  
 *
 * If you favor something a little more animated, and I know you do, run it test
 * program with windowing.  This is the default.  This is basically the same
 * set-up, but it displays the current generation and the relative performance
 * of the provided methods.  The scores are jumpy for a little while, but they
 * eventually calm down.  When you close the window, the final scores are
 * displayed on the console.  
 *
 * See how fast you can make your code.
 *
 * I have one final piece of advice.  You are free to add as many test methods
 * as you want.  I would encourage you to do this.  Copy the code, give it a new
 * name, and add it to the library's suite of methods.  This way you can really
 * see if you are making improvements.  Have fun.
 *
 */

#include "liblife.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/* Simple Life evolution.  This function, and this tree support functions,
 * implement Conway's game of life rules.  Your millage may vary, void where
 * prohibited. 
 */

static int min(int x, int y) {
   return x < y ? x : y;
}
static int max(int x, int y) {
   return x < y ? y : x;
}

/* All Neighbors
 * Given the board and cell position, calculate all the neighbors using one formula.
 * 
 * NOTE: Only works if the cell is a non-side cell.
 */
int allNeighbors(board b, int i, int j) {
   return b[i + 1][j] + b[i - 1][j] + b[i][j + 1] + b[i][j - 1] + b[i + 1][j + 1] + b[i - 1][j + 1] + b[i + 1][j - 1] + b[i - 1][j - 1];
}

/* Out of bounds
 * Given the cell position, returns true if any neighbor will be out of bounds.
 */
int outOfBounds(int i, int j) {
   return (j - 1 < 0) || (i - 1 < 0) || (j + 1 >= HEIGHT) || (i + 1 >= WIDTH);
}

/* Neighbors
 * Given the board b, this function counts the number of neighbors of 
 * cell-(i,j).
 *
 * This implementation over-counts the neighborhood.  The loop counts the
 * cell-(i,j) and then subtracts off one if it is alive. 
 *
 * The use of min and max ensure that the neighborhood is truncated at the edges
 * of the board.  
 * 
 * Additionally, if the given cell is not an edge cell, use allNeighbors()
 */
static int neighbors (board b, int i, int j)
{
   if (!outOfBounds(i, j)) {
      return allNeighbors(b, i, j);
   }
   int n = 0;
   int i_left = max(0,i-1);
   int i_right  = min(HEIGHT, i+2);
   int j_left = max(0,j-1);
   int j_right  = min(WIDTH, j+2);
   int ii, jj;

   for (ii = i_left; ii < i_right; ++ii) {
      for (jj = j_left; jj < j_right; jj += 2) {
         n += b[ii][jj];
         n += b[ii][jj + 1];
      }
      if (jj - j_right > 0) {
         n += b[ii][jj];
      }
   }

   return n - b[i][j];


}

/* Evolve
 * This is a very simple evolution function.  It applies the rules of Conway's
 * Game of Live as written.  There are a lot of improvements that you can make.
 * Good luck beating Ada, she is really good.
 */
void evolve(board prv, board nxt)
{
   int i, j;
   int n;

   for (i = 0; i < WIDTH; ++i) {
      for (j = 0; j < HEIGHT; ++j) {
         n = neighbors(prv, i ,j);
         nxt[i][j] = (prv[i][j] && (n == 3 || n == 2)) || (!prv[i][j] && (n == 3));
      }
   }
}

/* The program takes one optional arugment: -nw.  This tells the program to skip
 * the GUI components.  The non-GUI form is much more stable and what we will
 * use to measure your code's performance.  
 */
int main(int argc, char* argv[])
{
   if(argc > 2 || (argc == 2 && 0 != strcmp (argv[1], "-nw"))) {
      fprintf(stderr, "Usage: %s [-nw]\n\t-nw  No window\n", argv[0]);
      return EXIT_FAILURE;
   }
   else {
     add_method("Simple", &evolve);
     run_game(argc == 2 && 0 == strcmp (argv[1], "-nw"));
   }
              
   return 0;
}



