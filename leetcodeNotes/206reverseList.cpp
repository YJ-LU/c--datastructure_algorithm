//
// Created by apple on 2022/4/16.
//
//Definition for singly-linked list

struct ListNode{
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr){}
    ListNode(int x): val(x), next(nullptr){}
    ListNode(int x, ListNode* next): val(x), next(next){}
};

class Solution{
    public:
        ListNode* reverseList(ListNode* head){
            // set a previous pointer
            ListNode* pre = nullptr;

            ListNode* cur = head;

            while (cur){
                //set a tem pointer for traverse
                ListNode *tem = cur->next;
                // reverse
                cur->next = pre;
                pre = cur;
                cur = tem;
            }
            return pre;
    }
};
// time 8ms
// memory 8mb
