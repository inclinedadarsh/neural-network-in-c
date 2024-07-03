# Neural network in C

These are some pretty basic implementation of the Neural network in C language.

I have made these just for fun while wanting to get started in C.

## Files & descriptions

- [linear_line.c](./linear_line.c) :- An _over engineered_ linear neural network implementation. It's a basic neuron (or perceptron) which identifies the solution for the line `y = 4x + 1`.

- [and.c](./and.c) :- A _non-linear_ neural network implementation for learning the data of different gates. In the code, I have used the OR gate data, but it can be trained on any gate data except XOR gate.

- [xor.c](./xor.c) :- A multi-layer neural network implementation for learning the data of XOR gate. It uses 2 neurons (2 + 1) and learns the XOR gate data.
