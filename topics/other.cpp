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
