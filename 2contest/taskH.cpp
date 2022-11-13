#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::swap;
using std::vector;

void Partition(const vector<int>& a, int x, vector<int>& left, vector<int>& med,
               vector<int>& right);
void BubbleSort(vector<int>& a);
void SortFive(vector<int>& a);
int QuickSelect(const vector<int>& a, size_t k);
void GetArrayOfMedian(const vector<int>& a, vector<int>& ans);
void Print(const vector<int>& a);
vector<int> QuickSort(const vector<int>& a);

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  a = QuickSort(a);
  Print(a);
}

void Print(const vector<int>& a) {
  for (auto i : a) {
    cout << i << ' ';
  }
  cout << '\n';
}

vector<int> QuickSort(const vector<int>& a) {
  if (a.size() <= 1) {
    return a;
  }
  int m = QuickSelect(a, a.size() / 2);
  vector<vector<int>> ans(3, vector<int>());
  Partition(a, m, ans[0], ans[1], ans[2]);
  ans[0] = QuickSort(ans[0]);
  ans[2] = QuickSort(ans[2]);
  vector<int> v;
  for (int i = 0; i < 3; ++i) {
    for (int el : ans[i]) {
      v.push_back(el);
    }
  }
  return v;
}
void Partition(const vector<int>& a, int x, vector<int>& left, vector<int>& med,
               vector<int>& right) {
  for (int i : a) {
    if (i < x) {
      left.push_back(i);
    } else if (i > x) {
      right.push_back(i);
    } else {
      med.push_back(i);
    }
  }
}

int QuickSelect(const vector<int>& a, size_t k) {
  if (a.size() <= 1) {
    return a[0];
  }
  vector<int> medians;
  GetArrayOfMedian(a, medians);
  int m = QuickSelect(medians, medians.size() / 2);
  vector<vector<int>> ans(3, vector<int>());
  Partition(a, m, ans[0], ans[1], ans[2]);
  if (k < ans[0].size()) {
    return QuickSelect(ans[0], k);
  }
  if (k < ans[0].size() + ans[1].size()) {
    return m;
  }
  return QuickSelect(ans[2], k - ans[0].size() - ans[1].size());
}
void BubbleSort(vector<int>& a) {
  if (a.size() == 5) {
    SortFive(a);
    return;
  }
  for (size_t i = a.size(); i > 0; --i) {
    for (size_t j = 1; j < i; ++j) {
      if (a[j - 1] > a[j]) {
        std::swap(a[j - 1], a[j]);
      }
    }
  }
}
void GetArrayOfMedian(const vector<int>& a, vector<int>& ans) {
  for (size_t i = 0; i < a.size(); i += 5) {
    vector<int> tmp;
    for (size_t j = 0; j < 5 && j < a.size(); ++j) {
      tmp.push_back(a[i]);
    }
    BubbleSort(tmp);
    ans.push_back(tmp[tmp.size() / 2]);
  }
}
void SortFive(vector<int>& a) {
  if (a[4] < a[0]) {
    swap(a[4], a[0]);
  }
  if (a[3] < a[1]) {
    swap(a[3], a[1]);
  }
  if (a[1] < a[0]) {
    swap(a[1], a[0]);
    swap(a[4], a[3]);
  }

  if (a[2] < a[1]) {
    int x = a[2];
    a[2] = a[1];
    if (x < a[0]) {
      a[1] = a[0];
      a[0] = x;
    } else {
      a[1] = x;
    }
  } else if (a[3] < a[2]) {
    swap(a[3], a[2]);
  }

  if (a[4] < a[2]) {
    int x = a[4];
    a[4] = a[3];
    a[3] = a[2];
    if (x < a[1]) {
      a[2] = a[1];
      a[1] = x;
    } else {
      a[2] = x;
    }
  } else if (a[4] < a[3]) {
    swap(a[4], a[3]);
  }
}
