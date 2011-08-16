#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define TABLE_SIZE 200000000000

bool is_even(unsigned long n)
{
  return (n % 2 == 0);
}

unsigned long next_value(unsigned long n, unsigned long *table)
{
  if (n < TABLE_SIZE && table[n]) {
    return table[n];
  }

  unsigned long res = 0;
  
  if (is_even(n)) {
    res = n / 2;
  } else {
    res = (n * 3) + 1;
  }

  if (n < TABLE_SIZE) {
    table[n] = res;
  }
  
  return res;
}

unsigned long calc_cycle_length(unsigned long n, unsigned long *table)
{
  unsigned long count = 1;
  
  do {
    n = next_value(n, table);
    count++;
  } while (n != 1);

  return count;
}

int main(void)
{
  unsigned long i, j;
  unsigned long n, max, new_max;
  unsigned long *table = malloc(sizeof(unsigned long) * TABLE_SIZE);

  if (table == NULL) {
    printf("Error: could not allocate memory for lookup table");
    return EXIT_FAILURE;
  }

  memset(table, '\0', sizeof(table));
  
  while(scanf("%lu %lu", &i, &j) != EOF) {
    max = calc_cycle_length(i, table);
    n = i;
    while (n++ <= j) {
      new_max = calc_cycle_length(n, table);
      if (new_max > max) {
        max = new_max;
      }
    }
  
    printf("%lu %lu %lu\n", i, j, max);
  }

  free(table);

  return EXIT_SUCCESS;
}


/* Performance:
   $ time echo '100001 2000000' | ./3n_c 
   100001 2000000 557

   real	0m7.662s
   user	0m7.648s
   sys	0m0.009s
*/
