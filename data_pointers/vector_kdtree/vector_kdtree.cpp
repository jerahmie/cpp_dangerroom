#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

void init_data(std::vector<int>& d) {
  // Initialize Data.
  const std::vector<int> vals{5, 2, 6, 9, 8, 7, 3, 4, 0, 1};
  for (auto &val : vals) {
    std::cout << val << ' ';
    d.push_back(val);
  }
  std::cout << '\n';
}

void print_vector(const std::vector<int>& data) {
  for (auto &i : data) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

int main(int argc, char* argv[]) 
{
  std::vector<int> data;
  auto &datar = data;
  //init_data(datar);


  std::cout << "data: ";
  init_data(datar);
  print_vector(datar); 
  auto &mid = data.at(int(data.size()/2)-1);
  std::cout << "(pre-sort)  mid point: " << mid << ' ' << data.size()/2.0 << '\n';
  std::sort(data.begin(), data.end());
  std::cout << "(post-sort) mid point: " << mid << ' ' << data.size()/2.0 << '\n';
  std::cout << "\nDone.\n"; 

}
