#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
const ll MOD = 1e9;
const int p = 10;

struct Resid {
  ll r;
  Resid(ll r_ = 0, bool fl = 0) {
    if (!fl) r_ %= MOD;
    r = r_;
  }

  Resid operator+(const Resid& other) const {
    if (r + other.r >= MOD) return r + other.r - MOD;
    return r + other.r;
  }
  Resid operator-(const Resid& other) const {
    if (r - other.r < 0) return r - other.r + MOD;
    return r - other.r;
  }
  Resid operator*(const Resid& other) const {
    return 1ll * r * other.r % MOD;
  }
  bool operator==(const Resid& o) const {
    return r == o.r;
  }
};

ostream& operator<<(ostream& out, const Resid& r) {
  return out << r.r;
}

struct Hash {
  vector<Resid> h1;
  vector<ull> h2;
};

vector<Resid> pow1;
vector<ull> pow2;

pair<Resid, ull> substr(int l, int r, Hash& h) {
  // [l, r)
  return {
    h.h1[r] - h.h1[l] * pow1[r-l],
    h.h2[r] - h.h2[l] * pow2[r-l]
  };
}

const int N = 2e5;
Hash build(string s) {
  pow1.resize(N+1);
  pow2.resize(N+1);
  pow1[0] = 1;
  pow2[0] = 1;

  for (int i = 1; i <= N; i++) {
    pow1[i] = pow1[i-1] * p;
    pow2[i] = pow2[i-1] * p;
  }

  Hash h;
  h.h1.resize(s.size() + 1);
  h.h2.resize(s.size() + 1);
  for (int i = 0; i < s.size(); i++) {
    h.h1[i+1] = h.h1[i] * p + s[i] - 'a' + 1;
    h.h2[i+1] = h.h2[i] * p + s[i] - 'a' + 1;
  }
  return h;
}

bool isEq(pair<Resid, ull> a, pair<Resid, ull> b) {
  return a == b;
}

// bool ok = isEq(substr(l1 - 1, r1, h), substr(l2 - 1, r2, h));
