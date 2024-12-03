#include <bits/stdc++.h>
using namespace std ; 
#ifndef ONLINE_JUDGE
#include "/home/ylandolsi/debugger.cpp"
#else
#define debug(...)
#define debugArr(...)
#define show(...)
#endif
template<typename... T>void read(T&... args) {((cin >> args), ...);}
template<typename... T>void print(T&&... args) {((cout << args ), ...);}
#define int long long 
typedef array<int, 2> pi ; typedef vector<int> vi ; 
#define for_( i , debut,  fin) for( int i = debut ; i <  fin ; i++   )
#define all(x) x.begin(), x.end() 
#define getunique(vt)  vt.erase(unique(all(vt)), vt.end()) 
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
//--------------
struct info {
    int weight;
    int nd;
    int rided;
    bool operator<(const info& b) const  {
        // sorted increasing by weights cause it s priorty queue ( maklouba ) !
        return weight > b.weight;
        /*
            else {
                sort normal ken priorty queue raw ebch tsorti dec
                ken veftor wala heja tsorti dec

            }
        */
    }
};
void solve( int t ){
    priority_queue<info>pq;
    pq.push({10,1,0});
    pq.push({10,2,0});
    pq.push({20,2,0});
    while ( pq.size() ){
        auto [a,b,c] = pq.top();
        pq.pop();
        debug(a,b,c);
    }
}
// ---------



struct info {
	int to;
	int weight;
	bool operator<(const info &o) const {
		if ( weight == o.weight){ 
            if ( to != o.to ) return to>o.to ; 
        } 
        return weight < o.weight;
	}
};
/*
compartor in priorty queue are reversed 
a < b  make it decreasing not increasing  

but in set & vector its normal !
*/

int32_t main(){
    priority_queue<info>pq;
    pq.push({0,10});
    pq.push({0,15});
    pq.push({5,15});
    pq.push({1,15});
    pq.push({1,15});
    vector<info>aa ;
    aa.push_back({0,10});
    aa.push_back({0,15});
    aa.push_back({5,15});
    aa.push_back({1,15});
    aa.push_back({1,15});
    sort(all(aa));
    while (pq.size()){
        auto [to , weight]  = pq.top();
        pq.pop();
        debug(to,weight);
    }
    cout <<"here\n";
    for  (auto&[e,b]:aa) debug(e,b);
    set<info>aaa ;
    aaa.insert({0,10});
    aaa.insert({0,15});
    aaa.insert({5,15});
    aaa.insert({1,15});
    aaa.insert({1,15});

    cout <<"here\n";
    for  (auto&[e,b]:aaa) debug(e,b);
}