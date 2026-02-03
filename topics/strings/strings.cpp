#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
const ll MOD = 1000000007;
const ll inf = 1e18 + 5;
const int MAXN = (int)3e5 + 5;
const ll P = 31;

struct Trie {
  struct Node {
    int next[26];
    int term;
    int cnt;
    Node() {
      term = 0; cnt = 0;
      memset(next, -1, sizeof(next));
    }
  };

  vector<Node> trie;

  void add(const string& s) {
    int v = 0;
    trie[v].cnt++;
    for(char ch: s) {
      int c = ch - 'a';
      if(trie[v].next[c] == -1) {
        trie[v].next[c] = trie.size();
        trie.emplace_back();
      }
      v = trie[v].next[c]; 
      trie[v].cnt++;
    }
    trie[v].term++;
  }

  string get(int k) {
    string ans;
    int v = 0;
    while(true) {
      if(trie[v].term >= k) return ans;
      k -= trie[v].term;
      for(int c = 0; c < 26; c++) {
        int u = trie[v].next[c];
        if(u == -1) continue;
        if(trie[u].cnt < k) {
          k -= trie[u].cnt;
        } else {
          ans.push_back(c+'a');
          v = u;
          break;
        }
      }
    }
  }
};
// Trie tr;
// tr.trie.emplace_back();

