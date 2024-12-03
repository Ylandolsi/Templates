///  MIN QUEUEEEEEE
struct minstack {
        stack<pair<int, int>> st;
        int getmin() {return st.top().second;}
        bool empty() {return st.empty();}
        int size() {return st.size();}
        void push(int x) {
                int mn = x;
                if (!empty()) mn = min(mn, getmin());
                st.push({x, mn});
        }
        void pop() {st.pop();}
        int top() {return st.top().first;}
        void swap(minstack &x) {st.swap(x.st);}
};

struct mindeque {
        minstack l, r, t;
        void rebalance() {
                bool f = false;
                if (r.empty()) {f = true; l.swap(r);}
                int sz = r.size() / 2;
                while (sz--) {t.push(r.top()); r.pop();}
                while (!r.empty()) {l.push(r.top()); r.pop();}
                while (!t.empty()) {r.push(t.top()); t.pop();}
                if (f) l.swap(r);
        }
        int getmin() {
                if (l.empty()) return r.getmin();
                if (r.empty()) return l.getmin();
                return min(l.getmin(), r.getmin());
        }
        bool empty() {return l.empty() && r.empty();}
        int size() {return l.size() + r.size();}
        void push_front(int x) {l.push(x);}
        void push_back(int x) {r.push(x);}
        void pop_front() {if (l.empty()) rebalance(); l.pop();}
        void pop_back() {if (r.empty()) rebalance(); r.pop();}
        int front() {if (l.empty()) rebalance(); return l.top();}
        int back() {if (r.empty()) rebalance(); return r.top();}
        void swap(mindeque &x) {l.swap(x.l); r.swap(x.r);}
};


// min max queue

template<class T,T inf>
struct minmax_queue
{
    stack<T>front,back,fmin,bmin,fmax,bmax;
    minmax_queue(){fmin.push(inf);bmin.push(inf);fmax.push(-inf);bmax.push(-inf);}
    void push(T val)
    {
        back.push(val);
        bmin.push(std::min(bmin.top(),val));
        bmax.push(std::max(bmax.top(),val));
    }
    T top()
    {
        if(front.empty())
        {
            while(!back.empty())
            {
                T v=back.top();
                bmin.pop();bmax.pop();back.pop();
                front.push(v);fmin.push(std::min(fmin.top(),v));fmax.push(std::max(fmax.top(),v));
            }
        }
        return front.top();
    }
    void pop()
    {
        top();
        front.pop();fmin.pop();fmax.pop();
    }
    T min(){return std::min(fmin.top(),bmin.top());}
    T max(){return std::max(fmax.top(),bmax.top());}
};


/* HOW TO USSE IT 
    minmax_queue<ll,(ll)1e18>mm;
    for(int i=0;i<k;i++)mm.push(idx[i]);
    ll ans=mm.max()-mm.min();
    for(int i=k;i<n;i++)
    {
        mm.push(idx[i]);
        mm.pop();
        ans=min(ans,mm.max()-mm.min());
    }
*/