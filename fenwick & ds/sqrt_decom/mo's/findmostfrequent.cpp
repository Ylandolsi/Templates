
// https://codeforces.com/contest/2009/submission/280545696
const int MAXA = 200005; // max element in array A 
const int MAXN = 200005;

struct Query{
    int l, r, i , ans ; 
    bool operator <(Query b) const{
        if(l / sq != b.l / sq)
            return l / sq < b.l / sq;
        return l / sq % 2 ? r < b.r : r > b.r;
    }
};
vector<Query> query ; 
 
inline void moAlgorithm( int n,  vi a ,  int q)
{
	auto getBlockIndex = [=]( Query &q) {return q.l / sq; };
	sort(all(query));

	int count[MAXA + 1];
	memset(count, 0, sizeof(count));
	int numberOfValuesWithCount[MAXN + 1];
	memset(numberOfValuesWithCount, 0, sizeof(*numberOfValuesWithCount) * (n + 1));
	int maxCount = 0;
 
	auto remove = [&]( int index) {
		--numberOfValuesWithCount[count[a[index]]];
		if (count[a[index]] == maxCount && numberOfValuesWithCount[count[a[index]]] == 0){
			--maxCount;
		}
		--count[a[index]];
		++numberOfValuesWithCount[count[a[index]]];
 
	};
	auto add = [&]( int index) {
		--numberOfValuesWithCount[count[a[index]]];
		if (count[a[index]] == maxCount){
			++maxCount;
		}
		++count[a[index]];
		++numberOfValuesWithCount[count[a[index]]];
	};
 
	int left = 0, right = -1;
 
	for (int i = 0; i < q; ++i)
	{
		int r = query[i].r  , l = query[i].l ; 
		while(right < r)  add(++right);
        
        while(left > l)   add(--left);
        
        while(right > r)  remove(right--);
        
        while(left < l)   remove(left++);
        
		query[i].ans = maxCount;
	}
 
	sort(all(query), [&]( Query &a,  Query &b) {
		return a.i < b.i;
	});
}