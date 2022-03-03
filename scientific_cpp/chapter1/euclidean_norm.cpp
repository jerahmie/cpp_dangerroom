#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <functional>
#include <numeric>
#include <cassert>


// calculate the dot (inner) product of two vectors
double dot_product(const std::vector<double> &v1,
		   const std::vector<double> &v2)
{
  assert(v1.size() == v2.size());
  
  return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0);
}

// calculate the Euclidean (L2) norm 
double euclidean_norm(const std::vector<double> &v1,
		      const std::vector<double> &v2)
{
  std::vector<double> v3(v1.size());
  // subtract v1 - v2
  std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(),
		 std::minus<double>());

  // square 
  std::transform(v3.begin(), v3.end(), v3.begin(),
		 [](double d) -> double { return d * d;});

  // sum and sqrt
  return sqrt(std::accumulate(v3.begin(), v3.end(), 0.0));
}

int main(int argc, char* argv[]){
  const std::vector<double> v1{1.0, 2.0, 3.0};
  const std::vector<double> v2{4.0, 5.0, 6.0};

  std::cout << "Calculate the Dot Product: ";
  auto vdot = dot_product(v1, v2);
  std::cout << vdot << "\n";
  std::cout << "\nCalculate Euclidean Norm of two Vectors...\n";
  std::cout << euclidean_norm(v1, v2) << "\n";
}
