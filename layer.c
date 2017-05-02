# include <stdlib.h>

# include "layer.h"
# include "neuron.h"

struct layer *initLayer(int size, int syn)
{
	struct layer *L = malloc(sizeof(struct layer));
	L->size = size;
	L->N = malloc(size * sizeof(struct neuron));
	for (int i = 0; i < size; ++i)
	{
		L->N[i] = *initNeuron(syn);
	}
	return L;
}

void updateSum(struct layer *current, struct layer *previous)
{
	for (int i = 0; i < current->size;++i)
	{
		current->N[i].sum = 0;
		for (int j = 0; j < previous->size;++j)
		{
			current->N[i].sum += previous->N[j].out * 
			current->N[i].synapses[j];
		}
		active_n(&current->N[i]);
	}
}

void updateError(struct layer *current, struct layer *next)
{
	for (int i = 0; i < current->size;++i)
	{
		current->N[i].delta = 0;
		for (int j = 0; j < next->size;++j)
		{
			current->N[i].delta += next->N[j].synapses[i] * next->N[j].delta;
		}
	}
}

void updateWeights(struct layer *current, struct layer *previous)
{
	for (int i = 0; i < current->size; ++i)
	{
		for (int j = 0; j < current->N[i].syn; ++j)
		{
			current->N[i].synapses[j] += current->N[i].delta * 0.1  * 
			previous->N[j].out * sigmoid_d(current->N[i].sum);
		}
	}
}