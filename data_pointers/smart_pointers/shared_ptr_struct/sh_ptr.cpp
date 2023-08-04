// test creating and dereferening shared pointers.

#include <iostream>
#include <memory>

struct nodeData {
  float a;
};


int main(int argc, char* argv[])
{
  auto nd = nodeData {1};
  std::shared_ptr<nodeData> nds = std::make_shared<nodeData>(nd);
  std::cout << "nd: " << nd.a << '\n';

  std::cout << "nds: " << (*nds).a << '\n';
}
