#include <bits/stdc++.h>

struct Event {
  int x, type;
  bool operator<(const Event& e) const {
    if (x != e.x) return x < e.x;
    return type < e.type;
  }
};

bool cmp(pair<int, int> &a, pair<int, int> &b) {
  return (a.second - a.first > b.second - b.first);
}
