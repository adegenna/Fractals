#include "Iterate.h"
#include "func.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

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
    const double min_real = atof(argv[1]);
    const double max_real = atof(argv[2]);
    const double min_imag = atof(argv[3]);
    const double max_imag = atof(argv[4]);
    const int nx = atoi(argv[5]);
    const int ny = atoi(argv[6]);

    // Initialize iterate struct, limits on C
    Iterate XN;
    const double delta_real = (max_real - min_real) / (nx - 1);
    const double delta_imag = (max_imag - min_imag) / (ny - 1);

    // Start iterating
    const int max_periods = 50;
    const double tol = 1.0e-15;

    std::vector<std::vector<int> > iters_til_divergence(nx, std::vector<int>(ny));

    for (int i = 0; i < nx; i++) {
        XN.cr_ = min_real + i * delta_real;
        for (int j = 0; j < ny; j++) {
            XN.ci_ = min_imag + j * delta_imag;
            XN.xr_ = XN.cr_;
            XN.xi_ = XN.ci_;
            for (int k = 0; k < 100; k++) { // Iterate to steady-state
                func(XN);
            }
            double xr0 = XN.xr_;
            double xi0 = XN.xi_;
            int periods = 0;
            for (int k = 1; k < max_periods; k++) { // Iterate several times to find period
                func(XN);
                periods = k;
                if ((abs(XN.xr_ - xr0) < tol) && (abs(XN.xi_ - xi0) < tol))
                    break;
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
