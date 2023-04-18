void one_fast_time_step(int nx, int ny, double dx, double dy, double dt,
  double** u_new, double** u, double** u_prev) {
  int i, j;
  double dx_const, dy_const;
  dx_const = (dt * dt) / (8 * dx * dx);
  dy_const = (dt * dt) / (8 * dy * dy);

  // Everything except top and bottom row
  for (i = 1; i < ny - 1; i++) {
    u_new[i][0] = 2 * u[i][0] + dx_const * (2 * u[i][1] - 2 * u[i][0])
      + dy_const * (u[i - 1][0] - 2 * u[i][0] + u[i + 1][0]) - u_prev[i][0];
    for (j = 1; j < nx - 1; j++) {
      u_new[i][j] = 2 * u[i][j] + dx_const * (u[i][j - 1] - 2 * u[i][j] + u[i][j + 1])
        + dy_const * (u[i - 1][j] - 2 * u[i][j] + u[i + 1][j]) - u_prev[i][j];

    }
    u_new[i][nx - 1] = 2 * u[i][nx - 1] + dx_const * (2 * u[i][nx - 2] - 2 * u[i][nx - 1])
      + dy_const * (u[i - 1][nx - 1] - 2 * u[i][nx - 1] + u[i + 1][nx - 1]) - u_prev[i][nx - 1];
  }

  // Bottom and top row: i = 0, i = ny - 1
  for (j = 1; j < nx - 1; j++) {
    u_new[0][j] = 2 * u[0][j] + dx_const * (u[0][j - 1] - 2 * u[0][j] + u[0][j + 1])
      + dy_const * (2 * u[1][j] - 2 * u[0][j]) - u_prev[0][j];
    // Test for bottom row: i = ny - 1
    u_new[ny - 1][j] = 2 * u[ny - 1][j] + dx_const * (u[ny - 1][j - 1] - 2 * u[ny - 1][j] + u[ny - 1][j + 1])
      + dy_const * (2 * u[ny - 2][j] - 2 * u[ny - 1][j]) - u_prev[ny - 1][j];
  }

  // Calculating corners
  u_new[0][0] = 2 * u[0][0] + dx_const * (2 * u[0][1] - 2 * u[0][0])
    + dy_const * (2 * u[1][0] - 2 * u[0][0]) - u_prev[0][0];

  u_new[0][nx - 1] = 2 * u[0][nx - 1] + dx_const * (2 * u[0][nx - 2] - 2 * u[0][nx - 1])
    + dy_const * (2 * u[1][nx - 1] - 2 * u[0][nx - 1]) - u_prev[0][nx - 1];

  u_new[ny - 1][0] = 2 * u[ny - 1][0] + dx_const * (2 * u[ny - 1][1] - 2 * u[ny - 1][0])
    + dy_const * (2 * u[ny - 2][0] - 2 * u[ny - 1][0]) - u_prev[ny - 1][0];

  u_new[ny - 1][nx - 1] = 2 * u[ny - 1][nx - 1] + dx_const * (2 * u[ny - 1][nx - 2] - 2 * u[ny - 1][nx - 1])
    + dy_const * (2 * u[ny - 2][nx - 1] - 2 * u[ny - 1][nx - 1]) - u_prev[ny - 1][nx - 1];
}
