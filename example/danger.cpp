/*
 * danger python interface
 */

#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include "twice.h"

int add(int i, int j) {
  return i + j;
}



PYBIND11_MODULE(danger, m) {
  m.doc() = "pybind11 example plugin";  // optional module docstring
  m.def("add", &add, "A function that adds two numbers");
  m.def("twice", &twice<int>, "A template-based doubling of integer values.");
  m.def("twice", &twice<double>, "A template-based doubling of double values.");
  m.def("twice", &twice<std::complex<double>>, "Doubling complex values.");
}
