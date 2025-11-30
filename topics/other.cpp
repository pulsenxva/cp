#include <bits/stdc++.h>

// scanline
struct Event {
  int x, type;
  bool operator<(const Event& e) const {
    if (x != e.x) return x < e.x;
    return type < e.type;
  }
};

// faster mst alternative
struct heap { 
  priority_queue<int> pq, rem;

  void push(int x) {
    pq.push(x);
  }
  void erase(int x) {
    rem.push(x);
  }
  int top() {
    while(!pq.empty() && !rem.empty() && pq.top()==rem.top()) {
      pq.pop(); rem.pop();
    }
    return pq.top();
  }

  ///////////////
  // heap pqmx, pqmn;
  // add x:
  //   pqmx.push(x)
  //   pqmn.push(-x)
  // erase x:
  //   pqmx.erase(x)
  //   pqmn.erase(-1)
  // return max:
  //   return pqmx.top()
  // return min:
  //   return -pqmn.top()
};

// with heap
struct manhattan_dist {
  set<pair<ll, ll> > st;
  heap summx, summn, difmx, difmn;  
  void add(ll x, ll y) {
    ll a = x+y, b = x-y;
    st.insert({x,y});
    
    summx.push(a); summn.push(-a);
    difmx.push(b); difmn.push(-b);
  }
  void del(ll x, ll y) {
    ll a = x+y, b = x-y;
    st.erase({x,y});
    summx.erase(a); summn.erase(-a);
    difmx.erase(b); difmn.erase(-b);
  }
  bool have(pair<int,int> pr) {
    return st.count({pr.first,pr.second});
  }
  bool check() {
    return !st.empty(); // 1=>ok
  }
  
  ll mxsum() {
    return summx.top();
  }
  ll mnsum() {
    return -summn.top();
  }
  ll mxdif() {
    return difmx.top();
  }
  ll mndif() {
    return -difmn.top();
  }
};

// with mst
struct manhattan_dist {
  multiset<ll> sum, dif;
  set<pair<ll, ll> > st;
  void add(ll x, ll y) {
    sum.insert(x+y);
    dif.insert(x-y);
    st.insert({x,y});
  }
  void del(ll x, ll y) {
    st.erase({x,y});
    auto itsum = sum.find(x+y);
    if(itsum != sum.end()) sum.erase(itsum);
    auto itdif = dif.find(x-y);
    if(itdif != dif.end()) dif.erase(itdif);
  }
  bool have(pair<int,int> pr) {
    return st.count({pr.first,pr.second});
  }
  bool check() {
    return !st.empty(); // 1=>ok
  }
  
  ll mxsum() {
    return *sum.rbegin();
  }
  ll mnsum() {
    return *sum.begin();
  }
  ll mxdif() {
    return *dif.rbegin();
  }
  ll mndif() {
    return *dif.begin();
  }
};
manhattan_dist fi, se;
ll res1 = fi.mxsum() - se.mnsum();
ll res2 = se.mxsum() - fi.mnsum();
ll res3 = fi.mxdif() - se.mndif();
ll res4 = se.mxdif() - fi.mndif();
// max dist = max(res1, res2, res3, res4);
// min dist = min(res1, res2, res3, res4);
