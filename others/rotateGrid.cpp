    int n = 3 ;
    vector<vector<int>> grid(n+1, vector<int>(n+1));
    int tmp = 1 ;
    for ( int i = 0 ; i < n ; i++ ) for ( int j = 0 ; j <n ;j++ ) grid[i][j] = tmp++ ; 
    vector<vector<int>> rotated(2*n + 1, vector<int>(2*n + 1 ));
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
        rotated[i + j+1][i-j + n + 1] = grid[i][j];
    debug(grid);
    debug(rotated);

/*


    exp with roatiting fenwick : 
    https://codeforces.com/contest/1864/submission/220563562



    struct Fenwick2D {
    int n, m;
    vector <vi> tree;
    Fenwick2D(int n_, int m_) : n(n_), m(m_), tree(n + 1, vi(m + 1)) {}
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
};
 
void solve() {
    int n = 3 ;
    vector<vector<int>> grid(n+1, vector<int>(n+1));
    int tmp = 1 ;
    for ( int i = 0 ; i < n ; i++ ) for ( int j = 0 ; j <n ;j++ ) grid[i][j] = tmp++ ; 
    vector<vector<int>> rotated(2*n + 1 , vector<int>(2*n + 1 ));
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
        rotated[i + j+1][i-j + n + 1] = grid[i][j];
    debug(grid);
    debug(rotated);


    Fenwick2D tree(2 * n, 2 * n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            // if(tree.get(i + j + 1, i - j + n + 1) ^ int(a[i][j] == '1')) {
            //     tree.upd(i + j + 1, i - j + n + 1, 1);
            //     ans++;
            // }
            tree.upd(i + j + 1, i - j + n + 1, grid[i][j]);
            //tree.upd(i+1 , j+1 , grid[i][j]);

        }
    }
    int i = 2 , j = 1 ; 
    int ii = i + j + 1, jj = i - j + n + 1  ;
    int xx = tree.get(ii , jj ); 
    debug(xx);
    // 6 + 6+ 4 + 5 +8 
    // 9 + 12 + 8 
}

*/