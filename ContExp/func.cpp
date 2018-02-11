#include "func.h"
#include <stdio.h>
#include <cmath>
#include <stdlib.h>

void func(Iterate& zn) {
  // Function to compute forward iterate of z_{n+1} = exp(z*z0)
  // exp(z*z0) = exp((a+ib)*(c+id)) = exp[ (ac-bd) + i(ad+bc) ] = exp(x+iy)
  // exp(x+iy) = sqrt(x^2+y^2)*[ cos(x) + i*sin(y) ]

  // Compute iterate
  double a = zn.xr_; double b = zn.xi_;
  double c = zn.cr_; double d = zn.ci_;
  double x = a*c - b*d;
  double y = a*d + b*c;

  // exp(x+iy)
  double Z_R = exp(x)*cos(y);
  double Z_I = exp(x)*sin(y);
  
  // Update the iterate object
  zn.xr_ = Z_R;
  zn.xi_ = Z_I;

}
