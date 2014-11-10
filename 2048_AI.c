#include <math.h>
#include <stdlib.h>
#include "backend.h"
#include "2048_AI.h"
#include <stdio.h>

//Implementation of a helper function for getClusterscore function


Bestmove *bestmove_initialise(){
	Bestmove *bestmove = (Bestmove *) malloc(sizeof(Bestmove));
	return bestmove;
}

float getavgscore(Grid *grid, int i, int j){
	int num = grid->array[i][j], neighbours = 0;
	float diff = 0;
	if(i>0){
		diff += abs(num - grid->array[i-1][j]);
		neighbours++;
	}
	if(i<(grid->rows-1)){
		diff +=abs(num - grid->array[i+1][j]);
		neighbours++;
	}
	if(j>0){
		diff += abs(num - grid->array[i][j-1]);
		neighbours++;
	}
	if(j<(grid->cols-1)){
		diff += abs(num - grid->array[i][j+1]);
		neighbours++;
	}
	return (diff/neighbours);

}

//Implemetation of a function to return cluster score where cluster score is a measure of scatteredness of the grid i.e if similar values are at large distances then cluster score would be higher

float getClusterScore(Grid *grid){

	int i,j;
	float clusterscore = 0,sum = 0;
	for(i=0;i<grid->rows;i++){
		for(j=0;j<grid->cols;j++){
			if(grid->array[i][j] != 0){
				clusterscore+=getavgscore(grid, i, j);
				sum+=grid->array[i][j];
			}
		}
	}
	return clusterscore;
}


//Implementation of a function to return heuristic score which is a measure to decide how best a given state of the grid is larger the heuristic score then the system try to achieve this state

/*int getHeuristicScore(Grid *grid){
	if(grid->score == 0)
		return 0;
	int emptycells = 0, i, j;
	int heuristicScore = 0;
	for(i=0;i<grid->rows;i++){
		for(j=0;j<grid->cols;j++){
			if(grid->array[i][j] == 0)
				emptycells++;
		}
	}

	heuristicScore = grid->score + (log(grid->score)*emptycells)-1.5*getClusterScore(grid);	//printf("heuristicscore: %d\n",heuristicScore);
		return heuristicScore;

}*/

int getHeuristicScore(Grid *grid){
	int stat1[4][4] = {{4,3,2,1},{3,2,1,0},{2,1,0,-1},{1,0,-1,-2}};
	int stat2[4][4] = {{1,2,3,4},{0,1,2,3},{-1,0,1,2},{-2,-1,0,1}};
	//int stat1[4][4] = {{0,-1,-2,-3},{1,0,-1,-2},{2,1,0,-1},{3,2,1,0}};
	//int stat2[4][4] = {{-3,-2,-1,0},{-2,-1,0,1},{-1,0,1,2},{0,1,2,3}};
	int finalcount = 0,i,j,emptycells=0;
	int count =0;
	for(i=0;i<grid->rows;i++){
		for(j=0;j<grid->cols;j++){
			if(grid->array[i][j] == 0)
				emptycells++;
			count+=grid->array[i][j]*stat1[i][j];
		}
	}

	count = abs(count);
	finalcount = count;
	//printf("count1: %d\n",count);
	count =0;
	
	for(i=0;i<grid->rows;i++){
		for(j=0;j<grid->cols;j++){
			count+=grid->array[i][j]*stat2[i][j];
		}
	}
	count = abs(count);
	finalcount = count>finalcount?count:finalcount;
	//return finalcount;
	//return finalcount-getClusterScore(grid);
	return grid->score+25*finalcount+log(grid->score)*emptycells - 12.75*getClusterScore(grid);
	//15 10 -25000 200000
	//15 7 25000 200000
	//25 10 200000
	// 25 12
	// 25 12.75
	//25 13
}

//Solution for finding the next best move given the grid at any point of time
//depth is how deeper AI is allowed to go
//alpha is maximum value of heuristic score found so far and beta is the minmum value of the heuristic score found so far


 Bestmove* best_move(Grid *grid, int depth, int alpha, int beta, int player){


 	Bestmove *bestmove = bestmove_initialise();
	int direction = 0,bestscore;

	if(is_terminated(grid)){
		//printf("blahterm\n");
		bestscore = -200000;
		//printf("%d bestscore",bestscore);
	}
	else if(depth == 0){
		bestscore = grid->heuristicscore;

	}
	else{
		int i;
		if(player == USER){
			for(i=1;i<=4;i++){
				Grid *grid_copy = grid_duplicate(grid);
				move_tiles(grid_copy,i,0);
				if(is_identical(grid_copy,grid)){
					grid_delete(grid_copy);
					continue;
				}
				Bestmove *temp = best_move(grid_copy, depth-1, alpha, beta, COMPUTER);
				if(temp->heuristicscore>alpha){
					alpha = temp->heuristicscore;
					direction = i;
				}
				grid_delete(grid_copy);
				free(temp);
				if(beta<=alpha)
					break;
			}
			bestscore = alpha;
		}
		else{
			int randval,j,i,stat;
			stat = 0;
			for(i=0;i< grid->rows;i++){
				for(j=0;j<grid->cols;j++){
					if(grid->array[i][j] == 0){
						for(randval=2;randval<=4;randval+=2){
							Grid *grid_copy = grid_duplicate(grid);
							grid_copy->array[i][j] = randval;
							Bestmove *temp = best_move(grid_copy, depth-1, alpha, beta, USER);
							if((temp->heuristicscore) < beta){
								beta = temp->heuristicscore;
							}
							grid_delete(grid_copy);
							free(temp);
							if(beta<=alpha){
								stat = 1;
								break;
							}
						}
					}
					if(stat == 1)
						break;
				}
				if(stat == 1)
					break;
			}
			bestscore = beta;
		}

	}
	bestmove->heuristicscore = bestscore;
	bestmove->direction = direction;
	return bestmove;
}

/*Bestmove* best_move(Grid *grid, int depth){

	Bestmove *bestmove = bestmove_initialise();
	int bestscore = 0, direction = 0, i,j;
	if(is_terminated(grid))
		bestscore = 0;
	else if(depth <= 0){
		bestscore = grid->heuristicscore;
	}
	else{
		for(i=1;i<=4;i++){

			Grid *grid_copy = grid_duplicate(grid);
			move_tiles(grid_copy,i,0); 
			if(is_identical(grid_copy,grid)){
				grid_delete(grid_copy);
				continue;
			}

			Bestmove *temp = computer_move(grid_copy, depth-1);
			grid_delete(grid_copy);
			if(temp->heuristicscore>=bestscore){
				bestscore = temp->heuristicscore;
				direction = i;
			}
			free(temp);
		}
	}
	bestmove->heuristicscore = bestscore;
	bestmove->direction = direction;
	return bestmove;
}

Bestmove* computer_move(Grid *grid, int depth){

	Bestmove *bestmove = bestmove_initialise();
	int i,j,randval;
	float score =0,weight=0,probability;
	for(i=0;i<grid->rows;i++){
		for(j=0;j<grid->cols;j++){
			if(grid->array[i][j] == 0){
				for(randval = 2;randval<=4;randval+=2){

					Grid *grid_copy = grid_duplicate(grid);
					grid_copy->array[i][j] = randval;
					Bestmove *temp = best_move(grid_copy,depth-1);
					grid_delete(grid_copy);
					probability = (randval==2)? 0.9 : 0.1;
					score+=temp->heuristicscore*probability;
					weight+=probability;
					free(temp);
				}
			}
		}
	}
	bestmove->heuristicscore = score*1.0/weight;
	return bestmove;
}*/