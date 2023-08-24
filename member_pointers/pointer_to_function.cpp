/*
 * file -- pointer_to_function.cpp
 * A simple pointer to a function.
 *
 */

#include <iostream>

int doublex(int a) {
  return 2*a;
}

typedef int(*FPTR)(int);

int main(void) {
  int a = 2;
  //int(*fdoublex)(int) = &doublex;
  FPTR fdoublex = &doublex;
  std::cout << "a: " << a << " doubled: " << doublex(a)  << '\n';
  std::cout << "a: " << a << " doubled: " << (*fdoublex)(a) << std::endl;

}
