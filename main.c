/* --- */

#include "neuralNet.h"
#include "neuron.h"
#include "layer.h"
#include "networkSave.h"

int main(void){
    struct neuralNet *R = loadNetwork("network");
    double input[8] = {17,32,0.4,0.15,7,6,6,0};
    double *res = malloc(2*sizeof(double));
    res = result(R, input);
    printf("JOUEUR1: %lf   JOUEUR2: %lf\n", res[0], res[1]);
    free(res);
    return 0;
}

/* ---*/
