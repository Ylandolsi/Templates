
int n,q,a[N],ans[N];

struct Node{
    int basis[LOG],sz,lazy;
    bool hasLazy;
    Node(){
        lazy = -1;
        sz = 0;
        hasLazy = false;
        fill(basis,basis+LOG,0);
    }
    Node(int x){
        lazy = -1;
        sz = 0;
        hasLazy = false;
        fill(basis,basis+LOG,0);
        for(int i = LOG-1;i>=0;i--){
            if(x & (1<<i)){
                basis[i] = x;
                break;
            }
        }
    }
    void insert(int mask){
        for(int i = LOG-1;i>=0;i--){
            if(mask & (1<<i)){
                if(basis[i] == 0){
                    basis[i] = mask;
                    sz++;
                    break;
                }
                mask ^= basis[i];
            }
        }
    }
    Node(const Node &lt,const Node &rt){
        lazy = -1;
        sz = 0;
        hasLazy = false;
        fill(basis,basis+LOG,0);
        for(int i = 0;i<LOG;i++){
            if(lt.basis[i])
                insert(lt.basis[i]);
            if(rt.basis[i])
                insert(rt.basis[i]);
        }
    }
    void apply(){
        vector <int> tmp;
        for(int i = 0;i<LOG;i++){
            if(basis[i])
                tmp.push_back(basis[i] & lazy);
        }
        fill(basis,basis+LOG,0);
        sz = 0;
        for(auto it:tmp){
            insert(it);
        }
        hasLazy = false;
        lazy = -1;
    }
};
vector <Node> seg;

void prop(int node,int l,int r){
    if(seg[node].hasLazy){
        if(l != r){
            seg[node*2].hasLazy = seg[node*2+1].hasLazy = true;
            seg[node*2].lazy &= seg[node].lazy;
            seg[node*2+1].lazy &= seg[node].lazy;
        }
        seg[node].apply();
    }
}
void build(int node = 1,int l = 1,int r = n){
    if(l == r){
        seg[node] = Node(a[l]);
        return;
    }
    int md = (l+r)/2;
    build(node*2,l,md);
    build(node*2+1,md+1,r);
    seg[node] = Node(seg[node*2],seg[node*2+1]);
}

void updateAND(int s,int e,int val,int node = 1,int l = 1,int r = n){
    prop(node,l,r);
    if(l > e || r < s)
        return;
    if(l >= s && r <= e){
        seg[node].hasLazy = true;
        seg[node].lazy &= val;
        prop(node,l,r);
        return;
    }
    int md = (l+r)/2;
    updateAND(s,e,val,node*2,l,md);
    updateAND(s,e,val,node*2+1,md+1,r);
    seg[node] = Node(seg[node*2],seg[node*2+1]);
}
void updateIDX(int idx,int val,int node = 1,int l = 1,int r = n){
    prop(node,l,r);
    if(l > idx || r < idx)
        return;
    if(l == r){
        seg[node] = Node(val);
        return;
    }
    int md = (l+r)/2;
    updateIDX(idx,val,node*2,l,md);
    updateIDX(idx,val,node*2+1,md+1,r);
    seg[node] = Node(seg[node*2],seg[node*2+1]);
}
Node get(int s,int e,int node = 1,int l = 1,int r = n){
    prop(node,l,r);
    if(l > e || r < s)
        return Node();
    if(l >= s && r <= e){
        return seg[node];
    }
    int md = (l+r)/2;
    return Node(get(s,e,node*2,l,md),get(s,e,node*2+1,md+1,r));
}
bool check(const Node &cur,int mask){
    for(int i = LOG-1;i>=0;i--){
        if(((mask >> i) & 1) == 1){
            if(cur.basis[i] == 0)
                return false;
            mask ^= cur.basis[i];
        }
    }
    return true;
}

int main(){

    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
    #endif
	cin.tie(0);
	ios_base::sync_with_stdio(0);

    ans[0] = 1;
    for(int i = 1;i<N;i++){
        ans[i] = 2LL*ans[i-1] % MOD;
    }
	int T;
	cin>>T;	
	while(T--){
        cin>>n;
        for(int i = 1;i<=n;i++){
            cin>>a[i];
        }
        seg.assign(n*4+1,Node());
        build();
        cin>>q;
        while(q--){
            int type;
            cin>>type;
            if(type == 1){
                int l,r,x;
                cin>>l>>r>>x;
                updateAND(l,r,x);
            }else if(type == 2){
                int l,x;
                cin>>l>>x;
                updateIDX(l,x);
            }else {
                int l,r,x;
                cin>>l>>r>>x;
                Node cur = get(l,r);
                if(check(cur,x)){
                    assert(r-l+1 >= cur.sz);
                    cout<<ans[r-l+1-cur.sz]<<endl;
                }else{
                    cout<<"0\n";
                }
            }
        }
	}
	return 0;
}