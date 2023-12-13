// no_concepts
#include <iostream>
#include <string>
#include <vector>

const int kSigma = 26;
const int kDdd = 10;

int Decode(char ttt) { return ttt - 'a'; }

std::string BWT(std::string&& sss) {
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
  std::string ans;
  for (size_t iii = 0; iii < sss.size(); ++iii) {
    ans += sss[(ppp[iii] + sss.size() - 1) % sss.size()];
  }
  return ans;
}

std::string MTF(std::string&& sss) {
  std::string alp = "abcdefghijklmnopqrstuvwxyz";
  std::string ans;
  for (size_t i = 0; i < sss.size(); ++i) {
    int jjj;
    for (jjj = 0; jjj < kSigma; ++jjj) {
      if (sss[i] == alp[jjj]) {
        ans += static_cast<char>(jjj + 'a');
        break;
      }
    }
    for (; jjj > 0; --jjj) {
      std::swap(alp[jjj], alp[jjj - 1]);
    }
  }
  return ans;
}

std::string RLE(std::string&& sss) {
  int ttt = 1;
  std::string ans;
  for (size_t i = 1; i < sss.size(); ++i) {
    if (sss[i] == sss[i - 1]) {
      ++ttt;
    } else {
      ans += sss[i - 1];
      ans += std::to_string(ttt);
      ttt = 1;
    }
  }
  ans += sss[sss.size() - 1];
  ans += std::to_string(ttt);
  return ans;
}

std::string DRLE(std::string&& sss) {
  char kkk = sss[0];
  unsigned int eee = 0;
  std::string ans;
  for (size_t i = 1; i < sss.size(); ++i) {
    if (sss[i] - 'a' < 0 || sss[i] - 'z' > 0) {
      eee = eee * kDdd + sss[i] - '0';
    } else {
      ans += std::string(eee, kkk);
      kkk = sss[i];
      eee = 0;
    }
  }
  ans += std::string(eee, kkk);
  return ans;
}

std::string DMTF(std::string&& sss) {
  std::string alp = "abcdefghijklmnopqrstuvwxyz";
  std::string ans;
  for (size_t i = 0; i < sss.size(); ++i) {
    ans += alp[sss[i] - 'a'];
    for (int k = sss[i] - 'a'; k > 0; --k) {
      std::swap(alp[k], alp[k - 1]);
    }
  }
  return ans;
}

std::string DBWT(std::string&& sss, int xxx) {
  std::vector<int> count(kSigma, 0);
  int nnn = static_cast<int>(sss.size());
  std::vector<int> ttt(nnn);
  std::string ans;
  for (int i = 0; i < nnn; ++i) {
    ++count[sss[i] - 'a'];
  }
  int suum = 0;
  for (int i = 0; i < kSigma; ++i) {
    suum += count[i];
    count[i] = suum - count[i];
  }
  for (int i = 0; i < nnn; ++i) {
    ttt[count[sss[i] - 'a']] = i;
    ++count[sss[i] - 'a'];
  }
  int jjj = ttt[xxx];
  for (int i = 0; i < nnn; ++i) {
    ans += sss[jjj];
    jjj = ttt[jjj];
  }
  return ans;
}

int main() {
  std::string sss;
  int nnn;
  std::cin >> nnn >> sss;
  if (nnn == 1) {
    std::cout << RLE(MTF(BWT(std::move(sss))));
  } else {
    int jjj;
    std::cin >> jjj;
    std::cout << DBWT(DMTF(DRLE(std::move(sss))), jjj);
  }
}
