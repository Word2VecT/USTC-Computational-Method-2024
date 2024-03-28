#include <math.h>
#include <stdio.h>
#define N 4 // 方程组的大小

void pivotGaussianElimination(float a[][N + 1], float x[]);

int main() {
  // 这里我们用增广矩阵来代表方程组
  float a[N][N + 1] = {{1.116, 0.125, 0.139, 0.149, 1.547},
                       {0.158, 1.167, 0.176, 0.187, 1.647},
                       {0.196, 0.207, 1.216, 0.227, 1.747},
                       {0.236, 0.247, 0.256, 1.267, 1.847}};
  float x[N]; // 用于存储解的数组

  // 进行列主元素高斯消元
  pivotGaussianElimination(a, x);

  // 打印结果
  printf("解为: \n");
  for (int i = 0; i < N; i++) {
    printf("x%d = %f\n", i + 1, x[i]);
  }

  return 0;
}

void pivotGaussianElimination(float a[][N + 1], float x[]) {
  int i, j, k, maxIndex;
  float factor, max, temp;

  // 列主元素消去法
  for (k = 0; k < N - 1; k++) {
    // 找出当前列中绝对值最大的行
    max = fabs(a[k][k]);
    maxIndex = k;
    for (i = k + 1; i < N; i++) {
      if (fabs(a[i][k]) > max) {
        max = fabs(a[i][k]);
        maxIndex = i;
      }
    }

    // 将最大值所在行与当前行交换
    if (k != maxIndex) {
      for (j = 0; j <= N; j++) {
        temp = a[k][j];
        a[k][j] = a[maxIndex][j];
        a[maxIndex][j] = temp;
      }
    }

    // 进行消元
    for (i = k + 1; i < N; i++) {
      factor = a[i][k] / a[k][k];
      for (j = k; j <= N; j++) {
        a[i][j] -= factor * a[k][j];
      }
    }
  }

  // 回代求解
  for (i = N - 1; i >= 0; i--) {
    x[i] = a[i][N];
    for (j = i + 1; j < N; j++) {
      x[i] -= a[i][j] * x[j];
    }
    x[i] /= a[i][i];
  }
}
