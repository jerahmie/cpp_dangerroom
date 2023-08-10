/*
 * Use iterators to split a vector.
 *
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>

void print_split(std::vector<int>& v,
                 std::vector<int>::iterator it_begin,
                 std::vector<int>::iterator it_end, int depth) {
  size_t vec_len = std::distance(it_begin, it_end);
  if (vec_len == 1 ) {
  std::cout << "depth: " << depth <<  " vec_len: " << vec_len << " : " << *it_begin << '\n';
  } else {
    std::size_t mid_dist = round(((double)vec_len)/2.0); 
    std::size_t mid_id = distance(std::begin(v), it_begin + mid_dist - 1);
    std::vector<int>::iterator it_end_left, it_begin_right;
    it_end_left = it_begin + mid_dist-1;
    it_begin_right = it_begin + mid_dist;
    std::cout << ">> depth: " << depth << " v[mid_id]: " << v[mid_id] << '\n';
    if (depth == 1) {
      std::cout << "depth: " << depth << ": "
                << " v[mid_id]: " << v[mid_id]
                << ", vec_len: "<< vec_len << " mid_dist: " << mid_dist << " | ";
      for(auto i=it_begin; i<it_end; i++) {
        std::cout << *i << " ";
      }
      std::cout << '\n';
    }
    depth++;
    if (distance(it_begin, it_end_left) > 0) {
    print_split(v, it_begin, it_end_left, depth);
    }
    if (distance(it_begin_right, it_end) > 0) {
      print_split(v, it_begin_right, it_end, depth);
    }
    
  }
}


int main(int argc, char* argv[])
{
  std::vector<int> v9 = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
  std::vector<int> v10 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  print_split(v9, v9.begin(), v9.end(), 0);
}
