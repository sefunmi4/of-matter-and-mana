#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Definition for a linked list node with random pointer.
struct Node {
    int val;
    Node* next;
    Node* random;
    Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};

class Linked_List {
public:
    Linked_List() {}
    ~Linked_List() {}
    Linked_List(const Linked_List& other) = default;
    Linked_List(Linked_List&& other) noexcept = default;
    Linked_List& operator=(const Linked_List& other) = default;
    Linked_List& operator=(Linked_List&& other) noexcept = default;

    // 1. Reverse Linked List
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        while (head) {
            ListNode* next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }

    // 2. Merge Two Sorted Lists
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy;
        ListNode* current = &dummy;
        while (list1 && list2) {
            if (list1->val < list2->val) {
                current->next = list1;
                list1 = list1->next;
            } else {
                current->next = list2;
                list2 = list2->next;
            }
            current = current->next;
        }
        current->next = list1 ? list1 : list2;
        return dummy.next;
    }

    // 3. Reorder List
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;

        // Find middle
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Reverse second half
        ListNode* prev = nullptr;
        ListNode* curr = slow->next;
        slow->next = nullptr;
        while (curr) {
            ListNode* temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }

        // Merge halves
        ListNode* first = head;
        ListNode* second = prev;
        while (second) {
            ListNode* tmp1 = first->next;
            ListNode* tmp2 = second->next;
            first->next = second;
            second->next = tmp1;
            first = tmp1;
            second = tmp2;
        }
    }

    // 4. Remove Nth Node from End
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* left = dummy;
        ListNode* right = head;

        while (n--) right = right->next;
        while (right) {
            left = left->next;
            right = right->next;
        }

        left->next = left->next->next;
        return dummy->next;
    }

    // 5. Copy List with Random Pointer
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        // 1st pass: clone nodes
        Node* curr = head;
        while (curr) {
            Node* copy = new Node(curr->val);
            copy->next = curr->next;
            curr->next = copy;
            curr = copy->next;
        }

        // 2nd pass: assign random pointers
        curr = head;
        while (curr) {
            if (curr->random) {
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next;
        }

        // 3rd pass: restore original & extract copy
        curr = head;
        Node* dummy = new Node(0);
        Node* copyCurr = dummy;
        while (curr) {
            Node* copy = curr->next;
            curr->next = copy->next;
            copyCurr->next = copy;
            copyCurr = copy;
            curr = curr->next;
        }

        return dummy->next;
    }

    // 6. Add Two Numbers
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy;
        ListNode* curr = &dummy;
        int carry = 0;

        while (l1 || l2 || carry) {
            int v1 = l1 ? l1->val : 0;
            int v2 = l2 ? l2->val : 0;
            int sum = v1 + v2 + carry;
            carry = sum / 10;
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }

        return dummy.next;
    }

    // 7. Detect Cycle in Linked List
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }

    // 8. Find Duplicate Number
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        int slow2 = 0;
        while (slow != slow2) {
            slow = nums[slow];
            slow2 = nums[slow2];
        }
        return slow;
    }

    // 9. LRU Cache
    class LRUCache {
    private:
        unordered_map<int, pair<int, list<int>::iterator>> cache;
        list<int> order;
        int capacity;

    public:
        LRUCache(int capacity) : capacity(capacity) {}

        int get(int key) {
            if (cache.find(key) == cache.end()) return -1;
            order.erase(cache[key].second);
            order.push_back(key);
            cache[key].second = prev(order.end());
            return cache[key].first;
        }

        void put(int key, int value) {
            if (cache.find(key) != cache.end()) {
                order.erase(cache[key].second);
            } else if (cache.size() == capacity) {
                int lru = order.front();
                order.pop_front();
                cache.erase(lru);
            }
            order.push_back(key);
            cache[key] = {value, prev(order.end())};
        }
    };

    // 10. Merge K Sorted Lists
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);

        for (auto list : lists) {
            if (list) pq.push(list);
        }

        ListNode dummy;
        ListNode* curr = &dummy;

        while (!pq.empty()) {
            ListNode* node = pq.top(); pq.pop();
            curr->next = node;
            curr = curr->next;
            if (node->next) pq.push(node->next);
        }

        return dummy.next;
    }

    // 11. Reverse Nodes in k-Group
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* groupPrev = dummy;

        while (true) {
            ListNode* kth = getKth(groupPrev, k);
            if (!kth) break;

            ListNode* groupNext = kth->next;
            ListNode* prev = kth->next;
            ListNode* curr = groupPrev->next;

            while (curr != groupNext) {
                ListNode* tmp = curr->next;
                curr->next = prev;
                prev = curr;
                curr = tmp;
            }

            ListNode* tmp = groupPrev->next;
            groupPrev->next = kth;
            groupPrev = tmp;
        }

        return dummy->next;
    }

private:
    ListNode* getKth(ListNode* curr, int k) {
        while (curr && k > 0) {
            curr = curr->next;
            k--;
        }
        return curr;
    }
};