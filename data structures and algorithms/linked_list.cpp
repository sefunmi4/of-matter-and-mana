#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

class Linked_List {
public:
    // Default constructor
    Linked_List() {}

    // Destructor
    ~Linked_List() {}

    // Copy constructor
    Linked_List(const Linked_List& other) = default;

    // Move constructor
    Linked_List(Linked_List&& other) noexcept = default;

    // Copy assignment
    Linked_List& operator=(const Linked_List& other) = default;

    // Move assignment
    Linked_List& operator=(Linked_List&& other) noexcept = default;

    // 1. reverse_linked_list:
    // Given the beginning of a singly linked list head, reverse the list, and return the new beginning of the list.
    // /**
    // * Definition for singly-linked list.
    // * struct ListNode {
    // *     int val;
    // *     ListNode *next;
    // *     ListNode() : val(0), next(nullptr) {}
    // *     ListNode(int x) : val(x), next(nullptr) {}
    // *     ListNode(int x, ListNode *next) : val(x), next(next) {}
    // * };
    // */
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr) {
            ListNode* temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        return prev;
    }

    // 2.merge_two_sorted_list:
    // You are given the heads of two sorted linked lists list1 and list2.
    // Merge the two lists into one sorted linked list and return the head of the new sorted linked list.
    // The new list should be made up of nodes from list1 and list2.
    // /**
    //  * Definition for singly-linked list.
    //  * struct ListNode {
    //  *     int val;
    //  *     ListNode *next;
    //  *     ListNode() : val(0), next(nullptr) {}
    //  *     ListNode(int x) : val(x), next(nullptr) {}
    //  *     ListNode(int x, ListNode *next) : val(x), next(next) {}
    //  * };
    //  */
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);
        ListNode* node = &dummy;

        while (list1 && list2) {
            if (list1->val < list2->val) {
                node->next = list1;
                list1 = list1->next;
            } else {
                node->next = list2;
                list2 = list2->next;
            }
            node = node->next;
        }

        if (list1) {
            node->next = list1;
        } else {
            node->next = list2;
        }

        return dummy.next;
    }

    // 3. reorder_list:
    // You are given the head of a singly linked-list.
    // The positions of a linked list of length = 7 for example, can intially be represented as:
    // [0, 1, 2, 3, 4, 5, 6]
    // Reorder the nodes of the linked list to be in the following order:
    // [0, 6, 1, 5, 2, 4, 3]
    // Notice that in the general case for a list of length = n the nodes are reordered to be in the following order:
    // [0, n-1, 1, n-2, 2, n-3, ...]
    // You may not modify the values in the list's nodes, but instead you must reorder the nodes themselves.
    // /**
    //  * Definition for singly-linked list.
    //  * struct ListNode {
    //  *     int val;
    //  *     ListNode *next;
    //  *     ListNode() : val(0), next(nullptr) {}
    //  *     ListNode(int x) : val(x), next(nullptr) {}
    //  *     ListNode(int x, ListNode *next) : val(x), next(next) {}
    //  * };
    //  */
    void reorderList(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* second = slow->next;
        ListNode* prev = slow->next = nullptr;
        while (second != nullptr) {
            ListNode* tmp = second->next;
            second->next = prev;
            prev = second;
            second = tmp;
        }

        ListNode* first = head;
        second = prev;
        while (second != nullptr) {
            ListNode* tmp1 = first->next;
            ListNode* tmp2 = second->next;
            first->next = second;
            second->next = tmp1;
            first = tmp1;
            second = tmp2;
        }
    }

    // 4. remove_nth_to_last_node:
    // You are given the beginning of a linked list head, and an integer n.
    // Remove the nth node from the end of the list and return the beginning of the list.
    // /**
    //  * Definition for singly-linked list.
    //  * struct ListNode {
    //  *     int val;
    //  *     ListNode *next;
    //  *     ListNode() : val(0), next(nullptr) {}
    //  *     ListNode(int x) : val(x), next(nullptr) {}
    //  *     ListNode(int x, ListNode *next) : val(x), next(next) {}
    //  * };
    //  */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* left = dummy;
        ListNode* right = head;

        while (n > 0) {
            right = right->next;
            n--;
        }

        while (right != nullptr) {
            left = left->next;
            right = right->next;
        }

        left->next = left->next->next;
        return dummy->next;
    }

    // 5. copy_list_from_random_pointer:

    // Copy Linked List with Random Pointer
    // You are given the head of a linked list of length n. Unlike a singly linked list, each node contains an additional pointer random, which may point to any node in the list, or null.

    // Create a deep copy of the list.

    // The deep copy should consist of exactly n new nodes, each including:

    // The original value val of the copied node
    // A next pointer to the new node corresponding to the next pointer of the original node
    // A random pointer to the new node corresponding to the random pointer of the original node
    // Note: None of the pointers in the new list should point to nodes in the original list.

    // Return the head of the copied linked list.

    // In the examples, the linked list is represented as a list of n nodes. Each node is represented as a pair of [val, random_index] where random_index is the index of the node (0-indexed) that the random pointer points to, or null if it does not point to any node.

    // /*
    // // Definition for a Node.
    // class Node {
    // public:
    //     int val;
    //     Node* next;
    //     Node* random;
        
    //     Node(int _val) {
    //         val = _val;
    //         next = NULL;
    //         random = NULL;
    //     }
    // };
    // */

    Node* copyRandomList(Node* head) {
        if (!head) {
            return nullptr;
        }

        Node* l1 = head;
        while (l1) {
            Node* l2 = new Node(l1->val);
            l2->next = l1->random;
            l1->random = l2;
            l1 = l1->next;
        }

        Node* newHead = head->random;

        l1 = head;
        while (l1) {
            Node* l2 = l1->random;
            l2->random = (l2->next != nullptr) ? l2->next->random : nullptr;
            l1 = l1->next;
        }

        l1 = head;
        while (l1) {
            Node* l2 = l1->random;
            l1->random = l2->next;
            l2->next = (l1->next != nullptr) ? l1->next->random : nullptr;
            l1 = l1->next;
        }

        return newHead;
    }

    // 6. add_two_numbers:
    // You are given two non-empty linked lists, l1 and l2, where each represents a non-negative integer.

    // The digits are stored in reverse order, e.g. the number 123 is represented as 3 -> 2 -> 1 -> in the linked list.

    // Each of the nodes contains a single digit. You may assume the two numbers do not contain any leading zero, except the number 0 itself.

    // Return the sum of the two numbers as a linked list.

    // /**
    //  * Definition for singly-linked list.
    //  * struct ListNode {
    //  *     int val;
    //  *     ListNode *next;
    //  *     ListNode() : val(0), next(nullptr) {}
    //  *     ListNode(int x) : val(x), next(nullptr) {}
    //  *     ListNode(int x, ListNode *next) : val(x), next(next) {}
    //  * };
    //  */

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode();
        ListNode* cur = dummy;

        int carry = 0;
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int v1 = (l1 != nullptr) ? l1->val : 0;
            int v2 = (l2 != nullptr) ? l2->val : 0;

            int val = v1 + v2 + carry;
            carry = val / 10;
            val = val % 10;
            cur->next = new ListNode(val);

            cur = cur->next;
            l1 = (l1 != nullptr) ? l1->next : nullptr;
            l2 = (l2 != nullptr) ? l2->next : nullptr;
        }
        ListNode* res = dummy->next;
        delete dummy;
        return res;
    }

    // 7. linked_list_cycle_detection:

    // Given the beginning of a linked list head, return true if there is a cycle in the linked list. Otherwise, return false.

    // There is a cycle in a linked list if at least one node in the list can be visited again by following the next pointer.

    // Internally, index determines the index of the beginning of the cycle, if it exists. The tail node of the list will set it's next pointer to the index-th node. If index = -1, then the tail node points to null and no cycle exists.

    // Note: index is not given to you as a parameter.

    // /**
    // * Definition for singly-linked list.
    // * struct ListNode {
    // *     int val;
    // *     ListNode *next;
    // *     ListNode() : val(0), next(nullptr) {}
    // *     ListNode(int x) : val(x), next(nullptr) {}
    // *     ListNode(int x, ListNode *next) : val(x), next(next) {}
    // * };
    // */

    bool hasCycle(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;

        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
            
            if (fast == slow) {
                return true;
            }
        }
        
        return false;
    }


    // 8. find_the_duplicate_number:
    // You are given an array of integers nums containing n + 1 integers. Each integer in nums is in the range [1, n] inclusive.
    // Every integer appears exactly once, except for one integer which appears two or more times. Return the integer that appears more than once.
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast) {
                break;
            }
        }

        int slow2 = 0;
        while (true) {
            slow = nums[slow];
            slow2 = nums[slow2];
            if (slow == slow2) {
                return slow;
            }
        }
    }




private:
    // no private variables currently
};