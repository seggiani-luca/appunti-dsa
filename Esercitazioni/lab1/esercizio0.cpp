#include <iostream>
using namespace std;

void stampaVett(int* vett, int dim) {
  for(int i = 0; i < dim; i++) {
    cout << *(vett + i) << " ";
  }
  cout << endl;
}

int main() {
  const int dim = 10;
  int vett[dim] = { 1, 3, -5, 7, 8, 9, -12, 3, 4, 1 };

  stampaVett(vett, dim);
}
