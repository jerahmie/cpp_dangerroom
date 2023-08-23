/*
 * file - filter_vector.cpp
 *
 * Filter a STL container using std::copy_if and lambda.
 * https://stackoverflow.com/questions/21204676/modern-way-to-filter-stl-container
 
 */

#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> filter_vector(const std::vector<int> &orig,
                               std::vector<int> &filt) {
  std::vector<int> filtered;
  std::vector<int>::iterator it;
  std::vector<int> a = {6,7};
std::copy_if(orig.begin(), orig.end(), std::back_inserter(filtered),
            [a](int i){return (std::find(a.begin(), a.end(), i) != a.end());}); 
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
