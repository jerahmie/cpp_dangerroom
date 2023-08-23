/*
 *
 *
 */

#include <iostream>
#include "template_function.h"

int main(void) {
  std::cout << "Hello templated function.\n";
  std::string filename, groupname, dataname;
  filename = "afilename.ext";
  groupname = "agroup";
  dataname = "adata";

  std::vector<float> float_data = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  templated_fn(filename, groupname, dataname, float_data);
  std::vector<int> int_data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  templated_fn(filename, groupname, dataname, int_data);
}
