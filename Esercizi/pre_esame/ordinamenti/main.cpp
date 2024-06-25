#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
#include "heap.h"
using namespace std;

//Utilità
const int ITEMS = 12;
int k; //hack per i non comparativi

struct item {
  const char* name;
  void (*fun)(int*, int, int);
};

void stampa(int* vett, int dim) {
  for(int i = 0; i < dim; i++) {
    cout << vett[i] << "\t";
  }
  cout << endl;
}

void query_integer(int& num, int minBound = 0, int maxBound = INFINITY) {
  while(true) {
    std::cin >> num;
    bool fail = false;

    if(cin.fail()) {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
      cout << "Valore fuori dal dominio ammesso." << endl;
      fail = true;
    }

    if(num < minBound || num > maxBound) {
      cout << "Valore fuori dai bound." << endl;
      fail = true;
    }

    if(!fail) break;
  }
}

inline void stampa_exchange(int* v, int i1, int i2) {
  cout << "\tExchange fra " << i1 << " (valore " << v[i1] << ") e " << i2 << " (valore " << v[i2] << ")" << endl;
}

inline void stampa_passo(int* v, int n, int passo) {
  cout << "A fine passo\t" << passo << ": " << endl;
  stampa(v, n);
}

//ALGORITMI DI ORDINAMENTO
//1) Algoritmi n^2
void exchange(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void selection_sort(int* v, int n, int verbose) {
  for(int i = 0;  i < n - 1; i++) {
    int min = i;
    for(int j = i + 1; j < n; j++)
      if(v[j] < v[min])
        min = j;
    if(verbose >= 2) stampa_exchange(v, min, i); 
    exchange(v[min], v[i]);
    if(verbose >= 1) stampa_passo(v, n, i);
  }
}

void bubble_sort(int* v, int n, int verbose) {
  for(int i = 0; i < n - 1; i++) {
    for(int j = n - 1; j > i; j--)
      if(v[j] < v[j - 1]) {
        if(verbose >= 2) stampa_exchange(v, j, j - 1);
        exchange(v[j], v[j - 1]);
      }
    if(verbose >= 1) stampa_passo(v, n, i); 
  }
}

void bubble_sort_optimized(int* v, int n, int verbose) {
  for(int i = 0; i < n - 1; i++) {
    bool flag = false;
    for(int j = n - 1; j > i; j--) {
      if(v[j] < v[j - 1]) {
        if(verbose >= 2) stampa_exchange(v, j, j - 1);
        exchange(v[j], v[j - 1]);
        flag = true;
      }
    }
    if(!flag) {
      if(verbose >= 1) cout << "Early return a " << i << endl;
      return; 
    } 
    if(verbose >= 1) stampa_passo(v, n, i); 
  }
}

//2) Algoritmi n^2 ricorsivi
void selection_sort_recursive(int* v, int min, int max, int& verbose) {
  if(min > max - 2) return;
  int minPoint = min;
  for(int i = min + 1; i < max; i++) {
    if(v[i] < v[minPoint])
      minPoint = i;
  }
  if(verbose >= 2) stampa_exchange(v, min, minPoint); 
  exchange(v[min], v[minPoint]);
  if(verbose >= 1) stampa_passo(v, max, min); 
  selection_sort_recursive(v, min + 1, max, verbose);
}

void selection_sort_recursive_wrapper(int* v, int n, int verbose) {
  selection_sort_recursive(v, 0, n, verbose);
}

void bubble_sort_recursive(int* v, int min, int max, int& verbose) {
  if(min > max - 2) return;
  for(int i = max - 1; i > min; i--) {
    if(v[i] < v[i - 1]) {
      if(verbose >= 2) stampa_exchange(v, i, i - 1);
      exchange(v[i], v[i - 1]);
    }
  }
if(verbose >= 1) stampa_passo(v, max, min); 
  bubble_sort_recursive(v, min + 1, max, verbose);
}

void bubble_sort_recursive_wrapper(int* v, int n, int verbose) {
  bubble_sort_recursive(v, 0, n, verbose);
}

void bubble_sort_recursive_optimized(int* v, int min, int max, int& verbose) {
  if(min > max - 2) return;
  bool flag = false;
  for(int i = max - 1; i > min; i--) {
    if(v[i] < v[i - 1]) {
      if(verbose >= 2) stampa_exchange(v, i, i - 1);
      exchange(v[i], v[i - 1]);
      flag = true;
    }
  }
  if(!flag) {
    if(verbose >= 1) cout << "Early return a " << min << endl;
    return;
  }
  if(verbose >= 1) stampa_passo(v, max, min); 
  bubble_sort_recursive_optimized(v, min + 1, max, verbose); 
}

void bubble_sort_recursive_optimized_wrapper(int* v, int n, int verbose) {
  bubble_sort_recursive_optimized(v, 0, n, verbose);
}

//3) Algoritmo mergesort
void merge(int* a, int* b, int min, int midpoint, int max, int& verbose) {
  if(verbose >= 2) cout << " - - - - " << endl << "Scorrimento merge da " << min << " a max " << max << " con midpoint " << midpoint << endl;
  int i = min, j = midpoint;
  for(int k = min; k < max; k++) {
    if(verbose >= 2) cout << "Passo " << k << ": ";
    if(i < midpoint && (j >= max || a[i] <= a[j])) {
      b[k] = a[i];
      if(verbose >= 2) cout << "Scelto i (primo vettore) ovvero " << a[i] << endl;
      i++;
    } else {
      b[k] = a[j];
      if(verbose >= 2) cout << "Scelto j (secondo vettore) ovvero " << a[j] << endl;
      j++;
    }
  }
  if(verbose >= 2) cout << " - - - - " << endl;
}

void mergesplit_topdown(int* a, int* b, int min, int max, int& verbose, int depth) {
  if(min > max - 2) {
    for(int i = 0; i < depth; i++) cout << "\t";
    cout << "Ricorsione troncata a min " << min << " e max " << max << endl;
    return;
  } 
  int midpoint = (min + max) / 2;
  if(verbose >= 1) {
    for(int i = 0; i < depth; i++) cout << "\t";
    cout << "Preso intervallo da " << min << " a " << max << ", scelto midpoint " << midpoint << endl;
  }
  mergesplit_topdown(b, a, min, midpoint, verbose, depth + 1);
  mergesplit_topdown(b, a, midpoint, max, verbose, depth + 1);

  if(verbose >= 1) {
    for(int i = 0; i < depth; i++) cout << "\t";
    cout << "Merge da min " << min << " a max " << max << " con midpoint " << midpoint << endl;
  }
  merge(a, b, min, midpoint, max, verbose);
}

void merge_sort_topdown_wrapper(int* v, int n, int verbose) {
  int aux[n];
  for(int i = 0; i < n; i++) {
    aux[i] = v[i];
  }
  mergesplit_topdown(aux, v, 0, n, verbose, 0);   
}

void merge_sort_bottomup(int* v, int n, int verbose) {
  int aux[n]; int* b = aux;
  for(int window = 1; window < n; window *= 2) {
    if(verbose >= 1) cout << "Window ha dimensione " << window << endl; 
    for(int i = 0; i < n; i += 2 * window) {
      int min = i;
      int midpoint = std::min(i + window, n);
      int max = std::min(i + 2 * window, n);
      if(verbose >= 1) cout << "Merge da min " << min << " a max " << max << " con midpoint " << midpoint << endl;
      merge(v, b, min, midpoint, max, verbose);
    }
    int* temp = b;
    b = v;
    v = temp;
    if(verbose >= 2) cout << "Scambio fra array" << endl;
  }
  if(verbose >= 2) {
    cout << "Stampo vettore primario e ausiliario:" << endl;
    stampa(v, n);
    stampa(b, n);
  }

  for(int i = 0; i < n; i++) {
    b[i] = v[i];
  }
}

//4) Algoritmo quicksort
void quicksort(int* v, int min, int max, int& verbose, int depth) {
  int pivot = v[(min + max) / 2];
  int h = min, k = max;
  while(h <= k) {
    while(v[h] < pivot) h++;
    while(v[k] > pivot) k--;
    if(h > k) break;
    if(verbose >= 2) stampa_exchange(v, h, k);
    exchange(v[h], v[k]);
    h++; k--;
  }
  if(verbose >= 1) {
    for(int i = 0; i < depth; i++) cout << "\t";
    cout << "A profondità " << depth << ", chiamo quicksort da " << min << " a " << k << " (a sinistra)" << endl;
  }
  if(min < k) quicksort(v, min, k, verbose, depth + 1);
  if(verbose >= 1) {
    for(int i = 0; i < depth; i++) cout << "\t";
    cout << "A profondità " << depth << ", chiamo quicksort da " << h << " a " << max << " (a destra)" << endl;
  }
  if(max > h) quicksort(v, h, max, verbose, depth + 1);
}

void quicksort_wrapper(int* v, int n, int verbose) {
  quicksort(v, 0, n - 1, verbose, 0);
}

//5) Algoritmo heapsort
void heapsort(int* v, int n, int verbose) {
  Heap<int> heap(v, n);
  if(verbose >= 1)
    cout << "Creato heap: " << heap << endl;
  for(int i = n - 1; i >= 0; i--) {
    v[i] = heap.extract();
    if(verbose >= 2) {
      cout << "Passo " << i << ", estratto " << v[i] << " con heap rimasto " << heap << endl;
    }
  }
}

//6) Algoritmi non basati sul confronto
void counting_sort(int* v, int n, int verbose) {
  vector<int> occur(k, 0);
  for(int i = 0; i < n; i++) {
    occur[v[i]]++;
    if(verbose >= 1) cout << "Trovato " << v[i] << endl;
  }
  int count = 0;
  for(int i = 0; i < occur.size(); i++)
    while(occur[i] > 0) {
      v[count] = i;
      occur[i]--;
      count++;
    }
}

void radix_sort(int* v, int n, int verbose) {
  vector<queue<int>> buckets(10);
  for(int j = 1; j < k + 1; j++) {
    if(verbose >= 1) cout << "Passo " << j << endl;
    for(int i = 0; i < n; i++) {
      int digit = v[i] % (int) pow(10, j);
      digit /= pow(10, j - 1);
      buckets[digit].push(v[i]);
      if(verbose >= 2)
        cout << "Per l'elemento " << v[i] << " ho preso la cifra " << digit << endl; 
    }
    int count = 0;
    for(int i = 0; i < 10; i++) {
      while(!buckets[i].empty()) {
        v[count] = buckets[i].front();
        buckets[i].pop();
        count++;
      }
    }
    if(verbose >= 1)
      stampa_passo(v, n, j);
  }
}

int main(int argc, char** argv) {
  srand(time(nullptr)); 

  cout << "Dimensione?" << endl;
  int dim;
  query_integer(dim);
  int vett[dim];
  
  item menu[ITEMS] = {  "selection_sort",                   selection_sort,
                        "selection_sort_recursive",         selection_sort_recursive_wrapper,
                        "bubble_sort",                      bubble_sort,
                        "bubble_sort_optimized",            bubble_sort_optimized,
                        "bubble_sort_recursive",            bubble_sort_recursive_wrapper,
                        "bubble_sort_recursive_optimized",  bubble_sort_recursive_optimized_wrapper,
                        "merge_sort_topdown",               merge_sort_topdown_wrapper,
                        "merge_sort_bottomup",              merge_sort_bottomup,
                        "quicksort",                        quicksort_wrapper,
                        "heapsort",                         heapsort,
                        "counting_sort",                    counting_sort,
                        "radix_sort",                       radix_sort};

  cout << "Ordinamento?" << endl;
  for(int i = 0; i < ITEMS; i++) {
    cout << i << " - " << menu[i].name << endl;
  }
  int c;
  query_integer(c, 0, ITEMS - 1);

  if(c >= 10) {
    cout << "Valore k?"  << endl;
    query_integer(k);
  } else {
    k = 99;
  }

  cout << "Livello di verbosità?" << endl;
  int v;
  query_integer(v);
  
  if(c == 11)
    for(int i = 0; i < dim; i++)
      vett[i] = rand() % (int) pow(10, k);
  else for(int i = 0; i < dim; i++)
    vett[i] = rand() % k;
  cout << "Prima dell'ordinamento: " << endl;
  stampa(vett, dim);

  menu[c].fun(vett, dim, v);  

  cout << "Dopo l'ordinamento: " << endl;
  stampa(vett, dim);
 
  return 0;
}
