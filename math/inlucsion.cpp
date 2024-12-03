/*
    we use it when we want to calulate 
    A or B or C or D  

    =>  a + b + b - (ab + ac + cb) + (abc + acd + bcd) .. 
*/

/*
let us turn to the inverse problem,
do not contain at least one of the numbers.
*/
/*
        given x & n 
        we can count 
        gcd ( i , x ) = 1 
        i from [1 to  n ]


        // count number of Integer that are not divisbile by X => n - ( count divisible = bad)  =>
        
        //---------------------
        pollard.cnt_primes.clear();
        pollard.factor_rec(X , pollard.cnt_primes);
        int ans =NN ; 
        int primess = pollard.cnt_primes.size();
        int bad = 0 ;
        for  (int mask = 1 ; mask < 1<< primess ; mask++ ){
            int tmp =1 ; 
            auto iter = pollard.cnt_primes.begin();
            for ( int j = 0 ; j < primess ; j++ ){
                if ( (1 << j ) & mask ){
                    tmp*= iter->first;
                }
                iter++ ;
            }
            if ( __popcount(mask) & 1 ) bad += NN/tmp ;
            else bad -= NN /tmp ;  

        }
        ans -= bad ;  



        // if we are not using primes !!          ( we do lcm !!!!!!!!!)

        auto getans =[&]( int X ){
        int ans = 0 ;
        for ( int mask = 1 ; mask < 1 << N ; mask ++ ){
            int tmp = 1; 
            for ( int i = 0 ; i < N  ;i++ ){
                if ( (1 << i) & mask) {
                    tmp =  lcm( tmp , vals[i] ) ; 
                }
            }
            if ( __popcount(mask) &1 )  ans += X/tmp ; 
            else ans -= X/tmp ; 
        }
        return ans ; 
    } ;

*/