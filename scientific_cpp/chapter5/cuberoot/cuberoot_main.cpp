/*
 * Calculate the cubic root of a function using Newton-Raphson technique.
 */

#include <iostream>
#include "cuberoot.h"


int main(int argc, char* argv[])
{
  double x = 1.0;
  double K = 12.0;
  std::cout << "Calculating cubic roots... \n";
  std::cout << "result: " << cuberoot(x, K) << "\n";
  return 0;
}
