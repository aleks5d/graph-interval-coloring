#include <iostream>
#include <vector>

using namespace std;

using ll = long long int;

#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()

vector<pair<int, int>> ed;
vector<int> w;
vector<int> answer;
vector<vector<int>> gr;
int ans = 1e9;
vector<int> currw;

void dfs(int v, int t = 0) {
	currw[v] = t;
	for (int to : gr[v]) {
		if (currw[to] == -1) {
			dfs(to, t + w[v]);
		}
	}	
}

bool cross(int a, int b, int c, int d) {
	return max(c, a) < min(b, d);
}

void check(int pos = 0, int have = 0) {
	if (have + 1 == w.size()) {
		currw.assign(currw.size(), -1);
		dfs(0);

		int mx = 0;
		for (int i = 0; i < w.size(); ++i) {
			if (currw[i] == -1) {
				mx = -1;
				break;
			}
			mx = max(mx, currw[i] + w[i]);
		}
		if (mx == -1) return;

		for (auto [a, b] : ed) {
			if (cross(currw[a], currw[a] + w[a], currw[b], currw[b] + w[b])) {
				mx = -1;
				break;
			}
		}

		if (mx == -1) return;

		if (mx < ans) {
			ans = mx;
			answer = currw;
		}
		return;
	}
	if (pos == ed.size()) return;
	gr[ed[pos].ff].push_back(ed[pos].ss);
	gr[ed[pos].ss].push_back(ed[pos].ff);
	check(pos + 1, have + 1);
	gr[ed[pos].ff].pop_back();
	gr[ed[pos].ss].pop_back();
	check(pos + 1, have);
}

int main() {
	int n, m;
	cin >> n >> m;

	w.resize(n + 1);
	for (int i = 1; i <= n; ++i) cin >> w[i];

	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		ed.push_back({a, b});
	}

	for (int i = 1; i <= n; ++i) {
		ed.push_back({0, i});
	}
	m += n;

	gr.resize(n + 1);
	currw.resize(n + 1, -1);
	check();

	cout << ans << '\n';
	for (int i = 1; i <= n; ++i) cout << answer[i] << " ";
		cout << '\n';
}