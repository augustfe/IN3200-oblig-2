void one_regular_time_step(int nx, int ny, double dx, double dy, double dt,
  double** u_new, double** u, double** u_prev) {
  int i, j;
  double u_left, u_right, u_below, u_above;
  double dx_const, dy_const;
  dx_const = (dt * dt) / (8 * dx * dx);
  dy_const = (dt * dt) / (8 * dy * dy);

  for (i = 0; i < ny; i++)
    for (j = 0; j < nx; j++) {
      if (j == 0) {
        u_left = u[i][1];
      }
      else {
        u_left = u[i][j - 1];
      }
      if (j == nx - 1) {
        u_right = u[i][nx - 2];
      }
      else {
        u_right = u[i][j + 1];
      }
      if (i == 0) {
        u_below = u[1][j];
      }
      else {
        u_below = u[i - 1][j];
      }
      if (i == ny - 1) {
        u_above = u[ny - 2][j];
      }
      else {
        u_above = u[i + 1][j];
      }
      u_new[i][j] = 2 * u[i][j] + dx_const * (u_left - 2 * u[i][j] + u_right)
        + dy_const * (u_below - 2 * u[i][j] + u_above) - u_prev[i][j];
    }
}
