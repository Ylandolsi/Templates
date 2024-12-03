// https://atcoder.jp/contests/abc367/submissions/56895809
template <typename T>
class Zobrist {
private:
    unordered_map<T, T> hash_;

public:
    // the hash is one indexed : 
    
    template <typename... Args>
    Zobrist(const Args&... vecs){
        // thot l vecteuret lkol eli chtekhdm alehom 
        vector<T> merged;

        (merged.insert(merged.end(), vecs.begin(), vecs.end()), ...);

        sort(merged.begin(), merged.end());
        merged.erase(unique(merged.begin(), merged.end()), merged.end());

        random_device rd;
        mt19937_64 ran(rd());

        for(const auto& e : merged){
            hash_[e] = ran();
        }
    }

    T val(const T& e){
        assert(hash_.find(e) != hash_.end());
        return hash_[e];
    }
    // hashing a set 
    vector<T> xor_hash(const vector<T>& vec){
        int N = vec.size();
        vector<T> hashed_vec(N+1);
        unordered_set<T> memo;

        for(int i = 0; i < N; i++){
            if(memo.find(vec[i]) == memo.end()){
                memo.insert(vec[i]);
                hashed_vec[i+1] = hashed_vec[i] ^ val(vec[i]);
            } else{
                hashed_vec[i+1] = hashed_vec[i];
            }
        }

        return hashed_vec;
    }


    // hashing a multiset 
    vector<T> pref_hash(const vector<T>& vec){
        int N = vec.size();
        vector<T> hashed_vec(N+1);
        // if the values is too long we have to make it 
        // modulo % M , M = LONGLONG_MAX !!!!!!! 
        for(int i = 0; i < N; i++){
            hashed_vec[i+1] = hashed_vec[i] + val(vec[i]);
        }

        return hashed_vec;
    }
    /*
        pref_hash & xor_hash are one indexed 
        but the vector passed in paremtre of these function
        is 0 indexed 
    */
};


/*
    we can do multiset hash also with seg tree
    https://atcoder.jp/contests/abc367/submissions/56820206


    or with another zorbist hash with more than one values to avoid 
    collisions
    https://atcoder.jp/contests/abc367/submissions/56818814

*/