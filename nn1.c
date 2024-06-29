#include <stdio.h>
#include <stdlib.h>

struct Params
{
	float w;
	float b;
};

struct Grads
{
	float dw;
	float db;
};

int train[][2] = {
	{0, 1},
	{1, 5},
	{2, 9},
	{3, 13},
	{4, 17},
	{5, 21},
	{6, 25}};

#define train_size (int)sizeof(train) / (int)sizeof(train[0])

float rand_float()
{
	return (float)rand() / (float)RAND_MAX;
}

struct Params initialize_params(void)
{
	float w = rand_float() * 10;
	float b = 0.f;
	struct Params p;
	p.w = w;
	p.b = b;
	return p;
}

float cost(float w, float b)
{
	float result = 0.f;
	for (int i = 0; i < train_size; ++i)
	{
		float y = w * train[i][0] + b;
		float diff = y - train[i][1];
		result += diff * diff;
	}
	result /= train_size;
	return result;
}

struct Params optimize(struct Params p, struct Grads g)
{
	float lr = 1e-3;

	float w = p.w;
	float b = p.b;
	float dw = g.dw;
	float db = g.db;

	w = w - lr * dw;
	b = b - lr * db;

	struct Params result;
	result.w = w;
	result.b = b;
	return result;
}

struct Grads backward_prop(struct Params p, float (*f)(float, float))
{
	float eps = 1e-3;
	float w = p.w;
	float b = p.b;

	float cost = (*f)(w, b);
	float dw = ((*f)(w + eps, b) - cost) / eps;
	float db = ((*f)(w, b + eps) - cost) / eps;
	struct Grads g;
	g.dw = dw;
	g.db = db;
	return g;
}

int main(void)
{
	srand(42);

	struct Params params = initialize_params();

	for (size_t i = 1; i <= 1000; ++i)
	{
		float c = cost(params.w, params.b);
		struct Grads grads = backward_prop(params, cost);
		params = optimize(params, grads);

		if (i % 100 == 0)
		{
			printf("Iteration = %zu, Cost = %f\n", i, c);
		}
	}

	printf("w = %f, b = %f\n", params.w, params.b);

	return 0;
}
