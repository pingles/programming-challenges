#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void print_grid(char **grid, int m, int n)
{
  int i, j;
  
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      printf("%c", grid[i][j]);
    }
    printf("\n");
  }
}

void fill_grid(char **grid, int m, int n, char val)
{
  int i, j;
  
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      grid[i][j] = val;
    }
  }
}

char** create_grid(int m, int n)
{
  int i;
  char **grid = calloc(n, sizeof(char*));

  for (i = 0; i < n; i++) {
    grid[i] = calloc(m, sizeof(char*));
  }
  
  return grid;
}

bool in_bounds(int m, int n, int i, int j)
{
  if (i < 0 || j < 0) {
    return false;
  }
  if (i >= n || j >= n) {
    return false;
  }
  return true;
}

void increment_cell(char **grid, int m, int n, int i, int j)
{
  if (in_bounds(m, n, i, j)) {
    if (grid[i][j] != '*') {
      grid[i][j]++;
    }
  }
}

void increment_mine_near(char **grid, int m, int n, int i, int j)
{
  increment_cell(grid, m, n, i, j - 1); // w
  increment_cell(grid, m, n, i, j + 1); // e
  increment_cell(grid, m, n, i - 1, j); // n
  increment_cell(grid, m, n, i + 1, j); // s

  increment_cell(grid, m, n, i + 1, j + 1); // se
  increment_cell(grid, m, n, i - 1, j + 1); // ne
  increment_cell(grid, m, n, i - 1, j - 1); // nw
  increment_cell(grid, m, n, i + 1, j - 1); // sw
}

void draw_mine(char **grid, int m, int n, int i, int j)
{
  grid[i][j] = '*';
  increment_mine_near(grid, m, n, i, j);
}

int main(void)
{
  // m columns
  // n rows
  
  int m, n;
  int i, j;

  scanf("%d %d", &n, &m);

  char **grid = create_grid(m, n);  
  char *line = calloc(n, sizeof(char*));;
  
  for (i = 0; i < n; i++) {
    scanf("%s", line);
    
    for (j = 0; j < m; j++) {
      grid[i][j] = line[j];
    }
  }

  char **output_grid = create_grid(m, n);
  fill_grid(output_grid, m, n, '0');
  
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      if (grid[i][j] == '*') {
        draw_mine(output_grid, m, n, i, j);
      }
    }
  }

  print_grid(output_grid, m, n);
  
  return EXIT_SUCCESS;
}
