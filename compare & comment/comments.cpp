/*

//setbase - cout << setbase (16); cout << 100 << endl; Prints 64
//setfill -   cout << setfill ('x') << setw (5); cout << 77 << endl; prints xxx77
//setprecision - cout << setprecision (4) << f << endl; Prints x.xxxx

struct Compare {
    bool operator()( const int &a,  const int& b) const {
        return a < b;
    }
};
set<int,Compare>st;
sort(vec.begin(),vec.end(), [](int &a, int &b){ return a>b; });


using mykey = pair<int, pair<int, int>>;


struct node {
  int left , right ; 
  node ( int x = 0 , int y = 0  ) :left (x) , right(y) {}
}
*/           

/*
      order_of_key(x): counts the number of elements in the set that are
      strictly less than x.
      find_by_order(k): similar to find, returns the iterator corresponding
      to the k-th lowest element in the set (0-indexed). 
      or k-th largest depend of type of set declared !
      lef.order_of_key({0, -INF} 
      ===> el elements eli strictly asghar mel 0 , w ken andhom nafs 0 tkharaj eli andou akal mel -INF



      // how to del an element in indexed set ! 
      void del( indexed_set_inc& t , int val ){
      int rank = t.order_of_key(val);//Number of elements that are less than v in t
      auto  it = t.find_by_order(rank); //Iterator that points to the (rank+1)th element in t
      t.erase(it);
}

*/ 





  /* 
    indexed_map !!!!

    mp[50] = 4 ; 
    mp[80] = 10 ;
    mp[200] = 50 ; 
    cout << mp.find_by_order(1)->second << endl; = print( mp[80])
    mp.erase(mp.find_by_order(1));
    cout << mp.find_by_order(1)->second << endl; = print ( mp[200]) 
    */ 
  
  
