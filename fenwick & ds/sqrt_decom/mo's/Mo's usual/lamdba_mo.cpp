
const int N = 1e5;
const int sqr = 320;

struct Query {
  int l, r, a, b, idx;
  Query( int l_  = 0 , int r_ = 0 , int a_= 0 , int b_ = 0 ,   int  idx_ = 0 ){ 
        l = l_ , r = r_ , a = a_ , b = b_ ,  idx = idx_ ; 
  }
  bool operator <(Query b) const{
      if(l / sqr != b.l / sqr)
          return l / sqr < b.l / sqr;
      return l / sqr % 2 ? r < b.r : r > b.r;
  }
};


auto add = [&](int x) {
  int vl = a[x];
};
auto del = [&](int x) {
  int vl = a[x];  
};

auto getans =[&]( ){

};

vector<Query> queries(q);
  for (int i = 0; i < q; i++) {
    int l, r, a, b;
    cin >> l >> r >> a >> b;
    --l; --r; // if u wll work one indexed remove this !  !!!!!!!!!!ss
    queries[i] = {l, r, a, b, i};
}


sort(queries.begin(), queries.end());
vector<pair<int, int>> ans(q);
int cur_l = 0, cur_r = -1;
 
// 1 indexed !int cur_l = 1, cur_r = 0;

for (Query &qr : queries) {
        while (cur_l > qr.l) add(--cur_l);
        while (cur_r < qr.r) add(++cur_r);
        while (cur_l < qr.l) del(cur_l ) ,cur_l++ ; 
        while (cur_r > qr.r) del(cur_r ) ,cur_r-- ; 

    ans[qr.idx] = getans(); 
}