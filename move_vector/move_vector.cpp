/*
 * 
 */

#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <algorithm>
#include "move_vector.h"


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

//void build_tree(std::vector<std::reference_wrapper<DataPoint>> rw) {
  //std::sort(this->m_data.begin(), this->m_data.end(), compare_x);
  //  std::cout << "(build_tree) " << d1.x << " , " << d2.x '\n';
//  std::cout << "(build_tree) " << rw.x << '\n';
//}
void build_tree(std::vector<DataPoint> &data) {
    std::sort(data.begin(), data.end(), compare_x);
    int mid = int(data.size()/2) ;
    DataPoint &md = data[mid]; 
    std::cout << "(build_tree) mid: " << md.x << ", " << md.y << '\n';
    std::vector<DataPoint>::iterator l_begin, l_end;
    // left iterators
    l_begin = data.begin();
    l_end = data.begin() + mid;
    std::cout << "(build_tree) data.size() " << data.size() << " , " << std::distance(l_begin, l_end) << '\n';
    std::sort(l_begin, l_end, compare_y);    
}

aTree::aTree(std::vector<DataPoint> &data) : m_data(std::move(data)) {
  build_tree(this->m_data);
}

int main(int argc, char* argv[])
{
  std::cout << "Testing move vector.\n";

  std::vector<std::unique_ptr<DataPoint>> my_data;
  std::vector<DataPoint> data;  
  
  for (int i=0; i<=10; i++) {
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
