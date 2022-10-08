#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  int n;
  std::cin >> n;
  double* p = new double[n + 1];
  p[0] = 1;
  double* a = new double[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    p[i + 1] = p[i] * pow(a[i], 1.0 / n);
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int r, l;
    std::cin >> l >> r;
    double ans = pow(p[r + 1] / p[l], (n * 1.0) / (r - l + 1));
    std::cout << std::setprecision(10) << ans << '\n';
  }
  delete[] a;
  delete[] p;
}
