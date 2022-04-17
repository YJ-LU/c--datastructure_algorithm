//
// Created by YJ on 2022/4/16.
//
//Definition for singly-linked list
#include <iostream>
using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr){}
    ListNode(int x): val(x), next(nullptr){}
    ListNode(int x, ListNode* next): val(x), next(next){}
};

//reverse actually implement by reversing the direction of the signal pointer
class Solution{
    public:
        // time 8ms
        // memory 8 MB
        ListNode* reverseList(ListNode* head){
            // set a previous pointer
            ListNode* pre = nullptr;

            ListNode* cur = head;

            while (cur){
                //set a tem pointer for traverse
                ListNode *tem = cur->next;
                // reverse point
                cur->next = pre;
                pre = cur;
                cur = tem;
            }
            //return as new head
            return pre;
        }

        // time 8ms
        // memory 8.4 MB
        ListNode* reverseList2(ListNode* head){
            //base situation
            if(!head && !head->next)
                return head;
            //recursive
            ListNode* rHead = reverseList2(head->next);
            //reverse the pointer
            head->next->next = head;
            //after reverse, the next pointer is null
            head->next = nullptr;
            //return as new head
            return rHead;
        }
};

int main() {
    ListNode* head;
    Solution s;
    for(int i=1; i<10; i++){
        head->val = i;
        head = head->next;
    }

    cout << "reverse1 is: " << s.reverseList(head) << endl;
    return 0;
}

