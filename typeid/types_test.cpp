/*
 * file - types_test.cpp
 * Explore typeid exmaple.
 *
 */

#include <iostream>
#include <typeinfo>
#include "H5Cpp.h"

template <typename T> void type_finder(T a) {
  const std::type_info& t_a = typeid(a);
  if (t_a == typeid(int)) {
    std::cout << "Type is integer.\n";
  } else if (t_a == typeid(float)) {
    std::cout << "Type is float.\n";
  } else if (t_a == typeid(double)) {
    std::cout << "Type is double.\n";
  } else {
    std::cout << "Unable to detect type.\n";
  }
}


int main(){
  int i = 0;
  float a = 0.0;
  double b = 0.0;
  type_finder(i);  
  type_finder(a);
  type_finder(b);
}

