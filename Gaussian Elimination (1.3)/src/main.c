#include <math.h>
#include <stdio.h>
#define N 4 // 方程组的大小

// 函数前向声明
void gaussianElimination(double a[][N + 1]);

int main() {
  // 这里我们用增广矩阵来代表方程组
  double a[N][N + 1] = {{1.116, 0.125, 0.139, 0.149, 1.547},
                       {0.158, 1.167, 0.176, 0.187, 1.647},
                       {0.196, 0.207, 1.216, 0.227, 1.747},
                       {0.236, 0.247, 0.256, 1.267, 1.847}};

  // 进行高斯消元
  gaussianElimination(a);

  // 打印结果
  printf("解为: \n");
  for (int i = 0; i < N; i++) {
    printf("x%d = %.4f\n", i + 1, a[i][N]);
  }

  return 0;
}

void gaussianElimination(double a[][N + 1]) {
  int i = 0;
  int j = 0;
  int k = 0;
  double factor = NAN;

  // 前向消元过程
  for (k = 0; k < N - 1; k++) {
    for (i = k + 1; i < N; i++) {
      factor = a[i][k] / a[k][k];
      for (j = k; j <= N; j++) {
        a[i][j] -= factor * a[k][j];
      }
    }
  }

  // 回代过程
  for (i = N - 1; i >= 0; i--) {
    for (j = i + 1; j < N; j++) {
      a[i][N] -= a[i][j] * a[j][N];
    }
    a[i][N] = a[i][N] / a[i][i];
  }
}
