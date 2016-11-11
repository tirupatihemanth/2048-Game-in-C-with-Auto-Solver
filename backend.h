#ifndef BACKEND_H
#define BACKEND_H

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

typedef struct Grid_{

	int rows,cols;
	int **array;
	int score;
	int heuristicscore;
} Grid;

//Definition of grid_print function

void grid_print(Grid *);

//Definition for initialising a grid

Grid* grid_initialise(int, int);

//Definiton for duplicationg a grid

Grid * grid_duplicate(Grid *);

//Definition for resetting a grid

void grid_reset( Grid *);

// Definition to merge an array given 


int merge(int *, int);

// Helper function for merge function


int merger(int *, int);

// Helper function for merge function


int * sorter(int *, int);

//Definiton to move the grid when a particular arrow is pressed

void move_tiles(Grid *, int, int);

// Definiton to get the no. of rows in the grid useful for gui

int get_grid_rows(Grid *);

// Definition to get the no. of columns in the grid useful for gui

int get_grid_cols(Grid *);

//Definiton to create a new tile with 90% probability of getting a 2 and 10% probability of getting a 4

int new_tile(Grid *);

// Sets a given tile with a particular value

void set_tile(Grid *, int ,int, int);

// returns a the value of a particular tile in the grid

int get_tile(Grid *, int, int);





#endif