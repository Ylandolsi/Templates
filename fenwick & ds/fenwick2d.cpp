struct Fenwick2D {
    // one indexed !
    int n, m;
    vector < vector <int > > tree;
    Fenwick2D(int n_, int m_) : n(n_), m(m_), tree(n + 1, vector<int>(m + 1)) {}
    int get(int i, int j) {
        if(i <= 0 || i > n || j <= 0 || j > m) return 0;
        int sum = 0;
        for(; i; i -= (i & -i))
            for(int k = j; k; k -= (k & -k))
                sum += tree[i][k];
        return sum;
    }
    void upd(int i, int j, int val) {
        for(; i <= n; i += (i & -i))
            for(int k = j; k <= m; k += (k & -k))
                tree[i][k] += val;
    }
    int ans ( int i1 , int j1 , int i2 , int j2 ){
        int a1 = get(i2 , j2);
        int a2 = get(i1 -1 , j2 ); 
        int a3 = get(i2 , j1-1);
        int a4 = get(i1-1 , j1 -1 ) ; 
        return a1 - a2 -a3 +a4 ;
    }
};