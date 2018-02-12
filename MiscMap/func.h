#ifndef __FUNC_H__
#define __FUNC_H__

#include "Iterate.h"
#include <complex>

void func(Iterate& xn);

inline std::complex<double> name_this_function_better(const std::complex<double>& z_coord,
                                                      const std::complex<double>& z_iterate)
{
    return std::pow(z_coord, z_iterate);
}

#endif
