#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex>
#include <fstream>
#include <iostream>
#include <vector>
#include "Iterate.h"
#include "func.h"
#include <omp.h>

// *******************************************************
// MANDELBROT SET CREATION DRIVER PROGRAM
// *******************************************************

int main(int argc, const char* argv[])
{
  // Read in nx x ny grid resolution from stdin
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <XMIN> <XMAX> <YMIN> <YMAX> <nx> <ny>" << std::endl;
    return 1;
  }

  const std::complex<double> zmin(atof(argv[1]), atof(argv[3]));
  const std::complex<double> zmax(atof(argv[2]), atof(argv[4]));

  const double min_real = atof(argv[1]);
  const double max_real = atof(argv[2]);
  const double min_imag = atof(argv[3]);
  const double max_imag = atof(argv[4]);
  const int    nx       = atoi(argv[5]);
  const int    ny       = atoi(argv[6]);

  // Start iterating
  const int    max_steady_state = 100;
  const int    max_periods      = 50;
  const double tol              = 1.0e-15;

  std::vector<std::vector<int> > iters_til_divergence(nx, std::vector<int>(ny));

  const std::complex<double> delta_real((max_real - min_real) / (nx - 1), 0);
  const std::complex<double> delta_imag(0, (max_imag - min_imag) / (ny - 1));

  #pragma omp parallel for
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {

      const std::complex<double> z_coord = zmin + double(i) * delta_real + double(j) * delta_imag;
      std::complex<double>       z_iter  = z_coord;

      for (int k = 0; k < max_steady_state; k++) {  // Iterate to steady-state
        z_iter = name_this_function_better(z_coord, z_iter);
      }

      const std::complex<double> z_steadystate = z_iter;

      int periods = 0;
      while (periods < max_periods) {
        periods++;
        z_iter = name_this_function_better(z_coord, z_iter);
        if (std::abs(z_iter - z_steadystate) < tol) {
          break;
        }
      }

      iters_til_divergence[i][j] = periods;
    }
  }

  // Output to file
  std::ofstream outfile;
  outfile.open("JULIA");

  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      outfile << iters_til_divergence[i][j] << ",";
    }
    outfile << "\n";
  }
  outfile.close();
}
