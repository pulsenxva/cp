#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define pii pair<int, int> 
#define isz(x) (int)(x).size()
#define vi vector<int>

const ll inf = 2e18;
const int mx = 500000;
const ll mod = 998244353;
vector<vector<int> > G;
vector<int> used;
// vector<int> c;
vector<int> dp;
vector<int> er;
int cnt, mn, cntm;
bool flag = 1;

ll gcd(ll a, ll b) {
	if(b != 0) return gcd(b, a%b);
	else return a;
}

ll lcm(ll a, ll b) {
	return (a/gcd(a, b)) * b;
}

int comp(pair<int, double> a, pair<int, double> b) {
	if(a.second != b.second) return a.second > b.second;
	else return a.first < b.first;
}

void eratosfen(ll n, vector<ll>& primes) {
	er.assign(n+1, 0);
	er[0] = er[1] = 1;
	for(ll i = 2; i <= n; i++) {
		if(!er[i]) {
			primes.pb(i);
			for(ll j = 2*i; j <= n; j += i) {
				er[j] = 1;
			}
		}
	}
}

/* 
								Apple Division
There are n apples with known weights. Your task is to divide the apples into 
two groups so that the difference between the weights of the groups is minimal.
Input
The first input line has an integer n: the number of apples.
The next line has n integers p_1,p_2,\dots,p_n: the weight of each apple.
Output
Print one integer: the minimum difference between the weights of the groups.
Constraints

1 <= n <= 20

Example
Input:
5
3 2 7 4 1

Output:
1
*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
	int n;cin >> n;
	vi v(n);
	for(auto& d: v) cin >> d;
	ll ans = inf;
	
	// bitmasks
	for(int mask = 0; mask < (1 << n); mask++) {	
		ll dif = 0;
		for(int i = 0; i < n; i++) {
			if(mask & (1 << i)) dif += v[i];
			else dif -= v[i];
		}
		ans = min(ans, abs(dif));
	}
	cout << ans << '\n';
}











