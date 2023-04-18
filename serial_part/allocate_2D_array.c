#include <stdlib.h>

void allocate_2D_array(double*** array_ptr, int nx, int ny) {
  double* A_storage = (double*) malloc(nx * ny * sizeof(double));
  double** A = (double**) malloc(ny * sizeof(double*));
  for (int i = 0; i < ny; i++)
    A[i] = &(A_storage[i * nx]);
  *array_ptr = A;
}
