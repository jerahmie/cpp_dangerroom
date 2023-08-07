#pragma once
#include <memory>

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
    aTree(std::vector<DataPoint> & data);
    void print_data(void);
    ~aTree() = default;

  private:
    int depth;
    //void build_tree(void);
    std::vector<DataPoint> m_data;
    std::unique_ptr<TreeNode> root = nullptr;
    friend void build_tree(std::shared_ptr<std::vector<DataPoint>> data);
};
