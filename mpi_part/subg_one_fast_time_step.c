void subg_one_fast_time_step(int my_rank, int P, int nx, int my_ny, double dx, double dy, double dt,
    double** my_u_new, double** my_u, double** my_u_prev) {
    int i, j, has_neigh_below, has_neigh_above;
    double u_left, u_right, u_below, u_above;
    double dx_const, dy_const;
    has_neigh_below = (my_rank > 0) ? 1 : 0;
    has_neigh_above = (my_rank < P - 1) ? 1 : 0;
    dx_const = (dt * dt) / (8 * dx * dx);
    dy_const = (dt * dt) / (8 * dy * dy);

    for (i = 1; i < my_ny + (has_neigh_above * has_neigh_below); i++) {
        my_u_new[i][0] = 2 * my_u[i][0]
            + dx_const * (2 * my_u[i][1] - 2 * my_u[i][0])
            + dy_const * (my_u[i - 1][0] - 2 * my_u[i][0] + my_u[i + 1][0])
            - my_u_prev[i][0];
        for (j = 1; j < nx - 1; j++) {
            u_left = my_u[i][j - 1];
            u_right = my_u[i][j + 1];
            u_below = my_u[i - 1][j];
            u_above = my_u[i + 1][j];

            my_u_new[i][j] = 2 * my_u[i][j]
                + dx_const * (u_left - 2 * my_u[i][j] + u_right)
                + dy_const * (u_below - 2 * my_u[i][j] + u_above)
                - my_u_prev[i][j];
        }
        j = nx - 1;
        my_u_new[i][j] = 2 * my_u[i][j]
            + dx_const * (2 * my_u[i][j - 1] - 2 * my_u[i][j])
            + dy_const * (my_u[i - 1][j] - 2 * my_u[i][j] + my_u[i + 1][j])
            - my_u_prev[i][j];
    }

    if (my_rank == 0) {
        // Top row
        i = 0;
        for (j = 1; j < nx - 1; j++) {
            u_left = my_u[i][j - 1];
            u_right = my_u[i][j + 1];
            u_below = my_u[1][j];

            my_u_new[i][j] = 2 * my_u[i][j]
                + dx_const * (u_left - 2 * my_u[i][j] + u_right)
                + dy_const * (2 * u_below - 2 * my_u[i][j])
                - my_u_prev[i][j];
        }
        // Upper corners
        my_u_new[0][0] = 2 * my_u[0][0]
            + dx_const * (2 * my_u[0][1] - 2 * my_u[0][0])
            + dy_const * (2 * my_u[1][0] - 2 * my_u[0][0])
            - my_u_prev[0][0];

        my_u_new[0][nx - 1] = 2 * my_u[0][nx - 1]
            + dx_const * (2 * my_u[0][nx - 2] - 2 * my_u[0][nx - 1])
            + dy_const * (2 * my_u[1][nx - 1] - 2 * my_u[0][nx - 1])
            - my_u_prev[0][nx - 1];
    }
    else if (my_rank == P - 1) {
        // Bottom row
        i = my_ny;
        for (j = 1; j < nx - 1; j++) {
            u_left = my_u[i][j - 1];
            u_right = my_u[i][j + 1];
            u_below = my_u[i - 1][j];

            my_u_new[i][j] = 2 * my_u[i][j]
                + dx_const * (u_left - 2 * my_u[i][j] + u_right)
                + dy_const * (2 * u_below - 2 * my_u[i][j])
                - my_u_prev[i][j];
        }
        // Lower corners
        my_u_new[i][0] = 2 * my_u[i][0]
            + dx_const * (2 * my_u[i][1] - 2 * my_u[i][0])
            + dy_const * (2 * my_u[i - 1][0] - 2 * my_u[i][0])
            - my_u_prev[i][0];

        my_u_new[i][nx - 1] = 2 * my_u[i][nx - 1]
            + dx_const * (2 * my_u[i][nx - 2] - 2 * my_u[i][nx - 1])
            + dy_const * (2 * my_u[i - 1][nx - 1] - 2 * my_u[i][nx - 1])
            - my_u_prev[i][nx - 1];
    }
}