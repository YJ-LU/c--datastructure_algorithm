

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // time 8ms
    // memory 14.3 MB
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *cur1 = list1;
        ListNode *cur2 = list2;

        // create a new empty List
        ListNode *merge = new ListNode(-1);
        // traversal pointer for the List
        ListNode *traversal = merge;

        if(!cur1){
            return list2;
        }
        if(!cur2){
            return list1;
        }

        while(cur1 && cur2){
            if( cur1->val >= cur2->val){
                traversal->next = cur2;
                cur2 = cur2->next;
            }
            else{
                traversal->next = cur1;
                cur1 = cur1->next;
            }
            traversal = traversal->next;
        }
        // concat
        traversal->next = cur1 ? cur1 : cur2;
        return merge->next;
    }
};

