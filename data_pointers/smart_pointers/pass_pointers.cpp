/* 
 * Pass a unique_ptr to a function
 */

#include <iostream>
#include <vector>
#include <memory>

struct VecG {
  std::vector<int> data;
  void print_data(void);
  std::shared_ptr<int> mid(void);
  VecG(void) {};
  VecG(int ndata) : data(ndata,ndata) {};
  //VecG(std::vector<int>);
  //VecG(std::unique_ptr<std::vector<int>>);
};

void VecG::print_data(void){
  std::cout << "(data, " << data.size() << ") ";
  for (auto &i : data) { std::cout << i << ' '; }
  std::cout << '\n';
}

std::shared_ptr<int> VecG::mid(void) {
  int mid_idx = int(data.size()/2);
  std::cout << data[mid_idx] << '\n';
  return std::make_shared<int>(data[mid_idx]);
}

int main(int argc, char* argv[])
{
  std::cout << "Hello World!" << '\n';
  //int *a = new int; 
  std::shared_ptr<int> upa = std::make_shared<int>(6);
  std::cout << "(main) *upa: " << *upa << '\n';

  std::unique_ptr<VecG> myVecG = std::make_unique<VecG>();
  myVecG->data = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  myVecG->print_data();
  myVecG->print_data();
  auto myVecG_mid = myVecG->mid();
  std::cout << "Middle myVecG: " << *myVecG_mid << '\n';
  //myVecG->mid();  

  std::unique_ptr<VecG> vecg2 = std::make_unique<VecG>(100);
  vecg2->print_data();
  vecg2->print_data();
  
  
}
