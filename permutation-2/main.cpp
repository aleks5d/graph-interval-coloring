#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

using ll = long long int;

#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()

vector<vector<int>> gr;
vector<int> w;
vector<int> answer;
int ans = 1e9;

vector<int> currw;
set<int> have;
vector<int> perm;
vector<bool> inperm;

void calc(int pos = 0, int prw = 0) {
	if (have.size() == 0) {
		int mx = 0;
		for (int i = 0; i < perm.size(); ++i) {
			mx = max(mx, w[i] + currw[i]);
		}
		if (mx < ans) {
			ans = mx;
			answer = currw;
		}
		return;
	}
	int k = *have.begin() - 1;
	int t = have.size();
	for (int i = 0; i < t; ++i) {
		int j = *have.upper_bound(k);
		perm[pos] = j;
		inperm[j] = 1;
		currw[j] = 0;
		for (int to : gr[j]) {
			if (inperm[to]) {
				currw[j] = max(currw[j], currw[to] + w[to]);
			}
		}
		if (prw <= currw[j]) {
			have.erase(j);
			calc(pos + 1, currw[j]);
			have.insert(j);
		}
		inperm[j] = 0;
		k = j;
	}
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
	}

	currw.resize(n);
	perm.resize(n);
	inperm.resize(n);
	for (int i = 0; i < n; ++i) have.insert(i);

	calc();

	cout << ans << "\n";
	for (int i = 0; i < n; ++i) cout << answer[i] << " ";
	cout << '\n';
}
