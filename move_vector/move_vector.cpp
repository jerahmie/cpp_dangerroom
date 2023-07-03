/*
 * 
 */

#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <algorithm>

struct DataPoint {
  int x;
  int y;
  DataPoint(int x, int y) {this->x = x; this->y = y;};
};

struct TreeNode {
  DataPoint data;
  std::unique_ptr<TreeNode> node_left = nullptr;
  std::unique_ptr<TreeNode> node_right = nullptr;
};

class aTree {
  public:
    aTree() = delete;
    aTree(const std::vector<DataPoint> & data) = delete;
    aTree(std::vector<DataPoint> &data) : m_data(std::move(data)) {};
    void print_data(void);
    ~aTree() = default;
  private:
    int depth;
    std::vector<DataPoint> m_data;
    std::unique_ptr<TreeNode> root = nullptr;
};

void aTree::print_data() { 
  for ( auto & d : m_data ) {
    std::cout << "(aTree) " << d.x << ", " << d.y << '\n';
  }
}

int main(int argc, char* argv[])
{
  std::cout << "Testing move vector.\n";

  std::vector<std::unique_ptr<DataPoint>> my_data;
  std::vector<DataPoint> data;  
  //std::unique_ptr<std::vector<std::unique_ptr<DataPoint>>> p = std::make_unique<std::vector<std::unique_ptr<DataPoint>>>();
  
  for (int i=0; i<100; i++) {
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
