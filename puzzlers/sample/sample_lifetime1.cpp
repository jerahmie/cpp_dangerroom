// sample object lifetime puzzler
#include <iostream>

struct Pobj {
    std::string bi;
    Pobj(const std::string, const std::string b);
    ~Pobj();
};

Pobj::Pobj(const std::string a, const std::string b) {
  std::cout << a;
  bi = b;
}

Pobj::~Pobj() {
  std::cout << bi;
}

  void run() {
    static Pobj object_1("t", "t");
  }

int main(void) {
  run();
  Pobj object_2("i", "e");
  static Pobj object_3("m", "_");
}
