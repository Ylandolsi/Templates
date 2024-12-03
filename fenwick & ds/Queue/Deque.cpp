
template<class T>
struct DEQUE {
        stack<T> l, r, t;
        void rebalance() {
                bool f = false;
                if (r.empty()) {f = true; l.swap(r);}
                int sz = r.size() / 2;
                while (sz--) {t.push(r.top()); r.pop();}
                while (!r.empty()) {l.push(r.top()); r.pop();}
                while (!t.empty()) {r.push(t.top()); t.pop();}
                if (f) l.swap(r);
        }
        bool empty() {return l.empty() && r.empty();}
        int size() {return (int)l.size() + (int)r.size();}
        void push_front(T x) {l.push(x);}
        void push_back(T x) {r.push(x);}
        void pop_front() {if (l.empty()) rebalance(); l.pop();}
        void pop_back() {if (r.empty()) rebalance(); r.pop();}
        T front() {if (l.empty()) rebalance(); return l.top();}
        T back() {if (r.empty()) rebalance(); return r.top();}
        void swap(DEQUE &x) {l.swap(x.l); r.swap(x.r);}
};