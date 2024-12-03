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

	/*if rollback used */ int get(int x) { return x == p[x] ? x : get(p[x]); }
	/*else */ // int get(int x) { return p[x] = ( x == p[x] ? x : get(p[x])) ; }

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




class EvalDsu {
// https://youtube.com/watch?v=Z2CFwayR8P0&t=495s
  public:
	vector<int> p , vals ; 
    fucntion<int ( int , int )> merge ; 

    void init ( int n  , function<int ( int , int ) > operation  ){
        p.resize(n+2) ; 
        vals.resize(n+2);
        iota(p.begin(), p.end(), 0);
        merge = operation ; 
        // merge is a fucntion between the values of node u and node v 
        // when we connect u , v , edge between them = merge ( u ,v ) ;
    }

    // cordinate compression 
    // and merging all value from U to top Leader of current connected compo 

    int find_set ( int u ){
        if ( p[u] != u ){
            int Topleader = find_set(p[u]) ;
            vals[u] += vals[p[u]] ;
            p[u] = Topleader ; 
        }
        return p[u] ; 
    }


    bool same  (int u , int v ){
        return ( find_set(u) == find_set(v)) ; 
    }


    // we will add an edge between 
    //  ( the leader of b , a )   


	void unite(int a, int b) {
        
        
        // b is the leader of Set 1 
        int leaderb  = find_set(b) ; 

		if (same(  a , leaderb )  ) return ;  
		vals[leaderb] += merge( a,  leaderb ); 
        p[leaderb] = a;
	}

    // Evaolution of the path from u to its leader 
    // in log n 
    int eval ( int u ){
        find_set(u);
        return vals[u] ; 
    }


};

// exmpale ; 
/*
    int main( ){
        int n ; cin >> n ;
        Evaldsu ( n , [] (int u , int v ){
            return abs ( u - v ); 
        }) ;


        // after mergin updates ! 
        int u ; 
        cout <<dsu.eval(u) ; s
    }
*/




