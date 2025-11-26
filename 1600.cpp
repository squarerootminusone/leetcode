class ThroneInheritance {
    unordered_map<string, vector<string>> m;
    set<string> dead;
    string kingName;

public:
    ThroneInheritance(string kingName) {
        this->kingName = kingName;
    }
    
    void birth(string parentName, string childName) {
        if (m.find(parentName) != m.end()) m[parentName].push_back(childName);
        else m[parentName] = {childName};
        
    }
    
    void death(string name) {
        dead.insert(name);
    }
    
    vector<string> getInheritanceOrder() {
        vector<string> order;
        successor(order, kingName);
        return order;
    }

    void successor(vector<string> &order, string person) {
        if (dead.find(person) == dead.end())
            order.push_back(person);

        for (string &child : m[person])
            successor(order, child);
    }
};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */