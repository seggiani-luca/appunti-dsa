int binSearch_it(int A[], int x, int l, int r) {
  int m = (1 + r) / 2;
  while(A[m] != x) {
    if(x < A[m])
      r = m - 1;
    else // x > A[m]
      l = m + 1;
    if(l > r)
      return -1;
    m = (1 + r) / 2;
  }
  return m;
}
