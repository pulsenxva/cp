#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int> > G(n + 1);

// diam
pair<int, int> graph_diametr(int start) {
  int n = (int) G.size();
  vector<bool> used(n, false);
  vector<int> dist(n, 0);
  queue<int> q;

  q.push(start);
  used[start] = true;

  while (!q.empty()) {
    int tmp = q.front();
    q.pop();
    for (int to: G[tmp]) {
      if (!used[to]) {
        used[to] = true;
        dist[to] = dist[tmp] + 1;
        q.push(to);
      }
    }
  }

  int mx = 0;
  int node = start;
  for (int i = 0; i < n; i++) {
    if (dist[i] > mx) {
      mx = dist[i];
      node = i;
    }
  }

  return {node, mx};
}
// auto [p1, dist1] = graph_diametr(1, G);
// auto [p2, diam] = graph_diametr(p1, G);

// cycle check (directed graph)
bool cycle = 0;
vector<int> used, par;
void cycleCheck_orient(int v) {
  used[v] = 1;
  for (auto to: G[v]) {
    if (!used[to]) {
      par[to] = v;
      cycleCheck_orient(to);
    } else if (used[to] == 1) {
      cycle = 1;
    }
  }
  used[v] = 2;
}

// topsort + маркировка компонент сильной связности
vector<int> topsort, component;
vector<vector<int> > T;
void graph_topsort(int v) {
  used[v] = 1;
  for (int u: G[v]) {
    if (!used[u]) graph_topsort(u);
  }
  topsort.push_back(v);
}
int cnt_comp = 0;
void dfs2(int v) {
  component[v] = cnt_comp;
  for (int u: T[v])
    if (component[u] == 0)
      dfs2(u);
}
// main:
// for (int v = 0; v < n; v++)
//   for (int u : g[v])
//     t[u].push_back(v);
//
// // запускаем топологическую сортировку
// for (int i = 0; i < n; i++)
//   if (!used[i])
//     dfs1(i);
//
// // выделяем компоненты
// reverse(topsort.begin(), topsort.end());
// for (int v : topsort)
//   if (component[v] == 0)
//     dfs2(v);
// set<pair<int, int> > ans; // для хранения ребер в конденсации ориентированного графа
// for (int v = 1; v <= n; v++) {
//   for (int u : G[v]) {
//     if (component[v] != component[u]) {
//       ans.insert({component[v], component[u]});
//     }
//   }
// }
// cout << ans.size() << '\n';

// cycle check (undirected graph) + recovery
vector<int> rec(int v, int u) {
  vector<int> path;
  while (v != u) {
    path.push_back(v);
    v = par[v];
  }
  path.push_back(u);
  return path;
}
vector<int> ans;
void cycleCheck_nonorient(int v) {
  used[v] = 1;
  for (auto to: G[v]) {
    if (!used[to]) {
      par[to] = v;
      cycleCheck_nonorient(to);
    } else if (used[to] == 1) {
      vector<int> path = rec(v, to);
      if (path.size() % 2) {
        cycle = 1;
        ans = path;
      }
    }
  }
  used[v] = 2;
}


vector<int> h, hup;
set<int> ans;
void articulation_point(int v, int p) {
  used[v] = 1;
  hup[v] = h[v];
  int cnt = 0;
  for (auto to: G[v]) {
    if (to == p) continue;
    if (!used[to]) {
      h[to] = h[v] + 1;
      cnt++;
      articulation_point(to, v);
      hup[v] = min(hup[v], hup[to]);
      if (hup[to] >= h[v] && p != -1) {
        ans.insert(v);
      }
    } else {
      hup[v] = min(hup[v], h[to]);
    }
  }
  if (cnt > 1 && p == -1) ans.insert(v);

  // main:
  // for (int i = 1; i <= n; i++) {
  //   if (!used[i]) articulation_point(i, -1);
  // }
}

vector<int> ans;
map<pair<int, int>, int> mp; // stores numbers of edjes. for recovery
void bridges(int v, int p) {
  used[v] = 1;
  hup[v] = h[v];
  for (auto to: G[v]) {
    if (to == p) continue;
    if (!used[to]) {
      h[to] = h[v] + 1;
      bridges(to, v);
      hup[v] = min(hup[v], hup[to]);
      if (hup[to] > h[v]) {
        ans.push_back(mp[{v, to}]);
      }
    } else {
      hup[v] = min(hup[v], h[to]);
    }
  }
}

void dfs_depth(int v, int p) {
  used[v] = 1;
  for (int to : G[v]) {
    if (to == p) continue;
    if (!used[to]) {
      h[to] = h[v] + 1;
      dfs_depth(to, v);
    }
  }
}
