// no_concepts
#include <iostream>
#include <string>
#include <vector>

const int kSigma = 26;

int Decode(char ttt) { return ttt - 'a'; }

std::vector<int> SufMas(std::string& sss) {
  int nnn = static_cast<int>(sss.size());
  std::vector<int> cnt(std::max(kSigma, nnn));
  std::vector<int> ppp(nnn);
  std::vector<int> ccc(nnn);
  for (int iii = 0; iii < nnn; ++iii) {
    ++cnt[Decode(sss[iii])];
  }
  for (int iii = 1; iii < kSigma; ++iii) {
    cnt[iii] += cnt[iii - 1];
  }
  for (int iii = nnn - 1; iii >= 0; --iii) {
    ppp[--cnt[Decode(sss[iii])]] = iii;
  }
  ccc[ppp[0]] = 0;
  for (int iii = 1; iii < nnn; ++iii) {
    ccc[ppp[iii]] = ccc[ppp[iii - 1]];
    if (sss[ppp[iii]] != sss[ppp[iii - 1]]) {
      ++ccc[ppp[iii]];
    }
  }
  int rrr = 1;
  while (rrr <= nnn) {
    std::vector<int> pnn(nnn);
    std::vector<int> cnn(nnn);
    for (int iii = 0; iii < nnn; ++iii) {
      pnn[iii] = ppp[iii] - rrr;
      if (pnn[iii] < 0) {
        pnn[iii] += nnn;
      }
    }
    cnt.assign(cnt.size(), 0);
    for (int iii = 0; iii < nnn; ++iii) {
      ++cnt[ccc[iii]];
    }
    for (int iii = 1; iii < nnn; ++iii) {
      cnt[iii] += cnt[iii - 1];
    }
    for (int iii = nnn - 1; iii >= 0; --iii) {
      ppp[--cnt[ccc[pnn[iii]]]] = pnn[iii];
    }
    cnn[ppp[0]] = 0;
    for (int iii = 1; iii < nnn; ++iii) {
      cnn[ppp[iii]] = cnn[ppp[iii - 1]];
      if (ccc[ppp[iii]] != ccc[ppp[iii - 1]]) {
        ++cnn[ppp[iii]];
      } else if (ccc[(ppp[iii] + rrr) % nnn] !=
                 ccc[(ppp[iii - 1] + rrr) % nnn]) {
        ++cnn[ppp[iii]];
                 }
    }
    ccc = std::move(cnn);
    cnn.assign(nnn, 0);
    rrr *= 2;
  }
  return ppp;
}

int main() {
  std::string sss;
  std::cin >> sss;
  std::vector<int> ans = SufMas(sss);
  for (size_t iii = 0; iii < sss.size(); ++iii) {
    std::cout << sss[(ans[iii] + sss.size() - 1) % sss.size()];
  }
}
