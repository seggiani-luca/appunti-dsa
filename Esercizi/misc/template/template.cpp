#include <iostream>
using namespace std;

int i_max(int a, int b) {
  return (a > b) ? a : b;
}

double d_max(double a, double b) {
  return (a > b) ? a : b;
}

template<class T>
T m_max(T a, T b) {
  return (a > b) ? a : b;
}

int main() {
  cout << m_max(0.3, 0.59) << endl;
  cout << m_max(2, 3) << endl;
}
