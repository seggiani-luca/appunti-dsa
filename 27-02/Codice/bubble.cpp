#include <iostream>
using namespace std;

void scambia(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void bubbleSort(int vett[], int n) {
  for(int i = 0; i < n - 1; i++) {
    for(int j = n-1; j > i; j--) {
      if(vett[j] < vett[j - 1]) scambia(vett[j], vett[j - 1]);
    }
  }
}

void betterBubbleSort(int vett[], int n) {
  for(int i = 0; i < n - 1; i++) {
    bool q = false;
    for(int j = n-1; j > i; j--) {
      if(vett[j] < vett[j - 1]) {
        scambia(vett[j], vett[j - 1]);
        q = true;
      }
    }
    if(q == false) {
      break;
    }
  }
}

int main() {
  int vett[] = {4, 2, 9, 3, 6};
  bubbleSort(vett, 5);
  for(int i = 0; i < 5; i++) {
    cout << vett[i] << " ";
  }
  cout << endl;
  return 0;
}
