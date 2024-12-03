double l = 0.0f, r = 1e14f;
for (int i = 0; i < iteration_count && l + eps < r; ++i)
{
    
    double mid = 0.5f * (l + r);
    if (check(mid))
        r = mid;
    else
        l = mid;
}


    // double 
    int iteration_count  = 600 ; // 200 is sufficent  
    double l = 0.0f, r = 1e12;
    for (int i = 0; i < iteration_count && l + eps < r; ++i){
        double mid1 = l+(r-l)/3;
        double mid2 = r-(r-l)/3;
        double m1 = check(mid1);
        double m2 = check(mid2);
        if ( m1 <= m2  )  r = mid2 ;
        else l = mid1;
    }
    /*
        l+1 < r  bs
        l+1 < r ts 
    */
