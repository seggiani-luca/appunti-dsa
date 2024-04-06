#include <iostream>
using namespace std;

void scambia(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void selectionSort(int vett[], int n) {
  for(int i = 0; i < n - 1; i++) {
    int m = i;
    for(int j = i + 1; j < n; j++) {
      if(vett[j] < vett[m]) m = j;
    }
    scambia(vett[m], vett[i]);
  }
}

int main() {
  int vett[] = {5, 3, 2, 6, 1};
  selectionSort(vett, 5);
  for(int i = 0; i < 5; i++) {
    cout << vett[i] << " ";
  }
  cout << endl;
  return 0;
}
