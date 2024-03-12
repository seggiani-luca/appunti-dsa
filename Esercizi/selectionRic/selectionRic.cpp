#include <iostream>
using namespace std;

void scambia(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void selectionSort(int* A, int n, int i = 0) {
  if(i == n - 1) return;
  int min = i;
  for(int j = i + 1; j < n; j++) {
    if(A[j] < A[min])
      min = j;
  }
  scambia(A[i], A[min]);
  cout << i << " | " << n - i << endl;
  selectionSort(A, n, ++i);
}

int main() {
  int n = 6;
  int vec[] = {3, 4, 7, 9 , 1, 12};
  selectionSort(vec, n);
  for(int i = 0; i < n; i++) {
    cout << vec[i] << " ";
  }
  cout << endl;
  return 0;
}
