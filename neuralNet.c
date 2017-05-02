# include <stdlib.h>

#include "layer.h"
#include "neuron.h"
#include "neuralNet.h"

struct neuralNet *initNeuralNet(int *layersizes, int size)
{
	struct neuralNet *R = malloc(sizeof(struct neuralNet));
	R->size = size;
	R->layers = malloc(size * sizeof(struct layer));
	int i = 0;
	for (;i < size; ++i)
	{
		if (i == 0)
		{
			R->layers[i] = *initLayer(layersizes[i], 0);
		}
		else
		{
			R->layers[i] = *initLayer(layersizes[i], layersizes[i - 1]);
		}
	}
	R->lastLayer = R->layers[i - 1].N;
	R->lSize = R->layers[i - 1].size;
	return R;
}

void forward(struct neuralNet *R)
{
	for (int i = 1; i < R->size;++i)
	{
		updateSum(&R->layers[i], &R->layers[i - 1]);
	}
}

double *result(struct neuralNet *R, double *input)
{
	for (int i = 0; i < R->layers[0].size;++i)
	{
		R->layers[0].N[i].out = input[i];
	}
	forward(R);
	double *returnValue = malloc(R->lSize * sizeof(double));
	for (int i = 0; i < R->lSize; ++i)
	{
		returnValue[i] = R->lastLayer[i].out;
	}
	return returnValue;
}

void backPropagation(struct neuralNet *R, double *target)
{
	for (int i = 0; i < R->lSize;++i)
	{
		R->lastLayer[i].delta = calcError(&R->lastLayer[i], target[i]);
	}
	for (int i = R->size - 1; i > 0; --i)
	{
		updateError(&R->layers[i - 1], &R->layers[i]);
	}
	for (int i = 0; i < R->size - 1; ++i)
	{
		updateWeights(&R->layers[i + 1], &R->layers[i]);
	}
}

double calcError(struct neuron *N, double target)
{
	return (target - N->out);
}

void learn(struct neuralNet *R, double *input, double *target)
{
		for (int i = 0; i < R->layers[0].size;++i)
		{
			R->layers[0].N[i].out = input[i];
		}
		forward(R);
		backPropagation(R, target);
}