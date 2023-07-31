/*
 * python_interop
 * Test python interoperability with C++
 */

#include <iostream>
#include <cassert>
#include "Python.h"


int main(int argc, char* argv[])
{
  std::cout << "Hello World!\n";
  Py_Initialize();
  int status = Py_FinalizeEx();
  assert(status == 0);
}
