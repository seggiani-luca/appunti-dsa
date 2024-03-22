#include <iostream>
using namespace std;

void maxCrossingSubarray(int vec[], int beg, int mid, int end, int& begDest, int& endDest, int& givenSum) {
  int left_sum = 0, sum = 0;
  for(int i = mid; i >= beg; i--) {
    sum = sum + vec[i];
    if(sum > left_sum) {
      left_sum = sum;
      begDest = i;
    }
  }

  int right_sum = 0;
  sum = 0;
  for(int i = mid + 1; i < end; i++) {
    sum = sum + vec[i];
    if(sum > right_sum) {
      right_sum = sum;
      endDest = i;
    }
  }
  givenSum = left_sum + right_sum;
}

void maxSubarray(int vec[], int beg, int end, int& begDest, int& endDest, int givenSum) {
  if(beg == end) {
    return;
  } else {
    int mid = (beg + end) / 2;
    int left_low = 0, left_high = 0, left_sum = 0;
    maxSubarray(vec, beg, mid, left_low, left_high, left_sum);
    int right_low = 0, right_high = 0, right_sum = 0;
    maxSubarray(vec, mid + 1, end, right_low, right_high, right_sum);
    int cross_low = 0, cross_high = 0, cross_sum = 0;
    maxCrossingSubarray(vec, beg, mid, end, cross_low, cross_high, cross_sum);
    if(left_sum >= right_sum && right_sum >= cross_sum) {
      begDest = left_low;
      endDest = left_high;
      givenSum = left_sum;
    } else {
      if(right_sum >= left_sum && right_sum >= cross_sum) {
        begDest = right_low;
        endDest = right_high;
        givenSum = right_sum;       
      } else {
        begDest = cross_low;
        endDest = cross_high;
        givenSum = cross_sum;
      }
    }
  }
}

int main() {
  int vec[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
  int beg, end;
  maxSubarray(vec, 0, 16, beg, end, 0);

  for(int i = beg; i <= end; i++) {
    cout << vec[i] << "\t";
  } 
  cout << endl;
  return 0;
}
