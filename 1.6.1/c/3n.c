#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int is_even(int n)
{
  return (n % 2 == 0);
}

int next_value(int n)
{
  int res = 0;
  
  if (is_even(n)) {
    res = n / 2;
  } else {
    res = (n * 3) + 1;
  }

  //printf("After %d is %d\n", n, res);

  return res;
}

int calc_cycle_length(int n)
{
  int count = 1;
  
  do {
    n = next_value(n);
    count++;
  } while (n != 1);

  return count;
}

int main(void)
{
  int i, j, max, new_max;
  int n;
  
  while(scanf("%d %d", &i, &j) != EOF) {
    max = calc_cycle_length(i);
    n = i;
    while (n++ <= j) {
      new_max = calc_cycle_length(n);
      if (new_max > max) {
        max = new_max;
      }
    }
  
    printf("%d %d %d\n", i, j, max);
  }

  return EXIT_SUCCESS;
}
