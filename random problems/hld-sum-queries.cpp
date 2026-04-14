// #pragma GCC optimize("O3",unroll-loops)
// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx,avx2,fma,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2")
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define ld long double
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define YES {cout<<"YES\n";return;}
#define NO {cout<<"NO\n";return;}
const int inf = 2e18+5;
const int MOD = 1e9 + 7;
const int MAXN = 1000005;
const int SHIFT = 1000005;
const int BL = 350;
const int N = 5000;
const int LOGN = 20;

int n, cn = 0;
vector<int> a;
vector<vector<int>> g;
vector<int> heavy, from;
vector<int> p, ids;
vector<int> parent;

void init() {
  g.resize(n);
  a.resize(n);
  heavy.assign(n, -1);
  from.resize(n);
  ids.resize(n);
  parent.resize(n);
}

int dfs1(int v, int pr = -1) {
  int s = 1, mx = 0;
  parent[v] = pr;
  for (int u: g[v]) {
    if (u == pr) continue;
    int nc = dfs1(u, v);
    s += nc;
    if (nc > mx) {
      mx = nc;
      heavy[v] = u;
    }
  }
  return s;
}

void dfs2(int v, int fr, int pr) {
  from[v] = (fr == -1 ? v : fr);
  p.push_back(v);
  ids[v]=cn; cn++;
  if (heavy[v] != -1) dfs2(heavy[v], from[v], v);
  for (auto u: g[v]) {
    if (u == pr || u == heavy[v]) continue;
    dfs2(u, -1, v);
  }
}

int segt[4*MAXN];
void build(int v, int l, int r) {
  if (l+1 == r) {
    segt[v] = a[p[l]];
    return;
  }
  int m = (l+r)/2;
  build(2*v+1, l, m);
  build(2*v+2, m, r);
  segt[v] = segt[2*v+1] + segt[2*v+2];
}

void upd(int v, int l, int r, int idx, int x) {
  if (l+1 == r) {
    segt[v] = x;
    return;
  }
  int m = (r+l)/2;
  if (idx < m) upd(2*v+1, l, m, idx, x);
  else upd(2*v+2, m, r, idx, x);
  segt[v] = segt[2*v+1] + segt[2*v+2];
}

int get(int v, int l, int r, int ql, int qr) {
  if (ql >= r || qr <= l) return 0;
  if (ql <= l && r <= qr) return segt[v];
  int m = (l+r)/2;
  return get(2*v+1, l, m, ql, qr) + get(2*v+2, m, r, ql, qr);
}

int query(int v, int u) {
  int res = 0;
  while (from[v] != from[u]) {
    if (ids[from[u]] < ids[from[v]])
      swap(u ,v);
    res += get(0, 0, n, ids[from[u]], ids[u]+1);
    u = parent[from[u]];
  }
  if (ids[v] > ids[u]) swap(u, v);
  res += get(0, 0, n, ids[v], ids[u]+1);
  return res;
}

void solve() {
  cin >> n; init();
  for (auto&d: a) cin >> d;
  for (int i = 0; i < n-1; i++) {
    int u, v; cin >> u >> v;
    u--; v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  dfs1(0);
  dfs2(0, -1, -1);
  build(0, 0, n);

  int q; cin >> q;
  while (q--) {
    char t; cin >> t;
    if (t == '?') {
      int v, u; cin >> v >> u; v--; u--;
      cout << query(v, u) << '\n';
    }
    else {
      int v, x; cin >> v >> x; v--;
      upd(0, 0, n, ids[v], x);
    }
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int TC = 1;
  // cin >> TC;
  while (TC--) solve();
}
