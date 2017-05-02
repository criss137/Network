# include <stdlib.h>
# include <math.h>

# include "neuron.h"

struct neuron *initNeuron(int syn)
{
	struct neuron *neur = malloc(sizeof(struct neuron));
	neur->syn = syn;
	neur->synapses = malloc(syn * sizeof(double));
	for (int i = 0; i < syn; ++i)
	{
		neur->synapses[i] = (((double)rand() / (double)RAND_MAX) - 0.5);
	}
	neur->sum = 0;
	neur->out = 0;
	neur->delta = 0;
	return neur;
}

double sigmoid(double input)
{
	return (1.0 / (1.0 + exp(-input)));
}

double sigmoid_d(double input)
{
	return (exp(-input)/((1 + exp(-input)) * (1 + exp(-input))));
}

void active_n(struct neuron *N)
{
	N->out = sigmoid(N->sum);
}