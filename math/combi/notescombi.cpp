
// If a ≡ b (mod n) and c ≡ d (mod n),
// then: ac ≡ bd (mod n)


/*
        if u need at least one condition satsififed 
        do it reversly 
        all - no condition satisfied

        for example
        
        u have X items 
        u want at least one of them to the right of i ! 

        = 
        choose ( allvide , X ) - choose ( videleft = 5 , X ) ;
        =
        guarnteed that no all of X occurence Appears to the left = at least one appears to the right !!!
        _ _ _ _ _ i _ _ _ _ _ 
        
        https://youtu.be/jxnf61YS4ks?list=PLc02D4EoVYQAg46jExEGcPnkV6eAQns60&t=596

*/
/*

        // Fermat's Little Theorem:
        // If p is a prime number and a is an integer not divisible by p:
        // a^(p-1) ≡ 1 (mod p)
        //
        // Equivalently:
        // a^(b % (p-1)) ≡ a^b (mod p)

*/
/*
        // The Binomial Theorem:
----------------------------------------
        // (x + y)^n = Σ C(i, n) * x^i * y^(n-i)
        
        Y = 1 
        
        (1 + x)^n = Σ (n choose k) * x^k
*/

/*    
        Binomial Theorem:
        ∑ (n choose k) = 2^n
        for k = 0 to n.

        Sum of even-indexed coefficients:
        ∑ (n choose k) for even k = 2^(n-1)

        mint pairC = 0 ;
        for ( int i = 0 ; i <= y  ;i +=2 ) pairC = pairC + C.ncr( y , i ); 

        == 2 ^ (n - 1 )

        Sum of odd-indexed coefficients:
        ∑ (n choose k) for odd k = 2^(n-1)

        This is because the coefficients are symmetric and the total sum (2^n) is evenly split between 
        the even and odd indexed coefficients.
 */