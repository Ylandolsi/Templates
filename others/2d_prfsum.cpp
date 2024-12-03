

template <class S>
struct prefix_2d {
    vector<vector<S>> d;
    int n,  m ; 
 
    prefix_2d(vector<vector<S>>& a) {
        // a 1 indexed 
        n = a.size(), m = a[1].size();
        d= a ; 
        
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++)
                d[i][j] = d[i][j] + d[i][j - 1] ; 
        
        for (int j = 1; j < m; j++)
            for (int i = 1; i < n; i++)
                d[i][j] = d[i][j] + d[i-1][j] ; 
        
    }
    // 1 indexed 
    //[i1    i2]
    //[        ]
    //[j1    j2]
    S prod(int i1, int j1, int i2, int j2) {
        if ( i1 <= 0 or j1 <= 0 or i2 >= n or j2 >= m ) return -1 ; 
        return d[i2][j2] + d[i1-1][j1-1]
            - d[i2][j1-1] - d[i1-1][j2];
    }

        // if u want to apply diffrence array on 2 d prfix sum 
    /*
        pref[i][j]++ prf[i][j+k] -- 
        prf[i+k][j]-- prf[i+k][j+k]++
    */

};

// rotate it ! 
vector<vector<int>> rotate_it_45deg ( vector<vector<int>>&grid ){
    int n = grid.size();
    vector<vector<int>> rotated(2*n + 1, vector<int>(2*n + 1 ));
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
        rotated[i + j+1][i-j + n + 1] = grid[i][j];
    
    return rotated ;
}
