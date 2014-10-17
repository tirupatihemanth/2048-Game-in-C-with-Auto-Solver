#include <stdio.h>
#include <stdlib.h>
#include "backend.h"
#include <time.h>

//Implementation to print the grid on a console

void grid_print(Grid *grid){

	int i,j;
	for(i=0;i<grid->rows;i++){
		for(j=0;j<grid->cols;j++){
			printf("%d ",grid->array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//Implementation to delete the grid

void grid_delete(Grid *grid){
	int i;
	for(i=0;i<grid->rows;i++){
		free(grid->array[i]);
	}
	free(grid);
}

//Implemenataion of a function to reverse an array

void reverse_array(int *array, int length){
	int i,var;
	for(i=0;i<length/2;i++){
		var = array[i];
		array[i] = array[length-i-1];
		array[length-i-1] = var;
	}
}
//Implementation to create new grid with rows * cols size 

Grid* grid_initialise(int rows, int cols){

	srand(time(NULL));
	int i,j;
	Grid *grid;
	grid = (Grid *) malloc(sizeof(Grid));
	grid->rows = rows;
	grid->cols = cols;
	
	grid->array = (int **) malloc(sizeof(int *)*rows);

	for(i=0;i<rows;i++)
		grid->array[i] = (int *) malloc(sizeof(int)*cols);

	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			grid->array[i][j] = 0;
		}
	}
	new_tile(grid);
	new_tile(grid);
	return grid;
}

//Implementation to reset a grid i.e sets all elements of a grid to 0

void grid_reset(Grid *grid){

	int i,j;
	for(i=0;i<grid->rows;i++){
		for(j=0;j<grid->cols;j++){
			grid->array[i][j] = 0;
		}
	}
	new_tile(grid);
	new_tile(grid);
}

//Implementation to merge an array of given size

int * merge(int *temp, int length){
	sorter(temp, length);
	merger(temp, length);
	return temp;
}

// Implementation of a function to seperate all non zero tiles from zero tiles

int * sorter(int *temp, int length){

	int i,j,var;
	for(i=0;i<length;i++){
		for(j=0;j<length-1;j++){
			if(temp[j]==0){
				var = temp[j];
				temp[j] = temp[j+1];
				temp[j+1] = 0;
			}
		}
	}
	return temp;
}

int * merger(int *temp, int length){

	int i;
	for(i=0;i<length-1;i++){
		if(temp[i] == temp[i+1]){
			temp[i]+=temp[i+1];
			temp[i+1]=0;
		}
	}
	temp = sorter(temp,length);
	return temp;
}

//Implementation to move rows in a particular direction

void move_tiles(Grid *grid, int direction){

	int duplicate_array[grid->rows][grid->cols], i, idx, status = 0, *temp;

	for(i = 0;i<grid->rows;i++){
		for(idx = 0;idx<grid->cols;idx++){
			duplicate_array[i][idx] = grid->array[i][idx];
		}
	}

	if(direction == UP){

		temp = (int *) malloc(sizeof(int)*(grid->rows));
		for(idx = 0; idx<grid->cols;idx++){
			for(i = 0; i<grid->rows;i++){
				temp[i] = grid->array[i][idx];
			}

			merge(temp, grid->rows);
			for(i=0;i<grid->rows;i++){
				grid->array[i][idx] = temp[i];

			}
		}
		free(temp);

	}
	else if(direction == DOWN){

		temp = (int *) malloc(sizeof(int)*(grid->rows));

		for(idx = 0;idx<grid->cols;idx++){

			for(i=0;i<grid->rows;i++){
				temp[i] = grid->array[i][idx];
			}

			reverse_array(temp, grid->rows);
			merge(temp, grid->rows);
			reverse_array(temp, grid->rows);
			for(i=0;i<grid->rows;i++){
				grid->array[i][idx] = temp[i];
			}
		}
		free(temp);

	}
	else if(direction == LEFT){

		temp = (int *) malloc(sizeof(int)*(grid->cols));
		for(idx = 0;idx<grid->rows;idx++){
			for(i=0;i<grid->cols;i++){
				temp[i] = grid->array[idx][i];
			}
			merge(temp, grid->cols);
			for(i=0;i<grid->cols;i++){
				grid->array[idx][i] = temp[i];
			}
		}
		free(temp);
	}
	else if(direction == RIGHT){

		temp = (int *)malloc(sizeof(int)*(grid->cols));
		for(idx = 0;idx<grid->rows;idx++){
			for(i=0;i<grid->cols;i++){
				temp[i] = grid->array[idx][i];
			}
			reverse_array(temp, grid->cols);
			merge(temp, grid->cols);
			reverse_array(temp, grid->cols);
			for(i=0;i<grid->cols;i++){
				grid->array[idx][i] = temp[i];
			}
		}
		free(temp);
	}

	for(i = 0;i<grid->rows;i++){
		for(idx = 0;idx<grid->cols;idx++){
			if(duplicate_array[i][idx] != grid->array[i][idx]){
				status = 1;
				new_tile(grid);
				break;
			}
		}

		if(status == 1)
			break;
	}

}

//Get No. of rows in the grid

int get_grid_rows(Grid *grid){

	return grid->rows;

}

// Get No. of columns in the grid

int get_grid_cols(Grid *grid){

	return grid->cols;

}

//creating a new tile in the empty space in the grid with 90% probablility of getting 2 and 10% probability of getting four

void new_tile(Grid *grid){

	int row,col,list[] = {2,2,2,2,2,2,2,2,2,4};

	while(1){
		row = rand()%(grid->rows);
		col = rand()%(grid->cols);
		if(grid->array[row][col]==0){
			grid->array[row][col] = list[rand()%10];
			break;
		}
	}

}

//sets the value of a particular grid to the specified "value"

void set_tile(Grid *grid, int rowidx, int colidx, int value){

	grid->array[rowidx][colidx] = value;

}

//Return the value of the tile at the position (row, column)

int get_tile(Grid *grid, int rowidx, int colidx){

	return grid->array[rowidx][colidx];

}