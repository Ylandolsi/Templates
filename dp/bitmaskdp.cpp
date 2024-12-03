// loop over the masks :
for(int submask = mask; ; submask = (submask - 1) & mask) {
         // do something

        if(submask == 0) break;
}



// base 3 
Get: digit[i] = (x / 3^i)) % 3.
// value can be 0 1 2 , think of it as transferming decimal number to numbre in baseX ( keep dividng and testahfdh b reste !) 
Set: x = x + (value - (x / 3^i)) % 3) * 3^i
// when we use mask of 10 digits
3^10 == 59049, so value of your mask will be in [0..59048].
Instead of slow division operation you can precompute modInverse(3^i, 2^32) and multiply.
x / (3^i) == x * modInverse(3^i, 2^32) In unsigned 32-bit integer type.