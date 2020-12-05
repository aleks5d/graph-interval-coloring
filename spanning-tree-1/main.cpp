#include <iostream>
#include <vector>

using namespace std;

using ll = long long int;

#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()

vector<vector<int>> gr;
vector<int> w;

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

int main() {
	int n, m;
	cin >> n >> m;

	w.resize(n + 1);
	for (int i = 1; i <= n; ++i) cin >> w[i];


	vector<pair<int, int>> ed;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		ed.push_back({a, b});
	}

	for (int i = 1; i <= n; ++i) {
		ed.push_back({0, i});
	}
	m += n;

	vector<int> answer;
	int ans = 1e9;

	if (m > 50) {
		cout << "To big input\n";
		return 0;
	}

	for (ll i = (1LL << n) - 1; i < (1LL << m); ++i) {
		if (__builtin_popcountll(i) != n) continue;
		gr.clear();
		gr.resize(n + 1);
		currw.clear();
		currw.resize(n + 1, -1);
		for (int j = 0; j < m; ++j) {
			if (i & (1LL << j)) {
				gr[ed[j].ff].push_back(ed[j].ss);
				gr[ed[j].ss].push_back(ed[j].ff);
			}
		}
		for (int j = 1; j <= n; ++j) {
			gr[0].push_back(j);
		}
		dfs(0);
		int mx = 0;
		for (int i = 0; i <= n; ++i) {
			if (currw[i] == -1) {
				mx = -1;
				break;
			}
			mx = max(mx, currw[i] + w[i]);
		}
		if (mx == -1) continue;

		for (auto [a, b] : ed) {
			if (cross(currw[a], currw[a] + w[a], currw[b], currw[b] + w[b])) {
				mx = -1;
				break;
			}
		}

		if (mx == -1) continue;

		if (mx < ans) {
			ans = mx;
			answer = currw;
		}
	}
	cout << ans << "\n";
	for (int i = 1; i <= n; ++i) cout << answer[i] << " ";
	cout << '\n';
}
