/*
 * cuberoot.h
 * My implementation of the cubic root calculation using Newton-Raphson 
 * technique. Page 120, Guide to Scientific Computing in C++.
 * 
 */

#ifndef SCIENTIFIC_COMPUTING_CPP_CH5_CUBIC_ROOTS_H
#define SCIENTIFIC_COMPUTING_CPP_CH5_CUBIC_ROOTS_H

/*
 * Calculate cubic roots of following equation using Newton-Raphson iterative
 * technique:
 * f(x) = x^3 - K = 0
 * 
 *      tolerance: tolerance of solution, default = 1e-6
 * max_iterations: maximum iterations, default=100
 */
double cuberoot(double &x, double K,
		double tolerance=1e-6, int max_iterations=100);

#endif /* SCIENTIFIC_COMPUTING_CPP_CH5_CUBIC_ROOTS_H */
