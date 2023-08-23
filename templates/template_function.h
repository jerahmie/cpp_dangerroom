/*
 * filename - template_function.h
 *
 */

#pragma once 
#include <vector>

template <typename T>
void templated_fn(std::string& filename, std::string& group, std::string& data_name, std::vector<T>& data) {
  std::string found_type;
  T val;
  if constexpr (std::is_same<T, int>::value) {
    found_type = "int";
    val = 1;
  } else if constexpr (std::is_same<T, float>::value) {
    found_type = "float";
    val = 1.2;
  } else {
    found_type = "unknown";
  }
  
  std::cout << filename << " | " << group << " | " << data_name << " | "
            << found_type << " | " << val << '\n';
}

