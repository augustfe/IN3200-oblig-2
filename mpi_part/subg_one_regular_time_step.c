void subg_one_regular_time_step(int my_rank, int P, int nx, int my_ny, double dx, double dy, double dt,
    double** my_u_new, double** my_u, double** my_u_prev) {
    int i, j, has_neigh_below, has_neigh_above;
    double u_left, u_right, u_below, u_above;
    double dx_const, dy_const;
    has_neigh_below = (my_rank > 0) ? 1 : 0;
    has_neigh_above = (my_rank < P - 1) ? 1 : 0;
    dx_const = (dt * dt) / (8 * dx * dx);
    dy_const = (dt * dt) / (8 * dy * dy);

    for (i = 1; i < my_ny + (has_neigh_above * has_neigh_below); i++) {
        for (j = 0; j < nx; j++) {
            u_left = (j == 0) ? my_u[i][1] : my_u[i][j - 1];
            u_right = (j == nx - 1) ? my_u[i][nx - 2] : my_u[i][j + 1];
            u_below = my_u[i - 1][j];
            u_above = my_u[i + 1][j];

            my_u_new[i][j] = 2 * my_u[i][j]
                + dx_const * (u_left - 2 * my_u[i][j] + u_right)
                + dy_const * (u_below - 2 * my_u[i][j] + u_above)
                - my_u_prev[i][j];
        }
    }

    if (my_rank == 0) {
        i = 0;
        for (j = 0; j < nx; j++) {
            u_left = (j == 0) ? my_u[i][1] : my_u[i][j - 1];
            u_right = (j == nx - 1) ? my_u[i][nx - 2] : my_u[i][j + 1];
            u_below = my_u[1][j];
            u_above = my_u[i + 1][j];

            my_u_new[i][j] = 2 * my_u[i][j]
                + dx_const * (u_left - 2 * my_u[i][j] + u_right)
                + dy_const * (u_below - 2 * my_u[i][j] + u_above)
                - my_u_prev[i][j];
        }
    }
    if (my_rank == P - 1) {
        i = my_ny;
        for (j = 0; j < nx; j++) {
            u_left = (j == 0) ? my_u[i][1] : my_u[i][j - 1];
            u_right = (j == nx - 1) ? my_u[i][nx - 2] : my_u[i][j + 1];
            u_below = my_u[i - 1][j];
            u_above = my_u[my_ny - 1][j];

            my_u_new[i][j] = 2 * my_u[i][j]
                + dx_const * (u_left - 2 * my_u[i][j] + u_right)
                + dy_const * (u_below - 2 * my_u[i][j] + u_above)
                - my_u_prev[i][j];
        }
    }
}