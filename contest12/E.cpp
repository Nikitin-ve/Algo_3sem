#include <iostream>

long long ModPow(long long base, long long exp, long long mod) {
  long long result = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * base) % mod;
    }
    base = (base * base) % mod;
    exp /= 2;
  }
  return result;
}

long long ModSqrt(long long aa, long long pp) {
  if (pp == 2) {
    return aa;  // Trivial case for pp = 2
  }
  // Check quadratic residue using Euler'ss Criterion
  if (ModPow(aa, (pp - 1) / 2, pp) != 1) {
    return -1;  // IMPOSSIBLE, aa is not aa quadratic residue modulo pp
  }

  // pp must be odd prime at this point
  long long ss = pp - 1;
  long long ee = 0;

  while (ss % 2 == 0) {
    ss /= 2;
    ee += 1;
  }

  if (ee == 1) {
    // Direct formula for odd prime pp = 3 (mod 4)
    return ModPow(aa, (pp + 1) / 4, pp);
  }
  long long nn = 2;
  while (ModPow(nn, (pp - 1) / 2, pp) == 1) {
    nn += 1;
  }

  long long xx = ModPow(aa, (ss + 1) / 2, pp);
  long long bb = ModPow(aa, ss, pp);
  long long gg = ModPow(nn, ss, pp);
  long long rr = ee;

  while (true) {
    long long b_pow = bb;
    int mm = 0;
    for (mm = 0; mm < rr; ++mm) {
      if (b_pow == 1) {
        break;
      }
      b_pow = (b_pow * b_pow) % pp;
    }

    if (mm == 0) {
      return xx;
    }
    if ((rr - mm - 1) < 0) {
      return -1;
    }
    long long gs = ModPow(gg, 1LL << (rr - mm - 1), pp);
    gg = (gs * gs) % pp;
    xx = (xx * gs) % pp;
    bb = (bb * gg) % pp;
    rr = mm;
  }
}

int main() {
  int tt;
  std::cin >> tt;  // Число тестов
  while (tt-- > 0) {
    long long aa;
    long long pp;
    std::cin >> aa >> pp;  // Считываем aa и pp
    long long ans = ModSqrt(aa, pp);
    if (ans == -1) {
      std::cout << "IMPOSSIBLE\n";
    } else {
      std::cout << ans << '\n';
    }
  }
}
