#include <iostream>
#include "mystructs.h"

int main() {
  mystruct ms {1.2, 3.4, 5};
  std::cout << "Hello mystructs\n";
  std::cout << ms.a << ',' << ms.b << '\n';
}
