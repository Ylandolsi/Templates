// https://codeforces.com/group/HcnH7vLzrr/contest/562768/problem/C2
const int N = 1e5 + 10 ; 
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
        
        bSize = (int)sqrt(n);

        blocks = (n+bSize-1)/bSize;
        b.resize( blocks);
        
        // we wll do sqrt decomp on indcies ! 

        for( int i = 0; i< n; i++ ){
            int realInd = idx[i] ; 
            b[i/bSize].push_back(a[realInd ]);
        } 


        // inside each block the values are sorted ! 
        // sort them  bases on the values ! 
        for(int i = 0 ; i <  blocks ; i++ ){
            sort(b[i].begin(),b[i].end());
        }
    }

    // if we want to look the block S
    // loop over indicies sorted ( not the values  sorted ) 
    // LoopLikeOriginalOrder
    int walk(int s ,int l,int r,int k){
        for(int i = s ; i <  n ; i++){
            int realInd = idx[i] ; 

            if ( a[realInd] >= l and a[realInd] <= r ){
                k-- ;
            } 

            if ( 0 == k ) {
                return realInd  +1  ;  
            }
        }
        return -1;
    }
    
    // s start of indicie , e,end 
    // [ l , r ] values should be in thsi range 
    int get(int s,int e,int k , int l , int r ){


        // we will convert them to their current position in our Vector idx ! 
        // ( because we applied the square root decomp on the vector idx )

        // bcz IDX only contains certain elements not all of them 
        // s become smallest such idx[i] >= s 
        // e become greaters such idx[i] <= e
        s = lower_bound(all(idx) , s)  - idx.begin();
        e = upper_bound(all(idx) , e ) - idx.begin() - 1  ;


        if(n == 0 || e < s)
            return -1;

        int stB = s/bSize;
        int enB = e/bSize;

        // how many values verfied condition we met so far 
        int cnt = 0 ;

        if(stB == enB){
            // loop normal without using blocks : 
            for( int i = s ; i <= e ; i++ ){
                // we use their correnspoing real indicies 
                int realInd = idx[i] ; 

                if ( a[realInd] >= l and a[realInd] <= r ){
                    cnt++ ; 
                } 

                if ( cnt == k ) {
                    return realInd  +1  ;  
                }
            }

            // we didint find the Kth indices such satisfy the condition 
            return  - 1 ; 
            
        }


        for(int i = s ; i < (stB+1) * bSize ; i++ ){
            int realInd = idx[i] ;

            if ( a[realInd] >= l and a[realInd] <= r ){
                cnt++ ; 
            } 
            
        }
        if(cnt >=k  )  // k-th indice is found on the  first block starting from indcie S ! 
            return walk(s,l,r,k);
        
        k -= cnt ; 

        for(int i = (stB+1) ; i < enB ; i++){
            // inside the i-th block the values are sorted ! 
            cnt = upper_bound(b[i].begin(),b[i].end(),r) - lower_bound(b[i].begin(),b[i].end(),l);

            if(cnt >= k )   // k-th indice is found on the  i-th block 
                return walk(i*bSize,l,r,k);

            k -= cnt ; 
            
        }
     
        cnt = 0 ; 
        for(int i =  enB * bSize ; i <= e ; i++ ){
            int realInd = idx[i] ;

            if ( a[realInd] >= l and a[realInd] <= r ){
                cnt++ ; 
            } 
        }
        if(cnt >=k ) // walk on last block 
            return walk(enB * bSize,l,r,k);

        k-= cnt ; 
        return -1;
    }
};

vector<SqaureRootDecomp>Xs(N) ;
