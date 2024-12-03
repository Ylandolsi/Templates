#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

/*
      we can use indexed set 
      as a set where we can remove the i-th element !

      if u use it like this st.insert({i , a[i]});
      https://cses.fi/problemset/result/10903422/
*/
template<typename T, typename Cmp = less<T>> // greater
using iset = tree<T, null_type, Cmp, rb_tree_tag,
		  tree_order_statistics_node_update, allocator<T>>;

void del( iset<int>& t , int val ){
      int rank = t.order_of_key(val);//Number of elements that are less than v in t
      auto  it = t.find_by_order(rank); // Iterator that points to the (rank+1)th element in t
      t.erase(it);
}

/* 
order_of_key(x): counts the number of elements in the set that are strictly less than x.
find_by_order(k):  returns the iterator corresponding to the k-th lowest element in the set (0-indexed). 
                            or k-th largest depend of type of set declare ( greater ) !
lef.order_of_key({0, -INF} 
===> el elements eli strictly asghar mel 0 , w ken andhom nafs 0 tkharaj eli andou akal mel -INF

st.order_of_key({ r , (int)1e9 } ) ;
=> return number of element { <= r , < 1e9 }  !

*/