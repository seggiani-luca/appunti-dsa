#include <iostream>
#include <vector>

using namespace std;

void combine(int arr[], int start, int mid, int end) {
  int iSx = start, iDx = mid;
  vector<int> tempResult;
  while(true) {
    if(arr[iSx] < arr[iDx]) {
      cout << "pushback in " << arr[iSx] << " [" << iSx << "]" << endl;;
      tempResult.push_back(arr[iSx++]);
      if(iSx >= mid) {
        cout << "iSx at final position." << endl;
        while(iDx < end) {
          tempResult.push_back(arr[iDx++]);
        }
        break;
      }
    } else {
      cout << "pushback in " << arr[iDx] << " [" << iDx << "]" << endl;
      tempResult.push_back(arr[iDx++]);
      if(iDx >= end) {
        cout << "iDx at final position." << endl; 
        while(iSx < mid) {
          tempResult.push_back(arr[iSx++]);
        }
        break;
      }
    }
  }

  for(int i = 0; i < tempResult.size(); i++) {
    arr[i] = tempResult[i];
  }
}

//utility
void printArr(int arr[], int size) {
  for(int i = 0; i < size; i++) {
    cout << arr[i] << "\t";
  }
  cout << endl;
}

int main() {
  int N;
  cout << "Inserisci la dimensione dell'array" << endl;
  cin >> N;
  int* arr = new int[N];
  
  for(int i = 0; i < N/2; i++) {
    arr[i] = i + N/2;
  }
  for(int i = N/2; i < N; i++) {
    arr[i] = i - N/2;
  }

  printArr(arr, N);

  combine(arr, 0, N/2, N);
  
  printArr(arr, N);
  
  delete[] arr;

  return 0;
}
