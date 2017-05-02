#ifndef NETWORKSAVE_H_DEFINE
#define NETWORKSAVE_H_DEFINE

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <assert.h>
# include <err.h>

int saveNetwork(struct neuralNet *R, char *cda);
struct neuralNet *loadNetwork(char *cda);
#endif
