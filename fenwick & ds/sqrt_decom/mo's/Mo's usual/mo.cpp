

// https://codeforces.com/contest/2014/submission/282747596
/*
    Runtime: O((n+q)*sqrt(n))
    Runtime w/ hilbert: O(n*sqrt(q))
*/


const int MAXA = 2000005 , N = (int)1e6 + 2 , sq = sqrt(N) ;
int cte[MAXA + 1] , ansi[MAXA + 1 ];
const int logmaxn = log2(N) ; 

inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t res = seg * subSquareSize;
	int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
	res += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return res;
}


struct Query{
    int l, r, i , ans , ordHelb; 
    bool operator <(Query b) const{
        if(l / sq != b.l / sq)
            return l / sq < b.l / sq;
        return l / sq % 2 ? r < b.r : r > b.r;
    }
	/*	
		bool operator <(Query b) const{
			// hilbert curve
			return ordHelb < b.ordHelb;

    	}
	
	*/
};

vector<Query> query ; 
inline void moAlgorithm( int n,  vi &a ,  int q)
{
	auto getBlockIndex = [=]( Query &q) {return q.l / sq; };
	sort(all(query));

	// intilize !
	//for ( auto &d : a ) occ[d] = 0 , ansi[d] = 0 ; 
	int anshere = 0;
 
	auto remove = [&]( int index) {
		// excuted N sqrt N
 
	};
	auto add = [&]( int index) {
		// excuted N sqrt N
	};
	auto getans = [&] (){
		return anshere; 
	};
	// 0 indexed 
	int left = 0, right = -1;
	// 1 indexed 
	int left = 1, right = 0;
	for (int i = 0; i < q; ++i)
	{
		/*
			Be careful sometimes it depends 
			add from left         [ a , b ] add element beside a 

			or add from right     [ a ,  b ] add element beside b

			sometimes its diffirent ! 
			
		*/
		int r = query[i].r  , l = query[i].l ; 
		while(right < r)  add(++right);
        
        while(left > l)   add(--left);
        
        while(right > r)  remove(right--);
        
        while(left < l)   remove(left++);
        
		// excuted Q times ! 
		query[i].ans = getans();
	}
 
	sort(all(query), [&]( Query &a,  Query &b) {
		return a.i < b.i;
	});
}

// for  (int i= 0 ; i < q ;i++ ){
// 	int l , r ;read(l,r);
// 	query[i].i = i ; 
// 	query[i].l = l , query[i].r = r , query[i].ordHelb = hilbertOrder(l, r, logmaxn, 0);
// }