#include <cmath>
#include <iostream>
#include <unordered_map>

const long long kInf = 2 * 1e9;
const double kMagicNumber = 1.5;

long long BinPow(long long base, long long degree, long long mod) {
  if (degree == 0) {
    return 1;
  }
  if (degree % 2 == 0) {
    long long tt = BinPow(base, degree / 2, mod);
    return (tt * tt) % mod;
  }
  return (base * BinPow(base, degree - 1, mod)) % mod;
}

int main() {
  int mod;
  int base;
  int ans;
  while (std::cin >> mod >> base >> ans) {
    if (ans == 1) {
      std::cout << 0 << '\n';
      continue;
    }
    long long sqm = std::ceil(kMagicNumber * std::sqrt(mod));
    std::unordered_map<int, int> f_1;
    for (int i = 1; i < mod / sqm + 1; ++i) {
      long long ee = BinPow(base, sqm * i, mod);
      if (f_1.find(ee) == f_1.end()) {
        f_1[ee] = i;
      }
    }
    long long answer = kInf;
    for (int i = 0; i < sqm + 1; ++i) {
      long long f_2 = (ans * BinPow(base, i, mod)) % mod;
      if (f_1.find(f_2) != f_1.end()) {
        long long kk = f_1[f_2] * sqm - i;
        if (kk < answer) {
          answer = kk;
        }
      }
    }
    if (answer == kInf) {
      std::cout << "no solution" << '\n';
    } else {
      std::cout << answer << '\n';
    }
    f_1.clear();
  }
}