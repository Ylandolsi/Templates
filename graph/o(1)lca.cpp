
// 1 indexed !! u , v dont decrease them !  
const int LOG = 20 ; 
int parents[N] , depth[N],  node2ind[N] ,   spt[N][LOG] ,  lg[N];
vector<int>ind2node ; 
struct processLca{

    void process(){
        dfs2(1); 
        buildspt();
    }
    void dfs2(int u, int dpth=0, int p=0){
        parents[u] = p ; 
        node2ind[u] = (int) ind2node.size();
        depth[u]=dpth;
        ind2node.push_back(u);
        for(int v:adj[u]){
            if(v==p)
                continue;
            dfs2(v, dpth+1, u);
            ind2node.push_back(u);
        }
    }

    void buildspt(){
        lg[0]=-1;
        for(int i=0;i<ind2node.size();i++){
            spt[i][0]=i;
            lg[i+1]= lg[i]+ !(i&i+1);
        }
        for(int j=1;(1<<j)<=ind2node.size();j++){
            for(int i=0;i+(1<<j)<=ind2node.size();i++){
                int a = spt[i][j-1];
                int b = spt[i+(1<<(j-1))][j-1];
                spt[i][j] = (depth[ind2node[a]]<depth[ind2node[b]] ? a:b);
            }
        }
    }

    int SPTMQ(int a , int b){
        int sz = b-a+1;
        int l = lg[sz];
        a = spt[a][l];
        b = spt[b-(1<<l)+1][l];
        return (depth[ind2node[a]]<depth[ind2node[b]] ? a:b);
    }

    int getLCA(int u , int v){
        int a = node2ind[u];
        int b = node2ind[v];
        if(a>b)
            swap(a,b);
        return ind2node[SPTMQ(a,b)];
    }
};

    processLca LCA ; 
    LCA.process();