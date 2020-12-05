#include <algorithm>
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

	vector<int> answer;
	int ans = 1e9;
	currw.resize(n);
	vector<int> perm(n);
	for (int i = 0; i < n; ++i) perm[i] = i;

	do {
		currw.assign(n, -1);
		for (int i : perm) {
			currw[i] = 0;
			for (int to : gr[i]) {
				if (currw[to] != -1) {
					currw[i] = max(currw[i], currw[to] + w[to]);
				}
			}
		}
		int mx = 0;
		for (int i = 0; i < n; ++i) {
			mx = max(mx, currw[i] + w[i]);
		}
		if (mx < ans) {
			ans = mx;
			answer = currw;
		}
	} while (next_permutation(all(perm)));

	cout << ans << "\n";
	for (int i = 1; i <= n; ++i) cout << answer[i] << " ";
	cout << '\n';
}
