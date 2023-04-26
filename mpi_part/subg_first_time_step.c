void subg_first_time_step(int my_rank, int P, int nx, int my_ny, double dx, double dy, double dt, double **my_u,
                          double **my_u_prev)
{
    int i, j;
    double u_left, u_right, u_below, u_above;
    double dx_const, dy_const;
    dx_const = (dt * dt) / (16 * dx * dx);
    dy_const = (dt * dt) / (16 * dy * dy);

    for (i = 1; i < my_ny; i++)
    {
        for (j = 0; j < nx; j++)
        {
            u_left = (j == 0) ? my_u_prev[i][1] : my_u_prev[i][j - 1];
            u_right = (j == nx - 1) ? my_u_prev[i][nx - 2] : my_u_prev[i][j + 1];
            u_below = my_u_prev[i - 1][j];
            u_above = my_u_prev[i + 1][j];

            my_u[i][j] = my_u_prev[i][j] + dx_const * (u_left - 2 * my_u_prev[i][j] + u_right) +
                         dy_const * (u_below - 2 * my_u_prev[i][j] + u_above);
        }
    }

    if (my_rank == 0)
    {
        i = 0;
        for (j = 0; j < nx; j++)
        {
            u_left = (j == 0) ? my_u_prev[i][1] : my_u_prev[i][j - 1];
            u_right = (j == nx - 1) ? my_u_prev[i][nx - 2] : my_u_prev[i][j + 1];
            u_below = my_u_prev[1][j];
            u_above = my_u_prev[i + 1][j];

            my_u[i][j] = my_u_prev[i][j] + dx_const * (u_left - 2 * my_u_prev[i][j] + u_right) +
                         dy_const * (u_below - 2 * my_u_prev[i][j] + u_above);
        }
    }
    else if (my_rank == P - 1)
    {
        i = my_ny;
        for (j = 0; j < nx; j++)
        {
            u_left = (j == 0) ? my_u_prev[i][1] : my_u_prev[i][j - 1];
            u_right = (j == nx - 1) ? my_u_prev[i][nx - 2] : my_u_prev[i][j + 1];
            u_below = my_u_prev[i - 1][j];
            u_above = my_u_prev[my_ny - 1][j];

            my_u[i][j] = my_u_prev[i][j] + dx_const * (u_left - 2 * my_u_prev[i][j] + u_right) +
                         dy_const * (u_below - 2 * my_u_prev[i][j] + u_above);
        }
    }
    else
    {
        i = my_ny;
        for (j = 0; j < nx; j++)
        {
            u_left = (j == 0) ? my_u_prev[i][1] : my_u_prev[i][j - 1];
            u_right = (j == nx - 1) ? my_u_prev[i][nx - 2] : my_u_prev[i][j + 1];
            u_below = my_u_prev[i - 1][j];
            u_above = my_u_prev[i + 1][j];

            my_u[i][j] = my_u_prev[i][j] + dx_const * (u_left - 2 * my_u_prev[i][j] + u_right) +
                         dy_const * (u_below - 2 * my_u_prev[i][j] + u_above);
        }
    }
}
