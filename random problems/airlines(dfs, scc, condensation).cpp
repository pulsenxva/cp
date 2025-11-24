#pragma GCC optimize(3)
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int>> vvi;
typedef vector<pair<int, int> > vpii;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define eb emplace_back
#define F first
#define S second
#define sz(x) (ll)(((x).size()))

const ll inf = 2e18 + 5;
const ll mod = 1e9 + 7;
const ll mod2 = (mod + 1) / 2;
const ld eps = 1e-9;

https://informatics.mccme.ru/mod/statements/view.php?chapterid=3360#1

vvi T;
vector<set<int>> G;
vi topsort, used;
map<int, vector<int> > mp;

void dfs1(int v) {
  used[v]=1;
  for(auto to: G[v]) {
    if(!used[to]) dfs1(to);
  }
  topsort.pb(v);
}

int cntcmp=0;
vi cmp;

void dfs2(int v) {
  cmp[v]=cntcmp;
  mp[cntcmp].pb(v);
  for(auto to: T[v]) {
    if(cmp[to]==-1) dfs2(to);
  }
}

vector<set<int>> cond(cntcmp);
void dfs3(int v, int goal, bool&can) {
  used[v]=1;
  if (v == goal) {
    can=1;
    return;
  }
  for (int u: cond[v]) {
    if (!used[u]) dfs3(u, goal, can);
  }
}

void solve() {
  int n, m; cin >> n >> m;
  G.resize(n+1), T.resize(n+1);

  for(int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    G[u].insert(v);
  }

  used.assign(n+1, 0);

  for(int i = 1; i <= n; i++) {
    if(!used[i]) dfs1(i);
  }
  reverse(all(topsort));

  for(int v = 1; v <= n; v++) {
    for(auto u: G[v]) T[u].pb(v);
  }

  cmp.assign(n+1, -1);
  for(int v: topsort) {
    if(cmp[v]==-1) {
      dfs2(v);
      cntcmp++;
    }
  }

  vector<vector<int> > res(n+1);
  for (const auto& [col, edges]: mp) {
    if (sz(edges)==1) continue;
    for (int i = 0; i < sz(edges); i++) {
      if (i == sz(edges)-1) res[edges[i]].pb(edges[0]);
      else res[edges[i]].pb(edges[i+1]);
    }
  }

  set<pair<int, int> > ed;
  cond.resize(cntcmp);
  used.assign(cntcmp, 0);
  for (int v = 1; v <= n; v++) {
    for (int u: G[v]) {
      if (cmp[v]!=cmp[u]) {
        cond[cmp[v]].insert(cmp[u]);
        ed.insert({cmp[v], cmp[u]});
      }
    }
  }

  for (auto [cv, cu]: ed) {
    cond[cv].erase(cu);
    int goal = cu;
    bool can = 0;
    used.assign(cntcmp, 0);
    dfs3(cv, goal, can);
    if (!can) {
      cond[cv].insert(cu);
      int v = *mp[cv].begin();
      int u = *mp[cu].begin();
      res[v].pb(u);
    }
  }

  vector<pair<int, int>> ans;
  for (int v = 1; v <= n; v++) {
    for (int u: res[v]) ans.eb(v, u);
  }

  cout << sz(ans) << "\n";
  for (auto [u, v]: ans) cout << u << " " << v << '\n';
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();
}
