// 0 indexd ( nodes form [ 0 , n-1 ])
for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (d[i][k] < INF && d[k][j] < INF)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
        }
    }
}


int d[n+1][n+1] ;
    vector adj(n+1 , vector<pi>()); 
    F ( i , 0 , n ) F (j , 0 , n ) if ( i == j ) d[i][j] = 0 ; else d[i][j] = INF ;
    F ( i , 1 , m ){
        int u , v, w ; 
        cin >> u >> v >> w;  
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    F ( i , 1 , n ) 
        for ( auto &[e, w ]: adj[i]) d[i][e] = min( d[i][e] , w ) ;
    // 1 indexed ! nodes from (1 , n ) ;
    for (int k = 1; k <= n; ++k) 
        for (int i = 1; i <= n; ++i) 
            for (int j = 1; j <= n; ++j) 
                if (d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 