#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// OR Gate
float train[][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1},
};

#define train_count (sizeof(train) / sizeof(train[0]))

float sigmoidf(float z) { return 1.f / (1.f + expf(-z)); }

float cost(float w1, float w2, float b) {
  float result = 0.0f;
  for (size_t i = 0; i < train_count; ++i) {
    float x1 = train[i][0];
    float x2 = train[i][1];
    float y = train[i][2];

    float z = x1 * w1 + x2 * w2 + b;
    float y_hat = sigmoidf(z);
    float diff = y_hat - y;

    result += diff * diff;
  }
  result /= train_count;
  return result;
}

float rand_float(void) { return (float)rand() / (float)RAND_MAX; }

int main(void) {
  srand(time(0));
  // srand(42);

  float eps = 1e-2;
  float lr = 1e-2;

  float w1 = rand_float();
  float w2 = rand_float();
  float b = rand_float();

  for (int i = 0; i < 40000; ++i) {
    float dw1 = (cost(w1 + eps, w2, b) - cost(w1, w2, b)) / eps;
    float dw2 = (cost(w1, w2 + eps, b) - cost(w1, w2, b)) / eps;
    float db = (cost(w1, w2, b + eps) - cost(w1, w2, b)) / eps;
    w1 = w1 - lr * dw1;
    w2 = w2 - lr * dw2;
    b = b - lr * db;

    float c = cost(w1, w2, b);
    if ((i + 1) % 500 == 0) {
      printf("w1 = %f, w2 = %f, b = %f, cost = %f\n", w1, w2, b, c);
    }
  }

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      printf("%d | %d = %f\n", i, j, sigmoidf(w1 * i + w2 * j + b));
    }
  }

  return 0;
}
