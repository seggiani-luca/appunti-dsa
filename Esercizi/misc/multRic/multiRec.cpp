#include <iostream>
using namespace std;

int mult(int a, int b) {
  if(b == 0) return 0;
  return a + mult(a, b - 1);
}

int main() {
  int a, b;
  cin >> a >> b;
  cout << mult(a, b) << endl;
}
