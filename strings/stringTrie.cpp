


// in case working with bits ? represnt numbers as string 1 , 0 
// in that case don t forget to ADD  0 at the debut !!!
bool mnwr(int num, int bit){
    return (num >> bit) & 1;
}
 
string mask(int x){
    string ret(31, '0');
 
    for (int i = 30; i >= 0; i--)
        if (mnwr(x, i))
            ret[i] = '1';
 
    reverse(ret.begin(), ret.end());
    return ret;
}
 
struct Trie{
    struct Node{
        Node* edges[2];
        int cnt;
    }*root = new Node();
 
    void add(string& s){
        Node* cur = root;
 
        for(auto& i : s){
            bool rank = i - '0';
 
            if(cur -> edges[rank] == NULL)
                cur -> edges[rank] = new Node();
 
            cur = cur -> edges[rank];
            cur -> cnt++;
        }
    }
 
    void erase(string& s){
        Node* cur = root;
 
        for(auto& i : s){
            bool rank = i - '0';
 
            cur = cur -> edges[rank];
 
            cur -> cnt--;
        }
    }
 
    int query(string& s){
        int ret = 0;
        Node* cur = root;
 
        int p = 30;
        for(auto& i : s){
            bool rank = i - '0';
 
            if(cur -> edges[!rank] != NULL and (cur -> edges[!rank]) -> cnt > 0)
                cur = cur -> edges[!rank],
                ret += (1 << p);
            else
                cur = cur -> edges[rank];
 
            p--;
        }
 
        return ret;
    }
};


// recurisve template
struct Trie
{
    Trie *children[2];
    int cnt;
    Trie()
    {
        cnt = 0;
        children[0] = children[1] = NULL;
    }
    void add(string &s, int idx = 0)
    {
        cnt++;
        if (s.size() == idx) return;
        if (!children[s[idx]-'0']) children[s[idx]-'0'] = new Trie();
        children[s[idx]-'0']->add(s, idx+1);
    }
    void erase(string &s, int idx = 0)
    {
        cnt--;
        if (s.size() == idx) return;
        children[s[idx]-'0']->erase(s, idx+1);
        if (!children[s[idx]-'0']->cnt) {
            delete children[s[idx]-'0'];
            children[s[idx]-'0'] = NULL;
        }
    }
    string get(string &s, int idx = 0, string acc = "")
    {
        if (s.size() == idx) return acc;
        int nxt = '1'-s[idx];
        assert(children[nxt] || children[!nxt]);
        if (children[nxt]) return children[nxt]->get(s, idx+1, acc+(nxt ? "1" : "0"));
        return children[!nxt]->get(s, idx+1, acc+(nxt ? "0" : "1"));
    }
}