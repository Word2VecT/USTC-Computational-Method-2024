#include <stdio.h>
#define N 3

void LUdecomposition(double A[N][N], double L[N][N], double U[N][N]);
void forwardSubstitution(double L[N][N], double b[N], double y[N]);
void backSubstitution(double U[N][N], double y[N], double x[N]);

int main() {
  double A[N][N] = {{2, 2, 3}, {4, 7, 7}, {-2, 4, 5}};
  double b[N] = {3, 1, -7};
  double L[N][N] = {0}; // 初始化为零
  double U[N][N] = {0}; // 初始化为零
  double y[N] = {0};    // 存储前向替代结果
  double x[N] = {0};    // 存储最终结果

  // 进行LU分解
  LUdecomposition(A, L, U);

  // 前向替代，解L*y=b
  forwardSubstitution(L, b, y);

  // 后向替代，解U*x=y
  backSubstitution(U, y, x);

  // 打印解
  printf("解为：\n");
  for (int i = 0; i < N; i++) {
    printf("x%d = %f\n", i + 1, x[i]);
  }

  return 0;
}

// LU分解函数
void LUdecomposition(double A[N][N], double L[N][N], double U[N][N]) {
  int i = 0;
  int j = 0;
  int k = 0;

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (j < i)
        L[j][i] = 0;
      else {
        L[j][i] = A[j][i];
        for (k = 0; k < i; k++) {
          L[j][i] = L[j][i] - L[j][k] * U[k][i];
        }
      }
    }
    for (j = 0; j < N; j++) {
      if (j < i)
        U[i][j] = 0;
      else if (j == i)
        U[i][j] = 1;
      else {
        U[i][j] = A[i][j] / L[i][i];
        for (k = 0; k < i; k++) {
          U[i][j] = U[i][j] - ((L[i][k] * U[k][j]) / L[i][i]);
        }
      }
    }
  }
}

// 前向替代函数
void forwardSubstitution(double L[N][N], double b[N], double y[N]) {
  for (int i = 0; i < N; i++) {
    y[i] = b[i];
    for (int j = 0; j < i; j++) {
      y[i] -= L[i][j] * y[j];
    }
    y[i] /= L[i][i];
  }
}

// 后向替代函数
void backSubstitution(double U[N][N], double y[N], double x[N]) {
  for (int i = N - 1; i >= 0; i--) {
    x[i] = y[i];
    for (int j = i + 1; j < N; j++) {
      x[i] -= U[i][j] * x[j];
    }
  }
}
