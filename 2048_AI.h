#ifndef AI_2048_H
#define AI_2048_H

#define USER 5
#define COMPUTER 6

typedef struct bestmove_{

	int heuristicscore;
	int direction;

} Bestmove;

/*typedef struct Node_{

	float data;
	Node *up;
	Node *down;
	Node *left;
	Node *right;

} Node;

typedef struct GTree_{
	Node *root;
} GTree;*/
Bestmove* bestmove_initialise();
Bestmove* best_move(Grid *, int, int, int, int);
//Bestmove* best_move(Grid *, int);
//Bestmove* computer_move(Grid *, int);
float getClusterScore(Grid *);
int getHeuristicScore(Grid *);

/*Node *node_new(float, Node *, Node *, Node *, Node *);

GTree *gtree_new();

GTree *gtree_add(GTree *, float):*/
#endif