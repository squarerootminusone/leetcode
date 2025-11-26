/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 class Solution {
    public:
        ListNode* mergeKLists(vector<ListNode*>& lists) {
            multimap<int, ListNode*> m;
    
            for (ListNode* first : lists)
                if (first != nullptr)
                    m.insert({first->val, first});
    
            ListNode* list = m.size() > 0 ? m.cbegin()->second : nullptr;
            ListNode* cur = nullptr;
            while (!m.empty()) {
                // Pop the lowest element
                ListNode* node = m.cbegin()->second;
                m.erase(m.cbegin());
    
                if (cur != nullptr)
                    cur->next = node;
                cur = node;
                if (node->next != nullptr)
                    m.insert({node->next->val, node->next});
            }
    
            return list;
        }
    };