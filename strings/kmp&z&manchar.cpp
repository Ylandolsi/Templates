// longest proper prefix = suffiix
//For example, prefix function of string "abcabcd" is [ 0, 0, 0, 1, 2, 3, 0] ,
// and prefix function of string "aabaaab" is [0, 1, 0, 1, 2, 2, 3] . 
template <typename T>
    vector<int> prefixFunction(const T &s) {
        int n = (s.size());
        vector<int> p(n);
        for (int i = 1; i < n; i++) {
            int j = p[i - 1];
            while (j > 0 && s[i] != s[j]) j = p[j - 1];
            if (s[i] == s[j]) j++;
            p[i] = j;
        }
        return p;
    }

//------
// we can use zfunction to calcualte the lcp
// https://codeforces.com/contest/126/submission/273366598
class ZAlgorithm {
public:
    vector<int> matchPattern(const string& text, const string& pattern) {
        string newString = pattern + "$" + text;
        vector<int> result;
        vector<int> Z = calculateZ(newString);

        for (int i = 0; i < Z.size(); ++i) {
            if (Z[i] == pattern.length()) {
                result.push_back(i - pattern.length() - 1);
            }
        }
        return result;
    }

private:
    // from i position what s the biggest lenght that 
    // s[i ..... i +  len ] == s[ 0 ...  0 +len ]
    vector<int> calculateZ(string& s) {
            int n = s.size();
            vector<int> z(n);
            int l = 0, r = 0;
            for(int i = 1; i < n; i++) {
                if(i < r) {
                    z[i] = min(r - i, z[i - l]);
                }
                while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                    z[i]++;
                }
                if(i + z[i] > r) {
                    l = i;
                    r = i + z[i];
                }
            }
            return z;
    }
};


//------------------
// Convert input string to manacher format (for eg. "abc" to "*a*b*c*")
// https://codeforces.com/contest/1326/submission/73836144
string manacher_str(const string &s) {
    string ans = "*";
 
    for (int i = 0; i < s.size(); i++) {
        ans += s[i];
        ans += '*';
    }
 
    return ans;
}
 
// Computes the radius of the longest palindrome centered at each element in O(n)
vector<int> manacher(string s) {
        // C = center, rad = radius, R = right boundary
        int C=0, rad=-1, R=-1, i, n = s.size();	
 
        if(n == 0) 
                return {};
 
        // pos holds how many characters around the current position have been scanned
        vector<int> pos(n, 0);
 
        for(i=0; i<n; i++) {
                int mirror = C - (i - C);
 
                // If i is within right_boundary (R), then take radius from i's mirror position, otherwise radius is 0
                // The idea is to re-use what's already been computed for the mirror value
                if(i <= R)
                        rad = min(pos[mirror], R - i);
                else
                        rad = 0;
 
                // rad characters around i have already been scanned. so start from that boundary and move outwards to see if the palindrome can be extended
                while((i - rad >= 0) && (i + rad < n) && (s[i - rad] == s[i + rad]))
                        ++rad;
 
                pos[i] = rad;
 
                // If the palindrome length from i exceeds the right boundary, update right boundary and move center to current position
                if(i + rad - 1 > R) {
                        R = i + rad - 1;
                        C = i;
                }
        }
        return pos;
}// => return the raduis from position I in new string 
// raduis ( shou3e3 mta palindrome including position I ); 