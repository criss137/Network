#include "neuralNet.h"
#include "neuron.h"
#include "networkSave.h"
#include <math.h>

int main(void){
    FILE *f = fopen("network", "r");
    if (!f){
        int layersize[4];
        layersize[0] = 8;
        layersize[1] = 24;
        layersize[2] = 18;
        layersize[3] = 2;
        struct neuralNet *R = initNeuralNet(layersize, 4);
        saveNetwork(R, "network");
    }
    int errorhandler;
    
    int nb = 1;                 /* number of learning matches */
    double input[nb][8];        /* matches */
    double target[nb][2];       /* results */
    FILE *data = fopen("data", "r");
    for (int i = 0; i < nb; i++){
        for (int k = 0; k < 8; k++){
            errorhandler = fscanf(data, "%lf", input[i] + k);
        }
        errorhandler = fscanf(data, "%lf", target[i]);
        errorhandler = fscanf(data, "%lf", target[i] + 1);
        if (!errorhandler){
            printf("scanning error");
            return 1;
        }
    }
    
    // TEST ZONE //
    /*
    for (int i = 0; i < nb; i++){
        for (int k = 0; k < 8; k++){
            printf("%lf ", input[i][k]);
        }
        for (int k = 0; k < 2; k++){
            printf("%lf ", target[i][k]);
        }
        printf("\n");
    }
    */
    double tempError;
    struct neuralNet *R = loadNetwork("network");
    long double error = 1;
    int delay = 0;
	while ((error > 0.01) || (error < (-0.01)))
	{
		error = 0;
		for (int i = 0; i < nb; ++i)
		{
			learn(R, input[i], target[i]);
			for (int j = 0; j < 2; ++j)
			{
                tempError = R->lastLayer[j].delta;
                error = tempError > 0? error + tempError:error-tempError;
			}
		}
		delay++;
        if (delay % 100 == 0){
            if (delay%200 == 0){
                saveNetwork(R, "network_");
            }
            else{
                saveNetwork(R, "network");
            }
            printf("ERROR: %Lf\n", error);
            delay = delay >= 10000? 0 : delay;
        }
		
	}
	saveNetwork(R, "network");
}
