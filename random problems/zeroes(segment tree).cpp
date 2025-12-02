#include <bits/stdc++.h>
using namespace std;

// https://informatics.msk.ru/mod/statements/view.php?chapterid=111798#1

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int>> vvi;
typedef vector<pair<int, int>> vpii;
typedef vector<vector<pair<int, int>>> vvpii;
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
const ll MOD = 1e9 + 7;
const ll mod2 = (MOD + 1) / 2;
const ld eps = 1e-9;
const int MAXN = 1e6 + 5;

struct node {
  int ans, pref, suf, len;
};

vector<ll> a;
vector<node> segt(4*MAXN);

node merge(const node& a, const node& b) {
  int ans = max({0, a.ans, b.ans, a.suf+b.pref});
  int pr = a.pref;
  int sf = b.suf;
  int ln = a.len+b.len;
  if(a.suf == a.len) {
    ans = max(ans, a.pref+b.pref);
    pr = a.pref + b.pref;
  }
  if(b.pref == b.len) {
    ans = max(ans, a.suf+b.pref);
    sf = a.suf+b.pref;
  }
  return {ans, pr, sf, ln};
}

void build(int v, int l, int r) {
  if(r-l==1) {
    if(a[l] == 0) {
      segt[v].ans = 1;
      segt[v].pref = 1;
      segt[v].suf = 1;
      segt[v].len=1;
    }
    else {
      segt[v].ans=0;
      segt[v].pref=0;
      segt[v].suf=0;
      segt[v].len=1;
    }
    return;
  }
  int m = (r+l)/2;
  build(2*v, l, m); build(2*v+1, m, r);
  segt[v] = merge(segt[2*v], segt[2*v+1]);
}

void upd(int v, int l, int r, int idx, ll x) {
  if(r-l == 1) {
    if(x == 0) {
      segt[v].ans=1, segt[v].len=1;
      segt[v].pref=1, segt[v].suf=1;
    } else {
      segt[v].ans=0, segt[v].len=1;
      segt[v].pref=0, segt[v].suf=0;
    }
    return;
  }
  int m = (r+l)/2;
  if(idx<m) {
    upd(2*v, l, m, idx, x);
  } else {
    upd(2*v+1, m, r, idx, x);
  }
  segt[v] = merge(segt[2*v], segt[2*v+1]);
}

node get(int v, int l, int r, int ql, int qr) {
  if (qr <= l || r <= ql) return{0,0,0,1};
  if (ql <= l && r <= qr) return segt[v];

  int m = (r+l)/2;
  node n1 = get(2*v, l, m, ql, qr);
  node n2 = get(2*v+1, m, r, ql, qr); 
  return merge(n1,n2); 
}

void solve() {
  int n; cin >> n;
  a.resize(n);
  for(auto& d: a) cin >> d;
  build(1, 0, n);
  int q; cin >> q;
  while(q--) {
    string s; cin >> s;
    if(s == "QUERY") {
      int l, r; cin >> l >> r;
      cout << get(1, 0, n, l-1, r).ans << '\n';
    } else {
      int idx, x; cin >> idx >> x;
      idx--;
      a[idx]=x;
      if(a[idx]==0) {
        upd(1, 0, n, idx, 0);
      } else {
        upd(1, 0, n, idx, 1);
      }
    }
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();
}
