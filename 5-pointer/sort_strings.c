#include <stdio.h>
#include <string.h>
#include "sort.h"
#include <stdlib.h>

/* Test data.
 * These strings should be sorted in increasing (a..z) order.  
 *
 * As an aside, what do all of these strings have in common.  (hint: how would
 * you pronounce them?)
 */
unsigned data_size = 8;
const char* data[8] = {
  "german",
  "ares",
  "lima",
  "reading",
  "rodeo",
  "job",
  "polish",
  "differently"
    };

/* Test program
 *
 * This program tests sort_array with an array of strings.  Or rather, an array
 * of pointers to variable length arrays of characters terminated by null.
 */
int main() {
  int i;
  int status = EXIT_SUCCESS;

  sort_array((void**)data, data_size);

  for(i = 0; i < data_size - 1; ++i) {
    if (strcmp (data[i], data[i+1]) >= 0)  {
      fprintf(stderr, 
	      "\"%s\" and \"%s\" are out of order\n", 
	      data[i], 
	      data[i+1]);
      status = EXIT_FAILURE;
    }
  }

  return status;
}

