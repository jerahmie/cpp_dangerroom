/*
 * Pointer to member function.
 *
 */

#include <iostream>
#include <functional>

typedef void(*TaskCallback)(struct MyStruct *);

typedef void (*myfun)(void);

struct MyStruct {
  myfun fn;
};

void somefun() {
  std::cout << "somefun" << std::endl;
}

class MyClass {
  private:

  public:
  int a;
  MyClass(int a) : a(a) {};
  ~MyClass() = default;
  int getA(void) { return a; };
  void doubleA(void) { a*=2; };
};

int main(int argc, char* argv[]) {
  //void (MyClass::* ptfdoubleA) (void) = &MyClass::doubleA;
  MyClass m5 = MyClass(5);
  //(m5.*ptfdoubleA)();
  MyClass m2 = MyClass(2);
  //(m2.*ptfdoubleA)();
  std::cout << "Test pointer to member function.\n";
  std::cout << m5.getA() << std::endl;
  std::cout << m2.getA() << std::endl;

   
  MyStruct s1 = MyStruct {&somefun}; 
  s1.fn();
  //MyStruct s2 = MyStruct { &(m5.doubleA) };
  //MyStruct s2 = MyStruct {std::bind(&MyClass::doubleA, m2)};
}
