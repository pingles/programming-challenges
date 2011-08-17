#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
  int columns;
  int rows;
  char **grid;
} matrix_t;

void print_grid(matrix_t *grid)
{
  int i, j;
  
  for (i = 0; i < grid->rows; i++) {
    for (j = 0; j < grid->columns; j++) {
      printf("%c", grid->grid[i][j]);
    }
    printf("\n");
  }
}

void fill_grid(matrix_t *grid, char val)
{
  int i, j;
  
  for (i = 0; i < grid->rows; i++) {
    for (j = 0; j < grid->columns; j++) {
      grid->grid[i][j] = val;
    }
  }
}

matrix_t* create_grid(int m, int n)
{
  int i;
  char **grid = calloc(n, sizeof(char*));

  for (i = 0; i < n; i++) {
    grid[i] = calloc(m, sizeof(char*));
  }

  matrix_t *g = malloc(sizeof(matrix_t));
  g->columns = m;
  g->rows = n;
  g->grid = grid;
  
  return g;
}

bool in_bounds(matrix_t *grid, int i, int j)
{
  if (i < 0 || j < 0) {
    return false;
  }
  if (i >= grid->rows || j >= grid->columns) {
    return false;
  }
  return true;
}

void increment_cell(matrix_t *grid, int i, int j)
{
  if (in_bounds(grid, i, j)) {
    if (grid->grid[i][j] != '*') {
      grid->grid[i][j]++;
    }
  }
}

void increment_mine_near(matrix_t *grid, int i, int j)
{
  increment_cell(grid, i, j - 1); // w
  increment_cell(grid, i, j + 1); // e
  increment_cell(grid, i - 1, j); // n
  increment_cell(grid, i + 1, j); // s

  increment_cell(grid, i + 1, j + 1); // se
  increment_cell(grid, i - 1, j + 1); // ne
  increment_cell(grid, i - 1, j - 1); // nw
  increment_cell(grid, i + 1, j - 1); // sw
}

void draw_mine(matrix_t *grid, int i, int j)
{
  grid->grid[i][j] = '*';
  increment_mine_near(grid, i, j);
}

void free_grid(matrix_t *grid)
{
  int i;
  for (i = 0; i < grid->rows; i++) {
    free(grid->grid[i]);
  }
  free(grid->grid);
  free(grid);
}

int main(void)
{
  // m columns
  // n rows
  
  int m, n;
  int i, j;

  scanf("%d %d", &n, &m);

  matrix_t *input_grid = create_grid(m, n);
  char *line = calloc(n, sizeof(char*));;
  
  for (i = 0; i < n; i++) {
    scanf("%s", line);
    
    for (j = 0; j < m; j++) {
      input_grid->grid[i][j] = line[j];
    }
  }

  matrix_t *output_grid = create_grid(m, n);
  fill_grid(output_grid, '0');
  
  for (i = 0; i < output_grid->rows; i++) {
    for (j = 0; j < output_grid->columns; j++) {
      if (input_grid->grid[i][j] == '*') {
        draw_mine(output_grid, i, j);
      }
    }
  }

  print_grid(output_grid);

  free_grid(input_grid);
  free_grid(output_grid);
  
  return EXIT_SUCCESS;
}
