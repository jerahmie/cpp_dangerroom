/*
 * file - simple_omp.cpp
 * Simple C++ + OpenMP example.
 *
 */

#include <iostream>
#include <chrono>
#include <omp.h>

int main() {
  int N = 100;
  int data[N];
  int t = omp_get_num_procs();
  int threadID = 0;

  std::cout << "Hello simple_omp.\n" << "number of threads: " << t << '\n';
  // initialize data
  #pragma omp parallel for private(threadID)
  for (int i=0; i<N; i++) {
    data[i] = i+1;
  }

  int sum = 0;
  // process data
  #pragma omp parallel for reduction(+:sum)
  for (int i=0; i<N; i++) {
    sum += data[i];
  }

  // Show results
  std::cout << "sum: " << sum <<  std::endl;

  return 0;
}
