#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll gcd(ll a, ll b) {
  if (b != 0) return gcd(b, a % b);
  else return a;
}

ll lcm(ll a, ll b) {
  return (a / gcd(a, b)) * b;
}

vector<int> er;
void eratosfen(ll n, vector<ll> &primes) {
  er.assign(n + 1, 0);
  er[0] = er[1] = 1;
  for (ll i = 2; i <= n; i++) {
    if (!er[i]) {
      primes.pb(i);
      for (ll j = 2 * i; j <= n; j += i) er[j] = 1;
    }
  }
}

vector<int> factors(int n) {
  vector<int> f;
  for (int x = 2; x*x <= n; x++) {
    while (n%x == 0) {
      f.push_back(x);
      n /= x;
    }
  }
  if (n > 1) f.push_back(n);
  return f;
}

// fenwik treev
ll tree[500500];
void addT(int k, int x) {
  for (; k <= n; k += k & -k) tree[k] += x;
}
ll sumT(int r) {
  ll res = 0;
  for(; r > 0; r -= r&-r) res += tree[r];
  return res;
}

bool cmp(pii &a, pii &b) {
  return (a.S-a.F > b.S-b.F);
}