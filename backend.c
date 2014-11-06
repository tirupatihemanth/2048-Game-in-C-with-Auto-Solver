/*
gcc `pkg-config gtk+-2.0 --cflags` -g frontend_2048.c 2048_AI.c backend.c `pkg-config gtk+-2.0 --libs`

This is the command one must type on linux terminal with gtk library already installed in it

*/

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
	printf("heuristicscore: %d\n",grid->heuristicscore);
	printf("score: %d\n",grid->score);
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
	grid->score = 0;
	grid->heuristicscore = 0;
	new_tile(grid);
	new_tile(grid);
	return grid;
}

//Implementation of a function to duplicate a grid given

Grid * grid_duplicate(Grid *grid){

	int i,j;
	Grid *duplicate_grid;
	duplicate_grid = (Grid *) malloc(sizeof(Grid));
	duplicate_grid->rows = grid->rows;
	duplicate_grid->cols = grid->cols;
	
	duplicate_grid->array = (int **) malloc(sizeof(int *)*grid->rows);

	for(i=0;i<grid->rows;i++)
		duplicate_grid->array[i] = (int *) malloc(sizeof(int)*grid->cols);

	for(i=0;i<grid->rows;i++){
		for(j=0;j<grid->cols;j++){
			duplicate_grid->array[i][j] = grid->array[i][j];
		}
	}
	duplicate_grid->score = grid->score;
	duplicate_grid->heuristicscore = grid->heuristicscore;
	return duplicate_grid;
}

//Implementation to reset a grid i.e sets all elements of a grid to 0

void grid_reset(Grid *grid){

	int i,j;
	for(i=0;i<grid->rows;i++){
		for(j=0;j<grid->cols;j++){
			grid->array[i][j] = 0;
		}
	}
	grid->score = 0;
	grid->heuristicscore = 0;
	new_tile(grid);
	new_tile(grid);
}

//Implementation to merge an array of given size

int merge(int *temp, int length){
	int score;
	sorter(temp, length);
	score = merger(temp, length);
	return score;
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

int merger(int *temp, int length){

	int i,score = 0;
	for(i=0;i<length-1;i++){
		if(temp[i] == temp[i+1]){
			score+=2*temp[i];
			temp[i]+=temp[i+1];
			temp[i+1]=0;
		}
	}
	temp = sorter(temp,length);
	return score;
}

//Implementation to move rows in a particular direction

void move_tiles(Grid *grid, int direction, int addtile){

	int  i, idx, status = 0, *temp;
	int **duplicate;
	duplicate = (int **) malloc(sizeof(int *)*grid->rows);

	for(i=0;i<grid->rows;i++)
		duplicate[i] = (int *) malloc(sizeof(int)*grid->cols);

	for(i = 0;i<grid->rows;i++){
		for(idx = 0;idx<grid->cols;idx++){
			duplicate[i][idx] = grid->array[i][idx];
		}
	}

	if(direction == UP){

		temp = (int *) malloc(sizeof(int)*(grid->rows));
		for(idx = 0; idx<grid->cols;idx++){
			for(i = 0; i<grid->rows;i++){
				temp[i] = grid->array[i][idx];
			}

			grid->score+=merge(temp, grid->rows);
			//printf("grid->score: %d\n",grid->score);
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
			grid->score+=merge(temp, grid->rows);
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
			grid->score+=merge(temp, grid->cols);
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
			grid->score+=merge(temp, grid->cols);
			reverse_array(temp, grid->cols);
			for(i=0;i<grid->cols;i++){
				grid->array[idx][i] = temp[i];
			}
		}
		free(temp);
	}

	if(addtile){
		for(i = 0;i<grid->rows;i++){
			for(idx = 0;idx<grid->cols;idx++){
				if(duplicate[i][idx] != grid->array[i][idx]){
					status = 1;
					new_tile(grid);
					break;
				}
			}

			if(status == 1)
				break;
		}
	}

	for(i=0;i<grid->rows;i++)
		free(duplicate[i]);
	free(duplicate);
	grid->heuristicscore = getHeuristicScore(grid);
	//printf("heuristicscorebackend: %d\n",grid->heuristicscore);
/*	return tileadded;*/
}

//returns 1 if the 2048 tile is obtained

int is_win(Grid *grid){

	int i,j;
	for(i=0;i<grid->rows;i++){
		for(j=0;j<grid->cols;j++){
			if(grid->array[i][j]>=2048)
				return 1;
		}
	}
	return 0;
}

//returns 1 if the two grids are identical else zero

int is_identical(Grid *grid1, Grid *grid2){

	int i,j;
	for(i=0;i<grid1->rows;i++){
		for(j=0;j<grid1->cols;j++){
			if(grid1->array[i][j] != grid2->array[i][j])
				return 0;
		}
	}
	return 1;
}

//returns 1 if the user cannot make any moves else returns 0
int is_terminated(Grid *grid){

	int i;
	Grid *grid_copy = grid_duplicate(grid);

	for(i=1;i<=4;i++){
		move_tiles(grid_copy, i,1);
		if(!is_identical(grid_copy,grid)){
			grid_delete(grid_copy);
			return 0;
		}
	}
	grid_delete(grid_copy);
	return 1;
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

int new_tile(Grid *grid){

	int row,col,list[] = {2,2,2,2,2,2,2,2,2,4};

	while(1){
		row = rand()%(grid->rows);
		col = rand()%(grid->cols);
		if(grid->array[row][col]==0){
			grid->array[row][col] = list[rand()%10];
			return grid->array[row][col];
			//break;
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
