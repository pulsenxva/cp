https://acmp.ru/asp/do/index.asp?main=task&id_course=3&id_section=24&id_topic=181&id_problem=1188


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 1e9 + 7;

vector<vector<int> > G;
vector<int> used, h, hup;
map<pair<int, int>, int> mp;

// находим мосты, закидываем их в map
void dfs(int v, int p) {
  used[v] = 1;
  hup[v] = h[v];
  for (auto to : G[v]) {
    if (to == p) continue;
    if (!used[to]) {
      h[to] = h[v] + 1;
      dfs(to, v);
      hup[v] = min(hup[v], hup[to]);
      if (hup[to] > h[v]) mp[{v, to}] = 1;
    } else {
      hup[v] = min(hup[v], h[to]);
    }
  }
}

int cmpid = 0;
vector<int> cmp, szcmp;

void dfs2(int v) {
  cmp[v] = cmpid;
  szcmp.back()++;
  for (auto to : G[v]) {
    if (mp[{v, to}] || mp[{to, v}]) continue;
    if (cmp[to] == -1) dfs2(to);
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  G.resize(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  h.resize(n + 1);
  hup.resize(n + 1);
  used.resize(n + 1);

  dfs(1, -1);
  cmp.assign(n + 1, -1);
  // каждую вершину красим, для каждой компоненты реберной двусвязности запоминаем количество вершин в ней
  for (int v = 1; v <= n; v++) {
    if (cmp[v] == -1) {
      szcmp.push_back(0);
      dfs2(v);
      cmpid++;
    }
  }

  if (cmpid == 1) {
    cout << 1 << " " << n % mod << '\n';
    return;
  }

  // делаем конденсацию
  vector<vector<int> > t(cmpid);
  for (auto [deg, q] : mp) {
    if (!q) continue;
    int u = cmp[deg.first];
    int v = cmp[deg.second];
    t[u].push_back(v);
    t[v].push_back(u);
  }

  ll ans = 1, cnt = 0;
  for (int v = 0; v < cmpid; v++) {
    if (t[v].size() == 1) {
      ans = ans * (ll) szcmp[v] % mod;
      cnt++;
    }
  }

  cout << cnt << " " << ans << '\n';
}
