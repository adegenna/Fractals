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
    const double dCR = (max_real - min_real) / (nx - 1);
    const double dCI = (max_imag - min_imag) / (ny - 1);

    // Start iterating
    const int K = 50;
    int periods;
    double tol = 1.0e-15;
    double xr0, xi0;
    std::vector<std::vector<int> > NUM(nx, std::vector<int>(ny));
    std::string tmp;

    for (int i = 0; i < nx; i++) { // Iterate over nx
        XN.cr_ = min_real + i * dCR;
        for (int j = 0; j < ny; j++) { // Iterate over ny
            XN.ci_ = min_imag + j * dCI;
            XN.xr_ = XN.cr_;
            XN.xi_ = XN.ci_;
            for (int k = 0; k < 100; k++) { // Iterate to steady-state
                func(XN);
            }
            xr0 = XN.xr_;
            xi0 = XN.xi_;
            for (int k = 1; k < K; k++) { // Iterate several times to find period
                func(XN);
                periods = k;
                if ((abs(XN.xr_ - xr0) < tol) && (abs(XN.xi_ - xi0) < tol))
                    break;
            }
            // Record number of iterations til divergence
            NUM[i][j] = periods;
        }
    }

    // Output to file
    std::ofstream outfile;
    outfile.open("JULIA");

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            outfile << NUM[i][j] << ",";
        }
        outfile << "\n";
    }
    outfile.close();
}
