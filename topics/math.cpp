#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
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
      primes.push_back(i);
      for (ll j = 2 * i; j <= n; j += i)
        er[j] = 1;
    }
  }
}

// для каждого i 1..n считает ко-во делителей
void eratosfen_divisors() {
  vector<int> divisors(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) {
      divisors[j]++;
    }
  }
}

// предпосчет phi 1..n
vector<int> euler_totient_sieve_optimized(int n) {
  vector<int> phi(n + 1);

  // Инициализация
  for (int i = 0; i <= n; i++) {
    phi[i] = i;
  }

  for (int i = 2; i <= n; i++) {
    if (phi[i] == i) {                 // i - простое число
      phi[i] = i - 1; // Для простого p: φ(p) = p - 1
      // Обновляем только кратные числа
      for (int j = 2 * i; j <= n; j += i) {
        phi[j] -= phi[j] / i;
      }
    }
  }

  return phi;
}

vector<int> factors(int n) {
  vector<int> f;
  for (int x = 2; x * x <= n; x++) {
    while (n % x == 0) {
      f.push_back(x);
      n /= x;
    }
  }
  if (n > 1)
    f.push_back(n);
  return f;
}

// fenwik tree
ll tree[500500];
void addT(int k, int x) {
  for (; k <= n; k += k & -k)
    tree[k] += x;
}
ll sumT(int r) {
  ll res = 0;
  for (; r > 0; r -= r & -r)
    res += tree[r];
  return res;
}

bool cmp(pair<int, int> &a, pair<int, int> &b) {
  return (a.second - a.first > b.second - b.first);
}

// ax+by=c, x, y-? x - min
void Diophantine(int a, int b, int &g, int &x, int &y) {
  if (b == 0)
  {
    g = a;
    x = 1;
    y = 0;
    return;
  }
  int x0, y0;
  Diophantine(b, a % b, g, x0, y0);
  x = y0;
  y = x0 - a / b * y0;
}
// void solve() {
//   int a, b, c;
//   cin >> a >> b >> c;
//   int x, y, g;
//   Diophantine (a, b, g, x, y);
//   if (c % g) {
//     cout << "Impossible" << '\n';
//     return;
//   }
//   x *= c / g;
//   y *= c / g;
//   int dx = b/g, dy = a/g;
//   int k = -x/dx;
//   if (x + k * dx < 0) k++;
//   x += k * dx;
//   y -= k * dy;
//   cout << x << " " << y;
// }

bool isPrime(int n) {
  if (n < 2)
    return false;
  for (int i = 2; i * i <= n; i++)
    if (n % i == 0)
      return false;
  return true;
}

// x^n mod m
int modpow(int x, int n, int m) {
  if (n == 0)
    return 1 % m;
  long long u = modpow(x, n / 2, m);
  u = (u * u) % m;
  if (n % 2 == 1)
    u = (u * x) % m;
  return u;
}
