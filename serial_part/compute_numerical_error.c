#include <math.h>
#include <stdio.h>
#define Pi M_PI

double compute_numerical_error(int nx, int ny, double dx, double dy,
  double t_value, double** u) {
  double S = 0, tmp;
  int i, j;

  for (i = 0; i < ny; i++)
    for (j = 0; j < nx; j++) {
      tmp = cos(2.0 * Pi * i * dy) * cos(2.0 * Pi * j * dx) * cos(Pi * t_value)
        - u[i][j];
      S += tmp * tmp;
    }

  return sqrt(dx * dy * S);
}
