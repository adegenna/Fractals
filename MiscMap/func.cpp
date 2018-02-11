#include "func.h"
#include <stdio.h>
#include <cmath>
#include <stdlib.h>

void func(Iterate& zn) {
  // Function to compute forward iterate of z_{n+1} = z**z_n

  // Compute iterate
  double c = zn.xr_; double d = zn.xi_;
  double a = zn.cr_; double b = zn.ci_;
  double arg_ab = atan2(b,a);
  
  // Function
  double mod = pow(a*a + b*b,c/2.0)*exp(-d*arg_ab);
  double Z_R = mod*cos(c*arg_ab + 0.5*d*log(a*a + b*b));
  double Z_I = mod*sin(c*arg_ab + 0.5*d*log(a*a + b*b));
  
  // Update the iterate object
  zn.xr_ = Z_R;
  zn.xi_ = Z_I;

}
