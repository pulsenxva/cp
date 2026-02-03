#include <bits/stdc++.h>
using namespace std;

struct Hash {
  static const long long MOD = 1000000007;
  static const long long P = 31;

  vector<long long> h, p;

  Hash(const string &s) {
    int n = s.size();
    h.resize(n + 1);
    p.resize(n + 1);

    p[0] = 1;
    for (int i = 0; i < n; i++) {
      h[i + 1] = (h[i] * P + (s[i] - 'a' + 1)) % MOD;
      p[i + 1] = (p[i] * P) % MOD;
    }
  }

  // хэш подстроки [l, r] (0-индексация)
  long long get(int l, int r) {
    long long res = (h[r + 1] - h[l] * p[r - l + 1]) % MOD;
    if (res < 0)
      res += MOD;
    return res;
  }
};

struct AnagramHash {
  vector<vector<int>> pref;

  AnagramHash(const string &s) {
    int n = s.size();
    pref.assign(n + 1, vector<int>(26, 0));

    for (int i = 0; i < n; i++) {
      pref[i + 1] = pref[i];
      pref[i + 1][s[i] - 'a']++;
    }
  }

  // возвращает вектор частот символов на [l, r]
  vector<int> get(int l, int r) {
    vector<int> res(26);
    for (int i = 0; i < 26; i++)
      res[i] = pref[r + 1][i] - pref[l][i];
    return res;
  }
};

int main() {
  string s;
  int l1, r1, l2, r2;
  Hash hs(s);
  if (hs.get(l1, r1) == hs.get(l2, r2)) {
    //
  }
}
