class MedianFinder {
    public:
        priority_queue<int> l; // all the smaller numbers are on the left
        priority_queue<int, vector<int>, greater<int>> r;
    
        MedianFinder() {
            l = priority_queue<int>();
            r = priority_queue<int, vector<int>, greater<int>>();
        }
        
        void addNum(int num) {
            l.push(num);
            r.push(l.top());
            l.pop();
    
            // Rebalance if needed - always keep left side higher
            if (r.size() > l.size()) {
                l.push(r.top());
                r.pop();
            }
        }
        
        double findMedian() {
            return l.size() > r.size() ? l.top() : (double).5 * (l.top() + r.top());
        }
    };
    
    /**
     * Your MedianFinder object will be instantiated and called as such:
     * MedianFinder* obj = new MedianFinder();
     * obj->addNum(num);
     * double param_2 = obj->findMedian();
     */