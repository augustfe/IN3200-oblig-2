#include <math.h>
#include <mpi.h>
#include <stdio.h>
#define Pi M_PI

double all_compute_numerical_error(int my_rank, int my_offset, int P, int nx, int my_ny, double dx, double dy,
                                   double t_value, double **my_u)
{
    double local_S = 0, tmp, S;
    int i, j, has_neigh_below;

    has_neigh_below = (my_rank > 0) ? 1 : 0;

    for (i = 0; i < my_ny; i++)
        for (j = 0; j < nx; j++)
        {
            tmp = cos(2.0 * Pi * (i + my_offset) * dy) * cos(2.0 * Pi * j * dx) * cos(Pi * t_value) -
                  my_u[i + has_neigh_below][j];
            local_S += tmp * tmp;
        }

    MPI_Allreduce(&local_S, &S, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    return sqrt(dx * dy * S);
}