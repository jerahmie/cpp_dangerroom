/*
 * file - vector_omp.cpp
 * Simple C++ + OpenMP example.
 *
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

int main() {
  int N = 100;
  std::vector<int> data(N);
   
  int t = omp_get_num_procs();
  int threadID = 0;

  std::cout << "Hello vector_omp.\n" << "number of threads: " << t << '\n';
  // initialize data
  #pragma omp for simd
  for (int i=0; i<N; i++) {
    data.at(i) = i+1;
 }

//  #pragma omp for simd
//  for (int i = 0; i<N; i++) {
//    data[i] *= 2; 
//  }

  int sum = 0;
  // process data
  std::cout << "Size: " << data.size() << '\n';
  #pragma omp parallel for reduction(+:sum)
  for (auto &elem : data ) {
    sum += elem;
  }
  // Show results
  std::cout << "sum: " << sum <<  std::endl;

  return 0;
}
