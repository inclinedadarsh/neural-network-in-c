#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  float or_w1;
  float or_w2;
  float or_b;
  float nand_w1;
  float nand_w2;
  float nand_b;
  float and_w1;
  float and_w2;
  float and_b;
} Xor;

// XOR Gate
float train[][3] = {{0, 0, 0}, {0, 1, 1}, {1, 0, 1}, {1, 1, 0}};
#define train_count (float)sizeof(train) / (float)sizeof(train[0])

float sigmoidf(float x) { return 1.f / (1.f + expf(-x)); }

float rand_float(void) { return (float)rand() / (float)RAND_MAX; }

float forward(Xor m, float x1, float x2) {
  float a = sigmoidf(m.or_w1 * x1 + m.or_w2 * x2 + m.or_b);
  float b = sigmoidf(m.nand_w1 * x1 + m.nand_w2 * x2 + m.nand_b);
  return sigmoidf(a * m.and_w1 + b * m.and_w2 + m.and_b);
}

float cost(Xor m) {
  float result = 0.f;
  for (size_t i = 0; i < train_count; ++i) {
    float x1 = train[i][0];
    float x2 = train[i][1];
    float y = train[i][2];

    float y_hat = forward(m, x1, x2);
    float diff = y_hat - y;
    result += diff * diff;
  }
  result /= train_count;
  return result;
}

Xor initialize_params(void) {
  Xor m;
  m.or_w1 = rand_float();
  m.or_w2 = rand_float();
  m.or_b = rand_float();
  m.and_w1 = rand_float();
  m.and_w2 = rand_float();
  m.and_b = rand_float();
  m.nand_w1 = rand_float();
  m.nand_w2 = rand_float();
  m.nand_b = rand_float();
  return m;
}

void print_xor(Xor m) {
  printf("or_w1 = %f, or_w2 = %f, or_b = %f\n", m.or_w1, m.or_w2, m.or_b);
  printf("nand_w1 = %f, nand_w2 = %f, nand_b = %f\n", m.nand_w1, m.nand_w2,
         m.nand_b);
  printf("and_w1 = %f, and_w2 = %f, and_b = %f\n", m.and_w1, m.and_w2, m.and_b);
}

Xor finite_diff(Xor m) {
  Xor g;
  float eps = 1e-1;
  float saved;

  float c = cost(m);

  saved = m.or_w1;
  m.or_w1 += eps;
  g.or_w1 = (cost(m) - c) / eps;
  m.or_w1 = saved;

  saved = m.or_w2;
  m.or_w2 += eps;
  g.or_w2 = (cost(m) - c) / eps;
  m.or_w2 = saved;

  saved = m.or_b;
  m.or_b += eps;
  g.or_b = (cost(m) - c) / eps;
  m.or_b = saved;

  saved = m.nand_w1;
  m.nand_w1 += eps;
  g.nand_w1 = (cost(m) - c) / eps;
  m.nand_w1 = saved;

  saved = m.nand_w2;
  m.nand_w2 += eps;
  g.nand_w2 = (cost(m) - c) / eps;
  m.nand_w2 = saved;

  saved = m.nand_b;
  m.nand_b += eps;
  g.nand_b = (cost(m) - c) / eps;
  m.nand_b = saved;

  saved = m.and_w1;
  m.and_w1 += eps;
  g.and_w1 = (cost(m) - c) / eps;
  m.and_w1 = saved;

  saved = m.and_w2;
  m.and_w2 += eps;
  g.and_w2 = (cost(m) - c) / eps;
  m.and_w2 = saved;

  saved = m.and_b;
  m.and_b += eps;
  g.and_b = (cost(m) - c) / eps;
  m.and_b = saved;

  return g;
}

Xor optimize(Xor m, Xor g) {
  float lr = 1e-1;

  m.or_w1 -= lr * g.or_w1;
  m.or_w2 -= lr * g.or_w2;
  m.or_b -= lr * g.or_b;

  m.nand_w1 -= lr * g.nand_w1;
  m.nand_w2 -= lr * g.nand_w2;
  m.nand_b -= lr * g.nand_b;

  m.and_w1 -= lr * g.and_w1;
  m.and_w2 -= lr * g.and_w2;
  m.and_b -= lr * g.and_b;

  return m;
}

int main(void) {
  // srand(42);
  srand(time(0));
  Xor m = initialize_params();

  for (size_t i = 0; i < 100 * 1000; ++i) {
    Xor g = finite_diff(m);
    m = optimize(m, g);
    // printf("cost = %f\n", cost(m));
    // printf("%f\n", cost(m));
  }

  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      printf("%zu ^ %zu = %f\n", i, j, forward(m, i, j));
    }
  }

  return 0;
}
