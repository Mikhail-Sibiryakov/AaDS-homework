#include <algorithm>
#include <deque>
#include <iostream>

void Push(std::deque<int>& d_left, int k) { d_left.push_front(k); }
void PushVIP(std::deque<int>& d_left, std::deque<int>& d_right, int k) {
  while (d_left.size() > d_right.size()) {
    int tmp = d_left.back();
    d_left.pop_back();
    d_right.push_front(tmp);
  }
  d_left.push_back(k);
}
void Del(std::deque<int>& d_left, std::deque<int>& d_right) {
  if (!d_right.empty()) {
    std::cout << d_right.back() << '\n';
    d_right.pop_back();
  } else {
    std::cout << d_left.back() << '\n';
    d_left.pop_back();
  }
}
int main() {
  int n;
  std::cin >> n;
  std::deque<int> d_left, d_right;
  for (int i = 0; i < n; ++i) {
    int k = -1;
    char ch;
    std::cin >> ch;
    if (ch == '-') {
      Del(d_left, d_right);
    } else {
      std::cin >> k;
      if (ch == '+') {
        Push(d_left, k);
      }
      if (ch == '*') {
        PushVIP(d_left, d_right, k);
      }
    }
  }
}
