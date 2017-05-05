/* --- */

#include "neuralNet.h"
#include "neuron.h"
#include "layer.h"
#include "networkSave.h"

int main(void){
    struct neuralNet *R = loadNetwork("network");
    
    double first_hand = 1;
    double first_age = 35;
    double first_rank = 287;
    double first_points = 172;
    
    double second_hand = 1;
    double second_age = 26;
    double second_rank = 95;
    double second_points = 558;
    
    double input[8] = {first_hand, first_age/100, 1/first_rank, first_points/10000, second_hand, second_age/100, 1/second_rank, second_points/10000};
    double *res = malloc(2*sizeof(double));
    res = result(R, input);
    printf("JOUEUR1: %lf   JOUEUR2: %lf\n", res[0], res[1]);
    free(res);
    return 0;
}

/* --- */
