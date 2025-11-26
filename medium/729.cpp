class MyCalendar {
    public:
        map<int, int> bookings;
    
        MyCalendar() {
            bookings = map<int, int>();
            bookings[-1] = -1;
            bookings[1e9 +5]=1e9+5;
        }
        
        bool book(int startTime, int endTime) {
            auto lit = --bookings.lower_bound(startTime);
            auto rit = bookings.upper_bound(endTime - 1);
            if (lit->second > startTime || ++lit != rit)
                return false;
            bookings[startTime] = endTime;
            return true;
        }
    };
    
    /**
     * Your MyCalendar object will be instantiated and called as such:
     * MyCalendar* obj = new MyCalendar();
     * bool param_1 = obj->book(startTime,endTime);
     */