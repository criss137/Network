#MAKEFILE

training:
	gcc -std=c99 -O2 -MMD networkSave.c neuralNet.c layer.c neuron.c training.c -lm -o training -lm
	
main:
	gcc -std=c99 -O2 -MMD main.c neuralNet.c layer.c neuron.c networkSave.c -o main -lm
 
clean:
	rm -f *.o *.d *~ main training
 
# END Makefile
