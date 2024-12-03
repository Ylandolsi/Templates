
// in case working with bits ? represnt numbers as string 1 , 0 
// in that case don t forget to ADD  0 at the debut !!!

// binary one !
// https://codeforces.com/contest/1895/submission/283067264
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


//-----------------------
/*
    Trie : 
    u have a dictionarry D and you want to 
        - count how many strings in D have string E as a prefix
        - count how many strings in D == E
        - count how many ways u can form string E by concatinating
            some of the strings in D ( this dp & trie !
                    https://cses.fi/problemset/task/1731/ )
        - traverse string S on count prefix and store for each prefix length
            how many strings have that prefix !  ( function all prefixs ! )
                https://atcoder.jp/contests/abc353/submissions/58357487 

    --
        - count bitwise U & V   
*/
 // https://cses.fi/problemset/task/1731

struct node{
    int cteprf , ctend ;
    // array<int , 2 > elems;
    array<int , 26 > elems;
    node(){
        cteprf = 0  , ctend = 0; 
        for ( auto& d : elems ) d = -1  ; 
    }
};
struct Trie {
    vector<node>tr;
    Trie (){
        tr.resize(1 ,node());
    }
    void insert ( string &s ){
        int cur= 0 ;  
        int sz = s.size();
        for ( int i= 0 ; i < sz ; i++  ){
            int c = s[i] -'a';
            // int c = s[i] -'0';
            if ( tr[cur].elems[c] == -1 ){
                tr[cur].elems[c] = tr.size();
                tr.push_back(node());
            }
            cur =  tr[cur].elems[c];
            tr[cur].cteprf++ ; 
        }
        tr[cur].ctend++ ;  
    }

    void erase(string& s){
        int cur = 0 ; 
        int sz = s.size();

        for ( int i= 0 ; i < sz ; i++  ){
            int c = s[i] -'a';
            // int c = s[i] -'0';
            cur =  tr[cur].elems[c];
            tr[cur].cteprf-- ; 
        }
        tr[cur].ctend-- ;
    }

    // int query (string s ) // count prefix of string s in dictionary 
                            // count how many String S occurs in trie !
                            // ect..
    int countPrefix ( string &s ){
        int cur = 0  ; 
        int sz = s.size();
        for ( int i= 0 ; i < sz ; i++  ){
            int c = s[i] -'a';
            // int c = s[i] -'0';
            if ( tr[cur].elems[c] == -1 ){
                return 0 ; 
            }
            cur =  tr[cur].elems[c];
        }
        return tr[cur].cteprf ; // .ctened ! ...  
    }    
    vector<pi> allprefixes ( string &s ){
        int cur = 0  ; 
        int sz = s.size();
        vector<pi> rts  ; 
        for ( int i= 0 ; i < sz ; i++  ){
            int c = s[i] -'a';
            // int c = s[i] -'0';
            if ( tr[cur].elems[c] == -1 ){
                return rts ; 
            }
            cur =  tr[cur].elems[c];
            rts.push_back({ tr[cur].cteprf , i +1 } );
        }
        return rts ;
        // how many strings have the preifx = s[0 ,i] 
        // pour tout i ! 
    }    


    int Max_xor(int x) {
        int cur = 0;
        int res = 0;
        int p = 30 ; 
        string SD = mask(x);
        for ( auto& d : SD ){
            int c = d -'0';
            if ( tr[cur].elems[!c] != -1 && tr[tr[cur].elems[!c]].cteprf > 0 ){
                res += 1LL << p ;  
                cur =  tr[cur].elems[!c];
            }
            else 
                cur =  tr[cur].elems[c];
            p-- ;

        }
        
 
        return res;
    }  

};