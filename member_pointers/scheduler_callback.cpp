#include <iostream>

class MyClass {
  private:
    int a;
  public:
    MyClass(int a) : a(a){};
    ~MyClass() = default;
    int getA(void) { return a; }
    void doublex(void){a *= 2;}
    void triplex(void){a *= 3;}
};

MyClass myobj = MyClass(2);
MyClass* objptr = &myobj;

void fn_wrapper() {
  objptr->triplex();
}

struct Task;

typedef void(*TaskCallback)(struct Task*);
typedef void(*fnptr)();

struct Task{
  int next_time = 0;
  fnptr callback;
};

int main() {
  std::cout << objptr->getA() << '\n';
  objptr->doublex();
  std::cout << objptr->getA() << '\n';
  fnptr getAp = &fn_wrapper;
  
  Task taskhandler = Task {100, getAp};
  taskhandler.callback();
  std::cout << objptr->getA() << '\n';
}
