#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> gr;
vector<int> w;

int main() {
	int n, m;
	cin >> n >> m;
	gr.resize(n);
	w.resize(n);
	for (int i = 0; i < n; ++i) {
		cin >> w[i];
	}
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a;
		--b;
		gr[a].push_back(b);
		gr[b].push_back(a);
	}
	vector<int> answer(n);
	vector<int> curr;
	vector<int> was(n);
	int cnt = n;
	int iter = 0;
	int l = 0;

	vector<int> prior(n);
	for (int i = 0; i < n; ++i) prior[i] = i;
	sort(prior.begin(), prior.end(), [&](int a, int b){return w[a] > w[b];});

	while (cnt) {
		++iter;
		curr.clear();
		for (int i : prior) {
			if (was[i]) continue;
			bool good = 1;
			for (int to : gr[i]) {
				if (was[to] == iter) good = 0;
			}
			if (good) {
				was[i] = iter;
				curr.push_back(i);
			}
		}
		cnt -= curr.size();
		int mw = 0;
		for (int i : curr) {
			 mw = max(mw, w[i]);
			 answer[i] = l;
		}
		l += mw;
	}
	cout << l << '\n';
	for (int i : answer) cout << i << " ";
		cout << '\n';
}