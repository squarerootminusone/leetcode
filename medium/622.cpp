class MyCircularQueue {
    int sz;
    vector<int> data;
    int l, r;
public:
    MyCircularQueue(int k): sz(k + 1), data(k + 1), l(0), r(0) {}

    bool enQueue(int value) {
        if (isFull())
            return false;

        data[r] = value;
        r = (r + 1) % sz;
        return true;
    }

    bool deQueue() {
        if (isEmpty())
            return false;

        l = (l + 1) % sz;
        return true;
    }

    int Front() {
        if (isEmpty()) return -1;
        return data[l];
    }

    int Rear() {
        if (isEmpty()) return -1;
        return data[(r - 1 + sz) % sz];
    }

    bool isEmpty() {
        return l == r;
    }

    bool isFull() {
        return (r + 1) % sz == l;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
