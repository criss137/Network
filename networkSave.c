# include <stdlib.h>
# include <stdio.h>

#include "neuron.h"
#include "layer.h"
#include "neuralNet.h"

int saveNetwork(struct neuralNet *R, char *cda)
{
	FILE *fichier = fopen(cda, "w");
	if (fichier == NULL)
	{
		printf("ERROR: Save file cannot be created");
		return 1;
	}
	for (int i = 0; i < R->size; ++i)
	{
		fprintf(fichier, "L");
		for (int j = 0; j < R->layers[i].size; ++j)
		{
			fprintf(fichier, "N");
			for (int k = 0; k < R->layers[i].N[j].syn; ++k)
			{
				fprintf(fichier, "S%lfF", R->layers[i].N[j].synapses[k]);
			}
		}
	}
	fclose(fichier);
	return 0;
}

struct neuralNet *loadNetwork(char *cda)
{
	FILE *fichier = fopen(cda, "r");
	if (fichier == NULL)
	{
		printf("ERROR: file doesn't exist");
		return NULL;
	}
	int layer = 0;
	int neurons = 0;
	int syn = 0;
	
	int *layersize = NULL;
	double *synapses = NULL;
	
	int current = fgetc(fichier);
	double tempsyn = 0;
	
	int sign = 1;
	int powten = 10;
	int dec = 0;
	while (current != EOF)
	{
		if (current == 'L')
		{
			if (neurons)
			{
				layersize[layer - 1] = neurons;
			}
			++layer;
			layersize = realloc(layersize, layer * sizeof(int));
			neurons = 0;
			current = fgetc(fichier);
		}
		else if (current == 'N')
		{
			++neurons;
			current = fgetc(fichier);			
		}
		else if (current == 'S')
		{
			++syn;
			synapses = realloc(synapses, syn * sizeof(double));
			tempsyn = 0;
			sign = 1;
			powten = 10;
			dec = 0;
			current = fgetc(fichier);
		}
		else if (current == 'F')
		{
			synapses[syn - 1] = sign * tempsyn;
			current = fgetc(fichier);
		}
		else
		{
			if (current == 45)
			{
				sign = -1;
			}
			else if (current == 46)
			{
				dec = 1;
			}
			else
			{
				if (!dec)
				{
					tempsyn = (tempsyn * 10) + (current - 48);
				}
				else
				{
					tempsyn += ((double)(current -  48)) / powten;
					powten *= 10;
				}
			}
			current = fgetc(fichier);
		}
	}
	fclose(fichier);
	layersize[layer - 1] = neurons;
	struct neuralNet *R = initNeuralNet(layersize, layer);
	int count = 0;
	for (int i = 1; i < R->size; ++i)
	{
		for (int j = 0; j < R->layers[i].size; ++j)
		{
			for (int k = 0; k < R->layers[i].N[j].syn; ++k)
			{
				R->layers[i].N[j].synapses[k] = synapses[count];
				++count;
			}
		}
	}
	return R;
}


