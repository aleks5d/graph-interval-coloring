#include <algorithm>
#include <iostream>
#include <random>
#include <climits>
#include <vector>

using namespace std;

using ll = long long int;
using ldd = long double;

#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()

const int Count = 1000;
const int Iters = 200;

vector<vector<int>> gr;
vector<pair<int, int>> edges;
vector<int> w;

mt19937 mt(1e9 + 7);

bool randP(ldd p) {
	uint32_t x = mt();
	if ((ldd)x < p * UINT_MAX) return 1;
}

ldd P(ldd Fold, ldd Fnew, ldd t) {
	if (Fnew < Fold) return 1;
	return exp((Fold - Fnew) / t); 
}

ll fillAns(vector<int> perm, vector<ll>& answer) {
	answer.assign(perm.size(), -1);
	for (int i : perm) {
		answer[i] = 0;
		for (int to : gr[i]) {
			if (answer[to] == -1) continue;
			answer[i] = max(answer[i], answer[to] + w[to]);
		}
	}
	ll ans = 0;
	for (int i = 0; i < perm.size(); i++)
		ans += w[i] + answer[i];
	return ans;
}

pair<int, int> genTr(int n, vector<int>& p) {
	if (edges.size() == 0) return {0, 0};
	int x = mt() % edges.size();
	pair<int, int> k = {-1, -1};
	for (int i = 0; i < n; ++i) {
		if (p[i] == edges[x].ff)
			k.ff = i;
		if (p[i] == edges[x].ss)
			k.ss = i;
	}
	return k;
}

ldd tempDown(ldd t) {
	return t / 2;
}

int main() {
	int n, m;
	cin >> n >> m;

	w.resize(n);
	for (int i = 0; i < n; ++i) cin >> w[i];

	gr.resize(n);
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a;
		--b;
		gr[a].push_back(b);
		gr[b].push_back(a);
		edges.push_back({a, b});
	}

	vector<ll> answer;
	vector<ll> currw;
	ldd ans;
	ldd curra;

	currw.resize(n);
	answer.resize(n);
	vector<int> perm(n);
	
	for (int i = 0; i < n; ++i) perm[i] = i;
	random_shuffle(all(perm));

	ans = fillAns(perm, answer);


	ldd t = 1e18;

	for (int i = 0; i < Iters; ++i) {
		for (int j = 0; j < Count; ++j) {
			pair<int, int> tr = genTr(n, perm);
			swap(perm[tr.ff], perm[tr.ss]);
			curra = fillAns(perm, currw);
			if (!randP(P(ans, curra, t))) {
				swap(perm[tr.ff], perm[tr.ss]);
			}
		}
		t = tempDown(t);
	}

	ll trueAns = 0;
	for (int i = 0; i < n; ++i) trueAns = max(trueAns, answer[i] + w[i]);
	cout << trueAns << "\n";
	for (int i = 0; i < n; ++i) cout << answer[i] << " ";
	cout << '\n';
}
