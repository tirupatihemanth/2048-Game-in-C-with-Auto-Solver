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
	float clusterscore = 0;
	for(i=0;i<grid->rows;i++){
		for(j=0;j<grid->cols;j++){
			if(grid->array[i][j] != 0)
			clusterscore+=getavgscore(grid, i, j);
		}
	}
	return clusterscore;
}


//Implementation of a function to return heuristic score which is a measure to decide how best a given state of the grid is larger the heuristic score then the system try to achieve this state

int getHeuristicScore(Grid *grid){
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
	//printf("clusterscore: %f\n",getClusterScore(grid));
	//printf("emptycells: %d\n",emptycells);
	//printf("score: %d\n",grid->score);
	heuristicScore = (grid->score) + (log(grid->score)*emptycells) - getClusterScore(grid);
	//printf("heuristicscore: %d\n",heuristicScore);
	if(heuristicScore<0){
		return 0;
	}
	else{
		return heuristicScore;
	}

}



//Solution for finding the next best move given the grid at any point of time
//depth is how deeper AI is allowed to go
//alpha is maximum value of heuristic score found so far and beta is the minmum value of the heuristic score found so far

 Bestmove* best_move(Grid *grid, int depth, int alpha, int beta, int player){

 	//grid_print(grid);
 	Bestmove *bestmove = bestmove_initialise();
	int direction = 0,i,j,stat,bestscore;
	//printf("depth: %d \n",depth);
	//grid_print(grid);
	if(is_terminated(grid)){
		printf("blahterm\n");
		bestscore = grid->heuristicscore;
		//direction = 0;
	}
	else if(depth == 0){
		//printf("blahdepth\n");
		bestscore = grid->heuristicscore;
		//direction = 0;
	}
	else{

		if(player == USER){
			for(i=1;i<=4;i++){
				Grid *grid_copy = grid_duplicate(grid);
				move_tiles(grid_copy,i,0); 
				if(is_identical(grid_copy,grid) && grid_copy->score == grid->score){
					//printf("identical\n");
					grid_delete(grid_copy);
					continue;
				}
				Bestmove *temp = best_move(grid_copy, depth-1, alpha, beta, COMPUTER);
				if(temp->heuristicscore>alpha){
					alpha = temp->heuristicscore;
					direction = i;
				}
				grid_delete(grid_copy);
				if(beta<=alpha)
					break;
			}
			bestscore = alpha;
		}
		else{
			int randval;
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









/*Node *node_new(float data, Node *up, Node *down, Node *left, Node *right){
	Node *node = (Node *) malloc(sizeof(Node));
	node->data = data;
	node->up = up;
	node->down = down;
	node->left = left;
	node->right = right;
}

GTree *gtree_new(){
	GTree *gtree = (GTree *) malloc(sizeof(GTree));
	gtree->root = NULL;
}

GTree *gtree_add(GTree *gtree, float data){
	NOde *node = node_new(data, NULL, NULL, NULL);

	if(gtree->root == NULL){
		gtree->root = node;
		return(gtree);
	}
	Node *iterator = gtree->root;

	while(1){
		if(iterator->up == NULL){
			iterator->up = node;
			return gtree;
		}
		else if(iterator->down == NULL){
			iterator->down = node;
			return gtree;
		}
		else if(iterator->left == NULL){
			iterator->left = node;
			return gtree;
		}
		else if(iterator->right == NULL){
			iterator->right = node;
			return gtree;
		}
		else{
			int k = rand()%4;
			switch(k){
				case 0:
					iterator = iterator->up;
					break;
				case 1:
					iterator = iterator->down;
					break;
				case 2:
					iterator = iterator->left;
					break;
				case 3:
					iterator = iterator->right;
					break;
				default:
					printf("An internal error has occured");
					exit(1);
			}
		}
		continue;

	}
}

GTree * make_postree(GTree *gtree, Grid *grid, int depth){
	//gtree_add(grid->heuristicscore);
	Grid *grid_new = grid_duplicate(grid);
	move_tiles(grid_new,UP);
	
}

*/