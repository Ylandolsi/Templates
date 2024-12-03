
// example !
// https://cses.fi/problemset/result/11090235/

const int N = 3e5 + 10; 
const int MAX_MASK = (1 << 26) + 1;
int n ; 
// vector<pi>adj[N]; 
// vi nodes ;
int nodes[N]; 
int prof[N];
int depth[N] , parent[N] , pfxor[N] , in[N] , out[N] ,big[N] ;   
int freq[MAX_MASK]  ;  
int timer = -1 ;
int ans = 0 ; 
int current_LCA ; 
struct smallToBIG
{
    // problem I code & conqeur 1.0  
    void calsz ( int nd , int pr , int xpf   ){
        depth[nd] = 1 ;
        pfxor[nd] = xpf ; 
        in[nd] = ++timer ; 
        prof[nd] = prof[pr] + 1 ;
        // nodes.push_back(nd);
        nodes[in[nd]] = nd ;
        int mx = -1 , u = -1 ; 
        for ( auto &[ch,_]:  adj[nd]){
            if ( ch == pr ) continue;
            calsz(ch , nd  , xpf ^ _   );
            parent[ch] = nd ;   
            depth[nd] += depth[ch];
            if (mx < depth[ch]) {
                u = ch ;
                mx = depth[ch];
            } 
        }
        out[nd] = timer ; 
        big[nd] = u;
    }
    
    // void GetAnsOfpathEndingAtUWith LCA=current node in the function 
    // small to big ! ( passed in the paramtre !!! ) 
    void GetPath(  int nodehere ){
        ans += freq[pfxor[nodehere]];
        for ( int j = 0 ; j < 26 ; j++ ){
            int x = 1LL << j ; 
            int need2 = pfxor[nodehere] ^ x ; 
            ans += freq[need2];
        }
    }
    void Addcontribution( int node ){
        freq[pfxor[node]]++ ;  
    }
    void Dellcontribution ( int node ){
        freq[pfxor[node]]--;
    }
    void smalltobig(int node, int p, int keep = 1) {
        for ( auto &[ch,w]:adj[node]){
            if ( ch == p or ch == big[node] )continue; 
            else smalltobig(ch,node,0);
        }
        if ( big[node] != -1 )  smalltobig(big[node],node,1);
        
        current_LCA = node ;
        GetPath(node); // path between current node(in this exp =  1 ) and nodes that 
                        // are down in the subtree of BIG child only !! ( same path !)
                        // because contributions of light nodes are not added yet !
                        /*
                                1
                              / |
                              5 2
                            /  |
                          6    3
                        /
                       7 
                        for example 1-5 1-6 1-7 
                        simple path !!
                        */
        
        Addcontribution(node); // we have to add the contribution before moving to 
                              // getpath of childs !
                              // because it have to  be included for example
                              // 3-1
        for ( auto &[ch,_] :adj[node]){
            if ( ch == p or ch == big[node] ) continue;
            // match child subtree ch with previiosu childs subtree
            for ( int i = in[ch]; i <= out[ch] ; i++ ){
                int nodehere = nodes[i];
                GetPath(nodehere);

            }
            // add elements of current child subtree ch 
            // bcz when we are moving to next ch
            // we will need the elements of all previous subtrees ! 
            
            for ( int i = in[ch] ; i <= out[ch] ;i++ ){
                int nodehere = nodes[i];
                Addcontribution(nodehere);
            }
        }
        if ( keep == 0 ) {
            // if the current node is not a big child of its ancestor  
            // remove its contrbution before going back to the ancestor ! 
            // this one will be done at most one time for each done ! 
            // so its like running a dfs from that node at most one extra time !


            // each node afer all the work done will be deleted at most logn times ! 
            // because exactly after the deletion the node will be merged when we go back
            // to its ancestor ! 
            // and each node will be merged in worst logn times !  
            for (int i=in[node];i<=out[node];++i) {
                int nodehere=nodes[i];
                Dellcontribution(nodehere);
            }
        }
    }
};
