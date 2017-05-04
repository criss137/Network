/* --- */

#include "neuralNet.h"
#include "neuron.h"
#include "layer.h"
#include "networkSave.h"

int main(void){
    struct neuralNet *R = loadNetwork("network");
    double input[8] = {1, 0.274825, 0.045000, 1.005000,1 ,0.348775, 0.039000, 1.100000};
    double *res = malloc(2*sizeof(double));
    res = result(R, input);
    printf("JOUEUR1: %lf   JOUEUR2: %lf\n", res[0], res[1]);
    free(res);
    return 0;
}

/* ---*/
