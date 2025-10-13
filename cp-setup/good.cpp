#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define eb emplace_back
#define F first
#define S second
#define isz(x) (int)(x).size()

const ll inf = (ll)2e18;
const int mod = 1e9;
const ld eps = 1e-9;
vector<unordered_set<int> > G;
vector<int> used;
vector<int> er; 

ll gcd(ll a, ll b) {
  if (b != 0) return gcd(b, a % b);
  else return a;
}

ll lcm(ll a, ll b) {
  return (a / gcd(a, b)) * b;
}

void maxi(int &a, int b) {
  a = max(a, b);
}

void add_self(int &a, int b) {
  a += b;
  if (a >= mod) a %= mod;
}

void write(vector<int> &v) {
  for (auto &d: v) cin >> d;
}

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

bool comp(pair<ll, ll> &a, pair<ll, ll> &b) {
  return a.S < b.S;
}

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k; cin >> n >> k;
  if(n == 1 || k == 1) cout << 100 << '\n';
  else cout << n+k << '\n';
}