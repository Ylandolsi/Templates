/*  We can reroot the tree by the median of The dimater ! 
    to work on some proprities !
    
*/

vector<vi>adj(n+1);
vi par(n+1) ;
for ( int i = 1 ,  u , v ; i< n ; i++ ){
    cin >> u >> v ;
    adj[u].push_back(v);
    adj[v].push_back(u);
}
int largest = 0 , mx = -1   ; 
int largest_ = 0 , mx_= -1   ; 
auto dfs =[&] ( int u , int p , int dp ,    auto & self )-> void {
    if ( mx < dp ) {
        largest = u , mx = dp ;
    }
    for ( auto & child : adj[u]){
        if  (child == p ) continue;
        self ( child , u , dp +1 , self);
    }
};  
dfs ( 1 , 1 , 1 , dfs ); 
auto dfs_ =[&] ( int u , int p , int dp ,    auto & self )-> void {
    if ( mx_ < dp ) {
        largest_ = u , mx_ = dp ;
    }
    par[u] = p ; 
    for ( auto & child : adj[u]){
        if  (child == p ) continue;
        self ( child , u , dp +1 , self);
    }
}; 
dfs_ ( largest , largest , 1 , dfs_ ); 
vi diamter ; 
while  ( 1 ){
    diamter.push_back(largest_);
    if ( par[largest_]  == largest_ )break ;
    largest_ = par[largest_]; 
}