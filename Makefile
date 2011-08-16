all: 3n_c minesweeper

3n_c: 1.6.1/c/3n.c
	gcc 1.6.1/c/3n.c -o 3n_c -Wall

minesweeper: 1.6.2/c/minesweeper.c
	gcc 1.6.2/c/minesweeper.c -o minesweeper -Wall
