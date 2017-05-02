#ifndef NEURALNET_H_DEFINE
#define NEURALNET_H_DEFINE

# include <stdlib.h>
# include <stdio.h>

struct neuralNet
{
	struct layer *layers;
	int size;
	struct neuron *lastLayer;
	int lSize;
};

struct neuralNet *initNeuralNet(int layersizes[], int size);
void forward(struct neuralNet *R);
double calcError(struct neuron *N, double target);
void backPropagation(struct neuralNet *R, double *target);
void learn(struct neuralNet *R, double *target, double *input);
double *result(struct neuralNet *R, double *input);
#endif