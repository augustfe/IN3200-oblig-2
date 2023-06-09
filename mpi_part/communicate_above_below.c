#include <mpi.h>
#include <stdio.h>

void communicate_above_below(int my_rank, int P, int nx, int my_ny, double **my_u)
{
    MPI_Status status;
    int neigh_below, neigh_above;

    // MPI_PROC_NULL specifies a dummy for boundary (ignored for upper and lower)
    neigh_below = (my_rank > 0) ? my_rank - 1 : MPI_PROC_NULL;
    neigh_above = (my_rank < P - 1) ? my_rank + 1 : MPI_PROC_NULL;

    int has_neigh_below, has_neigh_above;
    has_neigh_below = (my_rank > 0) ? 1 : 0;
    has_neigh_above = (my_rank < P - 1) ? 1 : 0;

    int endsize = my_ny - 1 + has_neigh_above + has_neigh_below;
    /*
    Pattern:
        1. Send to upper, receive from lower (tag = 2)
        2. Send to lower, receive from upper (tag = 3)
    */

    /*
    MPI_Sendrecv(
        SENT:
        buffer (arr),
        # elems, in this case x-dim,
        type (double),
        neighbour to send to (returns ASAP if MPI_PROC_NULL),
        tag,
        RECEIVED:
        --||--
        communicator,
        status,
    )
    */
    // Send from 'real' value, receive to ghost
    MPI_Sendrecv(&(my_u[endsize - 1][0]), nx, MPI_DOUBLE, neigh_above, 2, &(my_u[0][0]), nx, MPI_DOUBLE, neigh_below, 2,
                 MPI_COMM_WORLD, &status);

    MPI_Sendrecv(&(my_u[1][0]), nx, MPI_DOUBLE, neigh_below, 3, &(my_u[endsize][0]), nx, MPI_DOUBLE, neigh_above, 3,
                 MPI_COMM_WORLD, &status);
}