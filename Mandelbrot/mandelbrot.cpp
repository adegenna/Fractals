#include "Iterate.h"
#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <math.h>

// *******************************************************
// MANDELBROT SET CREATION DRIVER PROGRAM
// *******************************************************

int main(int argc, const char* argv[]) {

  // Read in NX x NY grid resolution from stdin
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <XMIN> <XMAX> <YMIN> <YMAX> <NX> <NY>" << std::endl;
    return 1;
  }
  double minCR = atof(argv[1]);
  double maxCR = atof(argv[2]);
  double minCI = atof(argv[3]);
  double maxCI = atof(argv[4]);
  int NX       = atoi(argv[5]);
  int NY       = atoi(argv[6]);

  // Initialize iterate struct, limits on C
  Iterate XN;
  double dCR   = (maxCR - minCR)/(NX - 1);
  double dCI   = (maxCI - minCI)/(NY - 1);

  // Start iterating
  double NORM = 0.0;
  int LIMIT = 1000;
  int K;
  std::vector<std::vector<int> > NUM(NX,std::vector<int>(NY));
  std::string tmp;
  char buf[256];    
  for (int i=0; i<NX; i++) {        // Iterate over NX
    XN.cr_ = minCR + i*dCR;
    for (int j=0; j<NY; j++) {      // Iterate over NY
      XN.ci_ = minCI + j*dCI;
      XN.xr_ = 0.0; XN.xi_ = 0.0;
      for (int k=0; k<LIMIT; k++) { // Iterate until convergence (or divergence)
	func(XN);
	NORM = sqrt(pow(XN.xr_,2) + pow(XN.xi_,2));
	// Check for divergence
	K = k;
	if (NORM >= 2) 
	  break;
      }
      // Record number of iterations til divergence
      NUM[i][j] = K;
    }
  }

  // Output to file
  FILE* outfile;
  //tmp = std::to_string(kk);
  strcpy(buf,"MANDELBROT"); //strcat(buf,tmp.c_str());
  outfile = fopen(buf,"w");
  for (int i=0; i<NX; i++) {
    for (int j=0; j<NY; j++) {
      fprintf(outfile,"%d,",NUM[i][j]);
    }
    fprintf(outfile,"\n");
  }
  fclose(outfile);
  
}
