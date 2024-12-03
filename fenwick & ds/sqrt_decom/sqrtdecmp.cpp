https://github.com/defnotmee/definitely-not-a-lib/blob/main/library/data%20structures/sqrt_decomp.hpp
/*
from https://github.com/defnotmee/definitely-not-a-lib

Divides an array into blocks of sqrt. In this case,
its doing range addition update and range maximum query.

TODO: clean code, make it more general
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif


template<typename T = ll>
struct decomp{
    vector<T> elem;
    vector<T> block, lz;
    int LEN = 420 ; 

    decomp(int n = 0){
        LEN = sqrt(n ); 
        elem = vector<T>(n);
        block = vector<T>((n+LEN-1)/LEN);
        lz = vector<T>((n+LEN-1)/LEN);
    }

    void reconstruct(int bid){
        block[bid] = 0;
        for(int i = bid*LEN; i < min(int(elem.size()), (bid+1)*LEN); i++){
            block[bid] = max(block[bid], elem[i]);
        }
        block[bid]+=lz[bid];
    }

    void update(int l, int r, T x){
        int bl = l/LEN+1, br = r/LEN;

        if(bl >= br){
            for(int i = l; i <= r; i++)
                elem[i]+=x;

            reconstruct(br);
            if(bl-1 != br)
                reconstruct(bl-1);
        } else {
            for(int i = l; i < bl*LEN; i++)
                elem[i]+=x;
            for(int i = bl; i < br; i++)
                lz[i]+=x, block[i]+=x;
            for(int i = br*LEN; i <= r; i++)
                elem[i]+=x;

            reconstruct(bl-1);
            reconstruct(br);
        }
    }

    T query(int l, int r){
        int bl = l/LEN+1, br = r/LEN;
        T ret = T();

        if(bl >= br){
            for(int i = l; i <= r; i++)
                ret = max(ret,elem[i]+lz[i/LEN]);
        } else {
            for(int i = l; i < bl*LEN; i++)
                ret = max(ret,elem[i]+lz[bl-1]);
            for(int i = bl; i < br; i++)
                ret = max(ret,block[i]);
            for(int i = br*LEN; i <= r; i++)
                ret = max(ret,elem[i]+lz[br]);
        }
        return ret;
    }
};




int a[N];
struct SqaureRootDecomp{
    vector <int> idx;
    vector <vector<int> > b;
    int n , bSize , blocks;
    SqaureRootDecomp(){
        bSize = blocks  = 0 ,  n  = 0 ; 
        idx.clear(),b.clear();
    }
    void add(int x){
        // we are pushing the indexses !
         
        idx.push_back(x);
    }
    void build(){

        sort(idx.begin(),idx.end());
        idx.erase(unique(idx.begin(),idx.end()),idx.end());

        n = (int)idx.size();
        
        if(n == 0)
            return;
        
        bSize = sqrt(n);
        blocks = (n+bSize-1)/bSize;
        b.resize((n+bSize-1)/bSize);
        
        // we wll do sqrt decomp on indcies ! 

        for( int i = 0; i< n; i++ ){
            b[i/bSize].push_back(a[idx[i]]);
        } 

        // sort them 
        for(int i = 0 ; i <  blocks ; i++ ){
            sort(b[i].begin(),b[i].end());
        }
    }

    // if we want to look the block S
    // LoopLikeOriginalOrder
    int walk(int s ,int l,int r,int k){
        for(int i = s;i<n;i++){
            if(a[idx[i]] > r || a[idx[i]] < l)
                continue;
            k--;
            if(k == 0)
                return idx[i];
        }
        return -1;
    }
    
    int get(int s,int e,int k){
        if(n == 0 || e < s)
            return -1;

        int stB = s/bSize;
        int enB = e/bSize;

        if(stB == enB){
            for( int i = s ; i <= e ; i++ ){
                
            }

            return ; 
            
        }


        int cnt = 0;
        for(int i = s ; i < (stB+1) * bSize ; i++ ){
            
        }
        if(/*conditon*/) // walk on first block 
            return walk(s,l,r,k);
        

        for(int i = (stB+1) ; i < enB ; i++){
            cnt = upper_bound(b[i].begin(),b[i].end(),r) - lower_bound(b[i].begin(),b[i].end(),l);

            if(/*conditon*/) // walk on the-ith block 
                return walk(i*bSize,l,r,k);
            
        }
     
        for(int i =  enB * bSize ; i <= e ; i++ ){
            
        }
        if(/*conditon*/) // walk on last block 
            return walk(enB * bSize,l,r,k);

        return -1;
    }
};