#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

int getMax(int A[], int n) {
  int max = A[0];
  for(int i = 1; i < n; i++) {
    if(A[i] > max) max = A[i];
  }
  return max;
}

void bucketSort(int A[], int n, int k) {
  vector<vector<int>> buckets;
  buckets.reserve(k);
  int max = 1 + getMax(A, n);
  for(int i = 0; i < n; i++) {
    buckets[floor(k * A[i] / max)].push_back(A[i]);
  }
  for(int i = 0; i < k; i++) {
    sort(buckets[i].begin(), buckets[i].end());
  }
  int count = 0;
  for(int i = 0; i < k; i++) {
    for(int j = 0; j < buckets[i].size(); j++) {
      A[count] = buckets[i][j];
      count++;
    }
  }
}

int main() {
  int A[] = {52, 25, 32, 84, 6, 3, 0};
  bucketSort(A, 7, 10);
  for(int i = 0; i < 7; i++) {
    cout << A[i] << " ";
  }
  cout << endl;
}
