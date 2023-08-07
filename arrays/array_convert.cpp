/*
 * Array_convert.cpp
 * convert a c++ array to a std::vector
 */

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
  std::cout << "Hello array_convert\n";
  // input src
  float arr_in[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  int n = sizeof(arr_in)/sizeof(arr_in[0]);
  std::cout << "n elements: " << n << '\n';
  std::vector<float> vec_out(arr_in, arr_in+n); // convert to vector
  for (auto v : vec_out) {
    std::cout << v << ' ';
  }
  std::cout << '\n';
}
