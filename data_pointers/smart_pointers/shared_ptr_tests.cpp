#include <iostream>
#include <memory>

int main(int argc, char* argv[]) 
{
  std::shared_ptr<double> my_ptr = std::make_shared<double>(100);
  std::cout << "my_ptr (before reset): " << *my_ptr << '\n';
  my_ptr.reset(); 
  my_ptr = nullptr;
  std::cout << "my_ptr (after reset): " << my_ptr << '\n';
}
