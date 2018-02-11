#include "func.h"
#include <stdio.h>
#include <cmath>
#include <stdlib.h>

void func(Iterate& xn) {
  // Function to compute forward iterate of x_{n+1} = x_n^2 + c
  // (a + ib)^2 + (c + id) = (a^2 - b^2 + c) + i*(2ab + d)

  // (a + ib)*((a^2 + i2ab - b^2)) + (c + id)

  // Compute iterate
  double a = xn.xr_; double b = xn.xi_;
  double c = xn.cr_; double d = xn.ci_;
  // Z^2 + c
  double X_2R = (pow(a,2) - pow(b,2)) + c;
  double X_2I = 2*a*b + d;
  // Z^3 + c
  //double X_3R = a*(pow(a,2) - pow(b,2)) - 2*a*pow(b,2) + c;
  //double X_3I = 2*pow(a,2)*b + b*(pow(a,2) - pow(b,2)) + d;
  
  // Update the iterate object
  xn.xr_ = X_2R;
  xn.xi_ = X_2I;

}
