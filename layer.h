#ifndef LAYER_H_DEFINE
#define LAYER_H_DEFINE

# include <stdlib.h>
# include <stdio.h>


struct layer
{
	struct neuron *N;
	int size;
};

struct layer *initLayer(int size, int syn);
void updateSum(struct layer *current, struct layer *previous);
void updateError(struct layer *current, struct layer *next);
void updateWeights(struct layer *current, struct layer *previous);
#endif