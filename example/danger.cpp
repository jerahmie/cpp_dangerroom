/*
 * danger python interface
 *
 * c++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) -I ../small_data/test scientific_cpp/chapter5/cuberoot danger.cpp -o danger$(python3-config --extension-suffix)
 *
 */

#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include "twice.h"
#include "cuberoot.h"

int add(int i, int j) {
  return i + j;
}


PYBIND11_MODULE(danger, m) {
  m.doc() = "pybind11 example plugin";  // optional module docstring
  m.def("add", &add, "A function that adds two numbers");
  m.def("twice", &twice<int>, "A template-based doubling of integer values.");
  m.def("twice", &twice<double>, "A template-based doubling of double values.");
  m.def("twice", &twice<std::complex<double>>, "Doubling complex values.");
  m.def("cuberoot", &cuberoot, "Calculate the cubic root of function.");
}
