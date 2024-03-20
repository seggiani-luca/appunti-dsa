#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

int rad;

void printArr(int arr[], int size) {
  for(int i = 0; i < size; i++) {
    cout << arr[i] << "\t";
  }
  cout << endl;
}

void merge(int arr[], int beg, int mid, int end) {
    int iS = beg;
    int iD = mid;

    vector<int> temp;

    while(true) {
        if(arr[iS] <= arr[iD]) {
            temp.push_back(arr[iS++]);
            if(iS >= mid) {
                while(iD < end) temp.push_back(arr[iD++]);
                break;
            }
        } else {
            temp.push_back(arr[iD++]);
            if(iD >= end) {
                while(iS < mid) temp.push_back(arr[iS++]);
                break;
            }
        }
    }

    for(int i = 0; i < temp.size(); i++) {
        arr[i + beg] = temp[i];
    }

}

void mergeSort(int arr[], int beg, int end) {
    if(beg + 1 < end) {
        int mid = (beg + end) / 2;
        mergeSort(arr, beg, mid);
        mergeSort(arr, mid, end);
        merge(arr, beg, mid, end);
    }
}

int main() {
  int n;
  cout << "Inserisci la dimensione dell'array" << endl;
  cin >> n;

  rad = n;

  int* arr = new int[n];
  srand(time(NULL));
  for(int i = 0; i < n; i++) {
    arr[i] = rand() % 99;
  }

  printArr(arr, n);
  mergeSort(arr, 0, n);
  printArr(arr, n);

  delete[] arr;
}
