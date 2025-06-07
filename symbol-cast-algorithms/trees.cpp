#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cstdint>

// Symbol Cast Algorithm Suite for EtherOS
// Inputs are 3D objects with ordering numbers and category colors.
// Complexity: O(n) = S(n) + cT(n) treating time as a spatial dimension.
// Referencing an object updates its position; copying leaves it in place.

using namespace std;

class Trees {
public:
    // Default constructor
    Trees() {}

    // Destructor
    ~Trees() {}

    // Copy constructor
    Trees(const Trees& other) = default;

    // Move constructor
    Trees(Trees&& other) noexcept = default;

    // Copy assignment
    Trees& operator=(const Trees& other) = default;

    // Move assignment
    Trees& operator=(Trees&& other) noexcept = default;
    // 1. invert binray tree:
    // You are given the root of a binary tree root. Invert the binary tree and return its root.
    // /**
    // * Definition for a binary tree node.
    // * struct TreeNode {
    // *     int val;
    // *     TreeNode *left;
    // *     TreeNode *right;
    // *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // * };
    // */
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;

        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);

        return root;
    }

    // 2. maximum depth of binary tree:
    // Given the root of a binary tree, return its depth.
    // The depth of a binary tree is defined as the number of nodes along the longest path from the root node down to the farthest leaf node.
    // /**
    // * Definition for a binary tree node.
    // * struct TreeNode {
    // *     int val;
    // *     TreeNode *left;
    // *     TreeNode *right;
    // *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // * };
    // */
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }

    // 3. diameter of binary tree:
    // The diameter of a binary tree is defined as the length of the longest path between any two nodes within the tree. The path does not necessarily have to pass through the root.
    // The length of a path between two nodes in a binary tree is the number of edges between the nodes.
    // Given the root of a binary tree root, return the diameter of the tree.
    // /**
    // * Definition for a binary tree node.
    // * struct TreeNode {
    // *     int val;
    // *     TreeNode *left;
    // *     TreeNode *right;
    // *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // * };
    // */
    class Solution {
    public:
        int diameterOfBinaryTree(TreeNode* root) {
            int res = 0;
            dfs(root, res);
            return res;
        }

    private:
        int dfs(TreeNode* root, int& res) {
            if (!root) {
                return 0;
            }
            int left = dfs(root->left, res);
            int right = dfs(root->right, res);
            res = max(res, left + right);
            return 1 + max(left, right);
        }
    };

    // 4. balanced binary tree:
    // Given a binary tree, return true if it is height-balanced and false otherwise.
    // A height-balanced binary tree is defined as a binary tree in which the left and right subtrees of every node differ in height by no more than 1.
    // /**
    // * Definition for a binary tree node.
    // * struct TreeNode {
    // *     int val;
    // *     TreeNode *left;
    // *     TreeNode *right;
    // *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // * };
    // */
    class Solution {
    public:
        bool isBalanced(TreeNode* root) {
            return dfs(root)[0] == 1;
        }

    private:
        vector<int> dfs(TreeNode* root) {
            if (!root) {
                return {1, 0};
            }

            vector<int> left = dfs(root->left);
            vector<int> right = dfs(root->right);

            bool balanced = (left[0] == 1 && right[0] == 1) && 
                            (abs(left[1] - right[1]) <= 1);
            int height = 1 + max(left[1], right[1]);

            return {balanced ? 1 : 0, height};
        }
    };

    // 5. same tree
    // Given the roots of two binary trees p and q, return true if the trees are equivalent, otherwise return false.
    // Two binary trees are considered equivalent if they share the exact same structure and the nodes have the same values.
    // /**
    // * Definition for a binary tree node.
    // * struct TreeNode {
    // *     int val;
    // *     TreeNode *left;
    // *     TreeNode *right;
    // *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // * };
    // */
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) {
            return true;
        }
        if (p && q && p->val == q->val) {
            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        } else {
            return false;
        }
    }

    // 6. subtree of another tree:
    // Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.

    // A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.

    // /**
    // * Definition for a binary tree node.
    // * struct TreeNode {
    // *     int val;
    // *     TreeNode *left;
    // *     TreeNode *right;
    // *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // * };
    // */
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!subRoot) {
            return true;
        }
        if (!root) {
            return false;
        }

        if (isSameTree(root, subRoot)) {
            return true;
        }
        return isSubtree(root->left, subRoot) || 
               isSubtree(root->right, subRoot);
    }

    // 7. Binary tree level order travesal:
    // Given a binary tree root, return the level order traversal of it as a nested list, where each sublist contains the values of nodes at a particular level in the tree, from left to right.
    // /**
    // * Definition for a binary tree node.
    // * struct TreeNode {
    // *     int val;
    // *     TreeNode *left;
    // *     TreeNode *right;
    // *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // * };
    // */
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            vector<int> level;
            int size = q.size();

            for (int i = q.size(); i > 0; i--) {
                TreeNode* node = q.front();
                q.pop();
                if (node) {
                    level.push_back(node->val);
                    q.push(node->left);
                    q.push(node->right);
                }
            }
            if (!level.empty()) {
                res.push_back(level);
            }
        }
        return res;
    }

    // 8. binary tree right side view:
    // You are given the root of a binary tree. Return only the values of the nodes that are visible from the right side of the tree, ordered from top to bottom.
    // /**
    // * Definition for a binary tree node.
    // * struct TreeNode {
    // *     int val;
    // *     TreeNode *left;
    // *     TreeNode *right;
    // *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // * };
    // */
    class Solution {
    public:
        vector<int> res;
        
        vector<int> rightSideView(TreeNode* root) {
            dfs(root, 0);
            return res;
        }
        
        void dfs(TreeNode* node, int depth) {
            if (!node) return;
            
            if (res.size() == depth) {
                res.push_back(node->val);
            }
            
            dfs(node->right, depth + 1);
            dfs(node->left, depth + 1);
        }
    };

    // 9. count good nodes in binary tree:
    // Within a binary tree, a node x is considered good if the path from the root of the tree to the node x contains no nodes with a value greater than the value of node x
    // Given the root of a binary tree root, return the number of good nodes within the tree.
    // /**
    // * Definition for a binary tree node.
    // * struct TreeNode {
    // *     int val;
    // *     TreeNode *left;
    // *     TreeNode *right;
    // *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // * };
    // */
    class Solution {
    public:
        int goodNodes(TreeNode* root) {
            return dfs(root, root->val);
        }

    private:
        int dfs(TreeNode* node, int maxVal) {
            if (!node) {
                return 0;
            }

            int res = (node->val >= maxVal) ? 1 : 0;
            maxVal = max(maxVal, node->val);
            res += dfs(node->left, maxVal);
            res += dfs(node->right, maxVal);
            return res;
        }
    };

    // 10. validate BS tree:
    // Given the root of a binary tree, return true if it is a valid binary search tree, otherwise return false.
    // A valid binary search tree satisfies the following constraints:
    // The left subtree of every node contains only nodes with keys less than the node's key.
    // The right subtree of every node contains only nodes with keys greater than the node's key.
    // Both the left and right subtrees are also binary search trees.
    // /**
    // * Definition for a binary tree node.
    // * struct TreeNode {
    // *     int val;
    // *     TreeNode *left;
    // *     TreeNode *right;
    // *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // * };
    // */
    class Solution {
    public:
        bool isValidBST(TreeNode* root) {
            return valid(root, LONG_MIN, LONG_MAX);
        }

        bool valid(TreeNode* node, long left, long right) {
            if (!node) {
                return true;
            }
            if (!(left < node->val && node->val < right)) {
                return false;
            }
            return valid(node->left, left, node->val) &&
                valid(node->right, node->val, right);
        }
    };

    // 11. kth smallest element in BST:
    // Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed) in the tree.

    // A binary search tree satisfies the following constraints:

    // The left subtree of every node contains only nodes with keys less than the node's key.
    // The right subtree of every node contains only nodes with keys greater than the node's key.
    // Both the left and right subtrees are also binary search trees.

    // /**
    // * Definition for a binary tree node.
    // * struct TreeNode {
    // *     int val;
    // *     TreeNode *left;
    // *     TreeNode *right;
    // *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // * };
    // */
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stack;
        TreeNode* curr = root;

        while (!stack.empty() || curr != nullptr) {
            while (curr != nullptr) {
                stack.push(curr);
                curr = curr->left;
            }
            curr = stack.top();
            stack.pop();
            k--;
            if (k == 0) {
                return curr->val;
            }
            curr = curr->right;
        }

        return -1; 
    }

    // 12. Construct Binary T w/ pre & in order traversal:
    // You are given two integer arrays preorder and inorder.

    // preorder is the preorder traversal of a binary tree
    // inorder is the inorder traversal of the same tree
    // Both arrays are of the same size and consist of unique values.
    // Rebuild the binary tree from the preorder and inorder traversals and return its root.

    // /**
    // * Definition for a binary tree node.
    // * struct TreeNode {
    // *     int val;
    // *     TreeNode *left;
    // *     TreeNode *right;
    // *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // * };
    // */

    class Solution {
        int preIdx = 0;
        int inIdx = 0;

        TreeNode* dfs(vector<int>& preorder, vector<int>& inorder, int limit) {
            if (preIdx >= preorder.size()) return nullptr;
            if (inorder[inIdx] == limit) {
                inIdx++;
                return nullptr;
            }

            TreeNode* root = new TreeNode(preorder[preIdx++]);
            root->left = dfs(preorder, inorder, root->val);
            root->right = dfs(preorder, inorder, limit);
            return root;
        }

    public:
        TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
            return dfs(preorder, inorder, INT_MAX);
        }
    };

    // 13. Binary Tree Maximum Path Sum:
    // Given the root of a non-empty binary tree, return the maximum path sum of any non-empty path.

    // A path in a binary tree is a sequence of nodes where each pair of adjacent nodes has an edge connecting them. A node can not appear in the sequence more than once. The path does not necessarily need to include the root.

    // The path sum of a path is the sum of the node's values in the path.

    // /**
    // * Definition for a binary tree node.
    // * struct TreeNode {
    // *     int val;
    // *     TreeNode *left;
    // *     TreeNode *right;
    // *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // * };
    // */

    class Solution {
    public:
        int maxPathSum(TreeNode* root) {
            int res = root->val;
            dfs(root, res);
            return res;
        }

    private:
        int dfs(TreeNode* root, int& res) {
            if (!root) {
                return 0;
            }

            int leftMax = max(dfs(root->left, res), 0);
            int rightMax = max(dfs(root->right, res), 0);

            res = max(res, root->val + leftMax + rightMax);
            return root->val + max(leftMax, rightMax);
        }
    };

    // 14. Serialize and deserialize a Binary Tree:
    // Implement an algorithm to serialize and deserialize a binary tree.
    // Serialization is the process of converting an in-memory structure into a sequence of bits so that it can be stored or sent across a network to be reconstructed later in another computer environment.
    // You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure. There is no additional restriction on how your serialization/deserialization algorithm should work.
    // Note: The input/output format in the examples is the same as how NeetCode serializes a binary tree. You do not necessarily need to follow this format.
    // /**
    // * Definition for a binary tree node.
    // * struct TreeNode {
    // *     int val;
    // *     TreeNode *left;
    // *     TreeNode *right;
    // *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    // *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // * };
    // */
    class Codec {
    public:
        // Encodes a tree to a single string.
        string serialize(TreeNode* root) {
            vector<string> res;
            dfsSerialize(root, res);
            return join(res, ",");
        }

        // Decodes your encoded data to tree.
        TreeNode* deserialize(string data) {
            vector<string> vals = split(data, ',');
            int i = 0;
            return dfsDeserialize(vals, i);
        }

    private:
        void dfsSerialize(TreeNode* node, vector<string>& res) {
            if (!node) {
                res.push_back("N");
                return;
            }
            res.push_back(to_string(node->val));
            dfsSerialize(node->left, res);
            dfsSerialize(node->right, res);
        }

        TreeNode* dfsDeserialize(vector<string>& vals, int& i) {
            if (vals[i] == "N") {
                i++;
                return NULL;
            }
            TreeNode* node = new TreeNode(stoi(vals[i]));
            i++;
            node->left = dfsDeserialize(vals, i);
            node->right = dfsDeserialize(vals, i);
            return node;
        }

        vector<string> split(const string &s, char delim) {
            vector<string> elems;
            stringstream ss(s);
            string item;
            while (getline(ss, item, delim)) {
                elems.push_back(item);
            }
            return elems;
        }

        string join(const vector<string> &v, const string &delim) {
            ostringstream s;
            for (const auto &i : v) {
                if (&i != &v[0])
                    s << delim;
                s << i;
            }
            return s.str();
        }
    };

private:
    // Add internal helper functions here if needed
};