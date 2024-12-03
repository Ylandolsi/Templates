vector<int> next_greater(vector<int>&v){
    int n=v.size();
    stack<pair<int,int>>s;
    vector<int>ans(n, n);
    s.push({v[0], 0});
    for(int i=1; i<n; ++i){
        while(s.size() && s.top().first<v[i]){
            ans[s.top().second]=i; s.pop();
        }
        s.push({v[i], i});
    }
    return ans;
}
vector<int> next_smaller(vector<int>&v){
    int n=v.size();
    stack<pair<int,int>>s;
    vector<int>ans(n, n);
    s.push({v[0], 0});
    for(int i=1; i<n; ++i){
        while(s.size() && s.top().first>v[i]){
            ans[s.top().second]=i; s.pop();
        }
        s.push({v[i], i});
    }
    return ans;
}
vector<int> prev_greater(vector<int>&v){
    int n=v.size();
    stack<pair<int,int>>s;
    vector<int>ans(n, -1);
    s.push({v[0], 0}); //ans[0]=n;
    for(int i=1; i<n; ++i){
        while(s.size() && s.top().first<v[i]){
            s.pop();
           // ans[s.top().second]=i; s.pop();
        }
        if(s.size()) ans[i]=s.top().second;
       // else ans[i]=n;
        s.push({v[i], i});
    }
    return ans;
}
vector<int> prev_smaller(vector<int>&v){
    int n=v.size();
    stack<pair<int,int>>s;
    vector<int>ans(n, -1);
    s.push({v[0], 0}); //ans[0]=n;
    for(int i=1; i<n; ++i){
        while(s.size() && s.top().first>v[i]){
            s.pop();
        }
        if(s.size()) ans[i]=s.top().second;
        s.push({v[i], i});
    }
    return ans;
}
