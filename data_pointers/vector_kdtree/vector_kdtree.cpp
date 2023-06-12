#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

struct MyData {
  double x, y;
  int i;
};

void init_data(std::vector<MyData>& d) {
  // Initialize Data.
  const std::vector<MyData> vals{{1.2, 3.4, 5},
                              {5.6, 7.8, 2},
                              {0.2, 4.6, 6},
                              {1.3, 5.7, 9},
                              {2.4, 6.8, 8},
                              {3.5, 7.9, 7},
                              {4.6, 8.0, 3},
                              {3.1, 7.5, 4},
                              {5.3, 9.7, 0},
                              {8.7, 6.5, 1}};
  for (auto &val : vals) {
    std::cout << val.i << ' ';
    //d.push_back(val);
  }
  std::cout << '\n';
}

void print_vector(const std::vector<MyData>& data) {
  for (auto &d : data) {
    std::cout << d.i << ' ';
  }
  std::cout << '\n';
}

int main(int argc, char* argv[]) 
{
  std::vector<MyData> data;
  MyData d1 {1.1, 2.2, 4};
  std::cout << d1.i << '\n';
  auto &datar = data;
  //init_data(datap);


  std::cout << "data: ";
  init_data(datar);
//  print_vector(datar); 
  //auto &mid = data.at(int(data.size()/2)-1);
 // auto testp = std::make_unique<int>(data[2]);
  //std::cout << "(pre-sort)  mid point: " << mid << ' ' << data.size()/2.0 << '\n';
  //std::sort(data.begin(), data.end());
  //std::cout << "(post-sort) mid point: " << mid << ' ' << data.size()/2.0 << '\n';
  // std::cout << "testp (after): " << *testp << '\n'; // segmentation fault (use after free)
  std::cout << "\nDone.\n"; 

}
