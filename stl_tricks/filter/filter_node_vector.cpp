/*
 * file - filter_vector.cpp
 *
 * Filter a STL container using std::copy_if and lambda.
 * https://stackoverflow.com/questions/21204676/modern-way-to-filter-stl-container
 
 */

#include <iostream>
#include <algorithm>
#include <vector>

struct node2D {
  double lat;
  double lon;
  int index;
};

std::vector<int> filter_vector(std::vector<int> &orig,
                               std::vector<int> &filt) {
  std::vector<int> filtered;
  std::vector<int>::iterator it;
  std::vector<int> a = {6,7};
  for (it=orig.begin(); it<orig.end(); it++) {
    if (std::find(a.begin(), a.end(), *it) != a.end()) {
      filtered.push_back(it - orig.begin());
    } 
  }
  return filtered;
}

int main()
{
  std::vector<int> orig = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 6, 8, 7, 2, 1, 3, 6};
  std::vector<int> filt = {6,7};
  std::cout << "Hello filter_vector!\n";
  std::vector<int> filtered = filter_vector(orig, filt); 
  std::cout << "\nFiltered Data: \n";
  for (auto i : filtered) {
    std::cout << i << " ";
  }
  std::cout << '\n';
}
