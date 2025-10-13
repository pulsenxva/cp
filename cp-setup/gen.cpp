#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll gen(ll l, ll r) {
  static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  uniform_int_distribution<ll> dist(l, r);
  return dist(rng);
}

string alph = "abcdefghijklmnopqrstuvwxyz";

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n = gen(1, 10);
  int k = gen(1, 10);

  cout << n << " " << k << "\n";
}
