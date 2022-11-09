#include <iostream>
#include <vector>
using std::cin, std::cout, std::pair, std::swap, std::vector;

const int kMOD = 10'000'000 + 4321;

void BubbleSort(vector<int>& a, size_t lhs, size_t rhs);
int QuickSelect(vector<int>& a, size_t k, size_t lhs, size_t rhs);
void GetArrayOfMedian(vector<int>& a, vector<int>& ans, size_t lhs, size_t rhs);
pair<size_t, size_t> Partition(vector<int>& a, size_t lhs, size_t rhs,
                               int pivot);

int main() {
  int n;
  size_t k;
  cin >> n >> k;
  --k;
  vector<int> a(n);
  cin >> a[0] >> a[1];
  for (int i = 2; i < n; ++i) {
    a[i] = (a[i - 1] * 123 + a[i - 2] * 45) % kMOD;
  }
  cout << QuickSelect(a, k, 0, a.size());
}

pair<size_t, size_t> Partition(vector<int>& a, size_t lhs, size_t rhs,
                               int pivot) {
  size_t ans_l = lhs, ans_r = lhs;
  for (size_t i = lhs; i < rhs; ++i) {
    if (a[i] < pivot) {
      swap(a[i], a[lhs]);
      ++lhs;
      ans_l = lhs;
    }
  }
  for (size_t i = lhs; i < rhs; ++i) {
    if (a[i] == pivot) {
      swap(a[i], a[lhs]);
      ans_r = lhs;
      ++lhs;
    }
  }
  return {ans_l, ans_r};
}

int QuickSelect(vector<int>& a, size_t k, size_t lhs, size_t rhs) {
  if (rhs - lhs <= 1) {
    return a[lhs];
  }
  vector<int> medians;
  GetArrayOfMedian(a, medians, lhs, rhs);
  int m = QuickSelect(medians, medians.size() >> 1, 0, medians.size());
  pair<size_t, size_t> p = Partition(a, lhs, rhs, m);

  if (k < p.first) {
    return QuickSelect(a, k, lhs, p.first);
  }
  if (k <= p.second) {
    return m;
  }
  return QuickSelect(a, k, p.second + 1, rhs);
}
void BubbleSort(vector<int>& a, size_t lhs, size_t rhs) {
  for (size_t i = rhs; i > lhs; --i) {
    for (size_t j = lhs + 1; j < i; ++j) {
      if (a[j - 1] > a[j]) {
        std::swap(a[j - 1], a[j]);
      }
    }
  }
}
void GetArrayOfMedian(vector<int>& a, vector<int>& ans, size_t lhs,
                      size_t rhs) {
  for (size_t i = lhs; i < rhs; i += 5) {
    BubbleSort(a, i, std::min(i + 5, rhs));
    ans.push_back(a[(std::min(i + 5, rhs) + i) >> 1]);
  }
}
