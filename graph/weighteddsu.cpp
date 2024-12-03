// https://qiita.com/drken/items/cce6fc5c579051e64fab#abc-087-d-people-on-a-line
// https://www.youtube.com/watch?v=oLsk9w94aY4
template<class T> struct UnionFind {
	vector<int> par;
	vector<int> rank;
	vector<T> diff_weight;

	UnionFind(int n = 1, T SUM_UNITY = 0) {
		init(n, SUM_UNITY);
	}
	void init(int n = 1, T SUM_UNITY = 0) {
		par.resize(n); rank.resize(n); diff_weight.resize(n);
		for (int i = 0; i < n; ++i) par[i] = i, rank[i] = 0, diff_weight[i] = SUM_UNITY;
	}
	int root(int x) {
		if (par[x] == x) {
			return x;
		}
		else {
			int r = root(par[x]);
			diff_weight[x] += diff_weight[par[x]];
			return par[x] = r;
		}
	}

    //weight till the parent ! 
	T weight(int x) {
		root(x);
		return diff_weight[x];
	}

	bool issame(int x, int y) {
		return root(x) == root(y);
	}

    // Merge x and y such that weight(y) - weight(x) =  w
	bool merge(int x, int y, T w) {
		w += weight(x); w -= weight(y);
		x = root(x); y = root(y);
		if (x == y) return false;
		if (rank[x] < rank[y]) swap(x, y), w = -w;
		if (rank[x] == rank[y]) ++rank[x];
		par[y] = x;
		diff_weight[y] = w;
		return true;
	}

	T diff(int x, int y) {
        if (!issame(x,y)) return  0 ; // dosent belong to same connected compononent 
		return weight(y) - weight(x);
	}
};
