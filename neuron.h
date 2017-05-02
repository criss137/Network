#ifndef NEURON_H_DEFINE
#define NEURON_H_DEFINE

# include <stdlib.h>
# include <stdio.h>

struct neuron
{
	double *synapses;
	int syn;
	double sum;
	double delta;
	double out;
};

struct neuron *initNeuron(int syn);
double sigmoid(double input);
double sigmoid_d(double input);
void active_n(struct neuron *N);
#endif