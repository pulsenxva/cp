// #pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int>> vvi;
typedef vector<pair<int, int>> vpii;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define eb emplace_back
#define F first
#define S second
#define sz(x) (ll)(((x).size()))

const int inf = 1e9 + 5;
const ll MOD = 1e9 + 7;
const ll mod2 = (MOD + 1) / 2;
const ld eps = 1e-9;

// https://informatics.msk.ru/mod/statements/view3.php?chapterid=113213#1

void solve() {
  int n; cin >> n;
  vi cost(n+1);
  for (int i = 1; i <= n; i++) cin >> cost[i];
  int m; cin >> m;
  vvi G(n+1);
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    G[u].pb(v); G[v].pb(u);
  }
  vector<vector<int> > dist(n+1, vector<int>(2, inf)); // 0-бак-бак+канистра
  dist[1][0]=0;
  set<array<int, 3> > st; // cost-v-бензин
  st.insert({0, 1, 0});
  while (!st.empty()) {
    auto [w,v,left] = *st.begin(); st.erase(st.begin());
    for (auto u: G[v]) {
      if (left == 1) {
        // ->0 ->1
        if (dist[v][1] < dist[u][0]) {
          st.erase({dist[u][0], u, 0});
          dist[u][0] = dist[v][1];
          st.insert({dist[u][0], u, 0});
        }
        if (dist[v][1]+cost[v] < dist[u][1]) {
          st.erase({dist[u][1], u, 1});
          dist[u][1] = dist[v][1]+cost[v];
          st.insert({dist[u][1], u, 1});
        }
      }
      else if (left==0) {
        // ->0 ->1
        if (dist[v][0]+cost[v] < dist[u][0]) {
          st.erase({dist[u][0], u, 0});
          dist[u][0] = dist[v][0]+cost[v];
          st.insert({dist[u][0], u, 0});
        }
        if (dist[v][0]+2*cost[v] < dist[u][1]) {
          st.erase({dist[u][1], u, 1});
          dist[u][1] = dist[v][0]+2*cost[v];
          st.insert({dist[u][1], u, 1});
        }
      }
    }
  }
  int ans = inf;
  ans = min({ans, dist[n][0], dist[n][1]});
  if (ans==inf) cout << -1 << '\n';
  else cout << ans << '\n';
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();
}
