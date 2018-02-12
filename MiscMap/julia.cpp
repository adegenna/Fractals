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

    // Read in NX x NY grid resolution from stdin
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <XMIN> <XMAX> <YMIN> <YMAX> <NX> <NY>" << std::endl;
        return 1;
    }
    double minCR = atof(argv[1]);
    double maxCR = atof(argv[2]);
    double minCI = atof(argv[3]);
    double maxCI = atof(argv[4]);
    int NX = atoi(argv[5]);
    int NY = atoi(argv[6]);

    // Initialize iterate struct, limits on C
    Iterate XN;
    double dCR = (maxCR - minCR) / (NX - 1);
    double dCI = (maxCI - minCI) / (NY - 1);

    // Start iterating
    double NORM = 0.0;
    double NORM0;
    int LIMIT = 1000;
    int K = 50;
    int periods;
    double tol = 1.0e-15;
    double xr0, xi0;
    std::vector<std::vector<int> > NUM(NX, std::vector<int>(NY));
    std::string tmp;
    char buf[256];
    for (int i = 0; i < NX; i++) { // Iterate over NX
        XN.cr_ = minCR + i * dCR;
        for (int j = 0; j < NY; j++) { // Iterate over NY
            XN.ci_ = minCI + j * dCI;
            XN.xr_ = XN.cr_;
            XN.xi_ = XN.ci_;
            for (int k = 0; k < 100; k++) { // Iterate to steady-state
                func(XN);
            }
            xr0 = XN.xr_;
            xi0 = XN.xi_;
            for (int k = 1; k < K; k++) { // Iterate several times to find period
                func(XN);
                NORM = sqrt(pow(XN.xr_, 2) + pow(XN.xi_, 2));
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

    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            outfile << NUM[i][j] << ",";
        }
        outfile << "\n";
    }
    outfile.close();
}
