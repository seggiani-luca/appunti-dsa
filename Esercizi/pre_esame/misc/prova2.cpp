#include <iostream>

class base {
public:
  virtual void fun() { std::cout << "base fun" << std::endl; }
};

class deriv : public base {
public:
  void fun() { std::cout << "deriv fun (not fun at all!)" << std::endl; }
};

int main() {
  deriv dv;
  base* b = & dv;
  b->fun();
}
