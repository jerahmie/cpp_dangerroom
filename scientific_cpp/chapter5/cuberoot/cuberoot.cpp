/*
 * Calculate the cubic root of a function using Newton-Raphson technique.
 */

#include <cmath>
#include <iostream>
#include "cuberoot.h"


double cuberoot(double &x, double K,
		double tolerance, int max_iterations)
{
  int iteration = 0;
  double residual = 1.0;
  double x_next = 0.0;
  while ( (iteration <= max_iterations) && (std::abs(residual) >= tolerance) )
    {
      x_next = x - (std::pow(x,3) - K)/(3*std::pow(x,2));
      residual = x_next-x;
      x = x_next;  // update x
      iteration++;
      //      std::cout << iteration << ", " <<  x << ", " << residual << '\n';
    }
  return x;
}
