/*
 * 
 */

#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <algorithm>
#include "move_vector_sh.h"


// compare x data
bool compare_x (const DataPoint &d1, const DataPoint &d2) {
  return (d1.x < d2.x);
}
// compare y data
bool compare_y (const DataPoint &d1, const DataPoint &d2) {
  return (d1.y < d2.y);
}
void aTree::print_data() { 
  for ( auto & d : m_data ) {
    std::cout << "(aTree) " << d.x << ", " << d.y << '\n';
  }
}

void build_tree(std::vector<DataPoint> &data,
                std::vector<DataPoint>::iterator data_begin,
                std::vector<DataPoint>::iterator data_end, int depth) {
  int data_len = std::distance(data_begin, data_end);
  std::cout << "data_len: " << data_len << '\n';
  if (data_len == 0 ) {
    std::cout << "data_len: " << data_len << " data_begin: (" 
              << (*data_begin).x << ", " << (*data_begin).y 
              <<  ") data_end: (" << (*(data_end-1)).x  << ", "
              << (*(data_end-1)).y << ")\n";
  } else { 
    std::sort(data.begin(), data.end(), compare_x);
    int mid = int(std::distance(data_begin, data_end)/2) ;
    std::vector<DataPoint>::iterator end_left, begin_right;
    end_left = data_begin + mid;
    begin_right = data_begin + mid + 1;
    DataPoint &md = data[mid]; 
    std::cout << "(build_tree) mid: " << md.x << ", " << md.y << '\n';
     
    for (auto i=data_begin; i<end_left; i++) {std::cout << '(' << (*i).x << ',' << (*i).y << ") ";}
    std::cout << " | (" << md.x << ',' << md.y << ") | ";
    for (auto i=begin_right; i<data_end; i++) {std::cout << '(' << (*i).x << ',' << (*i).y << ") ";}
    std::cout << '\n';
    build_tree(data, data_begin, end_left, depth++);
    build_tree(data, begin_right, data_end, depth++);
    
  }
}

aTree::aTree(std::vector<DataPoint> &data) : m_data(std::move(data)) {
  build_tree(this->m_data, this->m_data.begin(), this->m_data.end(), 0);
}

int main(int argc, char* argv[])
{
  std::cout << "Testing move vector.\n";

  std::vector<std::unique_ptr<DataPoint>> my_data;
  std::vector<DataPoint> data;  
  
  for (int i=0; i<10; i++) {
    my_data.push_back(std::make_unique<DataPoint>(DataPoint(rand() % 10, rand() %10)));
    data.push_back(DataPoint(rand() % 10, rand() %10));
  }
  for (auto & i : my_data) { 
    std::cout << i->x << ", " << i->y << '\n';
  }
 
  std::vector<std::unique_ptr<DataPoint>> *pd = &my_data;
  auto myTree = aTree(data);
  myTree.print_data();
}
