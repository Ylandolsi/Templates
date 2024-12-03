https://youtu.be/7gqFcunrFH0?si=m71cSibLMvJg--7_
class DisjointSet {
  public:
	vector<int> p, sz , sizecurrent;
	vector<pair<int &, int>> history;

    int connected_grps , current  ;
    void init ( int n ){
        current = -1 ; 
        connected_grps = n ;
        sz.resize(n+2,1) , p.resize(n+2) , sizecurrent.resize(n+2); 
        iota(p.begin(), p.end(), 0);
    }

	int get(int x) { return x == p[x] ? x : get(p[x]); }

	int unite(int a, int b) {
		a = get(a);
		b = get(b);
		if (a == b) { return false ; }
		if (sz[a] < sz[b]) { swap(a, b); }
		history.push_back({sz[a], sz[a]});
		history.push_back({p[b], p[b]});
		p[b] = a;
		sz[a] += sz[b];
        current++;
        sizecurrent[current] = connected_grps ;
        connected_grps-- ; 
        return true ; 
	}


	void rollback(int removecte ) {
		for ( int j = 0 ; j < removecte  ; j++ ){
            for ( int i = 0 ; i <2 ; i++ ) {
                history.back().first = history.back().second;
                history.pop_back();
            }
            connected_grps = sizecurrent[current];
            current--;
        }
        
	}
};

struct SegmentTree {
    int n; 
    vector<vector<pi>> st;
    SegmentTree(int _n) : n(_n), st(4*n){};
    void update(int p, int i, int j, pi val , int ns , int ne ) {
        if (i > ne || j < ns) return ;

        if (ns >= i && ne <= j){
            st[p].push_back(val);
            return;
        }
        int m = (ns + ne) / 2;
        update(2*p, i, j, val, ns , m );
        update(2*p+1,i, j, val , m+1 , ne );
    }

    void update(int i, int j, pi val) {
        update(1, i, j, val , 0 , n- 1 );
    }

};

void solve( int t ){
    int n , k ; read ( n , k ) ;
    DisjointSet dsu;
    dsu.init(n) ; 
    SegmentTree sg(k+2);
    map<pi , int >mp ; 
    vector<int>query(k+10,-1); 
    vector<pi>ans;
    for  (int i = 0 ; i <k  ; i++ ){
        int a ,b ; 
        char ch ; 
        cin >> ch ; 
        if ( ch =='+'){
            read(a,b);
            if (  a > b  )swap(a,b);
            mp[{a,b}] = i ; 
        } else if ( ch =='-'){
            read( a, b );
            if (  a > b  )swap(a,b);
            int iii = mp[{a,b}] ;
            pi vl = {a,b}; 
            sg.update(iii , i  ,vl ) ; 
            if ( mp.find(vl) != mp.end() )  mp.erase(mp.find(vl));
        } else {
            query[i] = i ;
        }
    }
    for  (auto &d : mp ){
        int iii = d.second ;
        pi vl = d.first; 
        sg.update(iii , k  ,vl ) ; 
    }


    auto dfs = [&] ( auto && dfs  , int id , int l , int r ) -> void {
        int cte = 0 ; 
        for ( auto& d : sg.st[id]){
            if ( dsu.unite(d[0] ,d[1]) )   cte++;
        }
        if ( l == r) {
            if ( query[l] != -1 )
            {
                ans.push_back({query[l] , dsu.connected_grps}) ; 
            }
        } else {
            int md = (l+r)/2;
            dfs ( dfs ,id *2 , l , md );
            dfs ( dfs , id *2 + 1 , md+1 , r );

        }
        dsu.rollback(cte);
    };
    dfs(dfs,  1,0,k+1);
    sort(all(ans));
    for  (auto &d: ans ){
        cout << d[1] << "\n";
    }
}


int32_t main() {
    cin.tie(0), ios_base::sync_with_stdio(0) ;cout << fixed << setprecision(14) ; 
    int t = 1;
    for ( int i = 1 ; i <= t ; i++ ) solve(i); 
}



