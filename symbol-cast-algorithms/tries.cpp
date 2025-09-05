#include <vector>
#include <string>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

// Symbol Cast Algorithm Suite for EtherOS
// Inputs are 3D objects with ordering numbers and category colors.
// Complexity: O(n) = S(n) + cT(n) treating time as a spatial dimension.
// Referencing an object updates its position; copying leaves it in place.

using namespace std;

class Tries {
public:
    Tries() {}
    ~Tries() {}
    Tries(const Tries& other) = default;
    Tries(Tries&& other) noexcept = default;
    Tries& operator=(const Tries& other) = default;
    Tries& operator=(Tries&& other) noexcept = default;

    // 1. Implment a trie prefix tree:
    // A prefix tree (also known as a trie) is a tree data structure used to efficiently store and retrieve keys in a set of strings. Some applications of this data structure include auto-complete and spell checker systems.

    // Implement the PrefixTree class:

    // PrefixTree() Initializes the prefix tree object.
    // void insert(String word) Inserts the string word into the prefix tree.
    // boolean search(String word) Returns true if the string word is in the prefix tree (i.e., was inserted before), and false otherwise.
    // boolean startsWith(String prefix) Returns true if there is a previously inserted string word that has the prefix prefix, and false otherwise.

    class TrieNode {
    public:
        unordered_map<char, TrieNode*> children;
        bool endOfWord = false;
    };

    class PrefixTree {
        TrieNode* root;

    public:
        PrefixTree() {
            root = new TrieNode();
        }

        void insert(string word) {
            TrieNode* cur = root;
            for (char c : word) {
                if (cur->children.find(c) == cur->children.end()) {
                    cur->children[c] = new TrieNode();
                }
                cur = cur->children[c];
            }
            cur->endOfWord = true;
        }

        bool search(string word) {
            TrieNode* cur = root;
            for (char c : word) {
                if (cur->children.find(c) == cur->children.end()) {
                    return false;
                }
                cur = cur->children[c];
            }
            return cur->endOfWord;
        }

        bool startsWith(string prefix) {
            TrieNode* cur = root;
            for (char c : prefix) {
                if (cur->children.find(c) == cur->children.end()) {
                    return false;
                }
                cur = cur->children[c];
            }
            return true;
        }
    };

    // 2. desgin word search data structure:
    // Design a data structure that supports adding new words and searching for existing words.

    // Implement the WordDictionary class:

    // void addWord(word) Adds word to the data structure.
    // bool search(word) Returns true if there is any string in the data structure that matches word or false otherwise. word may contain dots '.' where dots can be matched with any letter.

    class TrieNode {
    public:
        vector<TrieNode*> children;
        bool word;

        TrieNode() : children(26, nullptr), word(false) {}
    };

    class WordDictionary {
    public:
        TrieNode* root;

        WordDictionary() : root(new TrieNode()) {}

        void addWord(string word) {
            TrieNode* cur = root;
            for (char c : word) {
                if (cur->children[c - 'a'] == nullptr) {
                    cur->children[c - 'a'] = new TrieNode();
                }
                cur = cur->children[c - 'a'];
            }
            cur->word = true;
        }

        bool search(string word) {
            return dfs(word, 0, root);
        }

    private:
        bool dfs(string word, int j, TrieNode* root) {
            TrieNode* cur = root;

            for (int i = j; i < word.size(); i++) {
                char c = word[i];
                if (c == '.') {
                    for (TrieNode* child : cur->children) {
                        if (child != nullptr && dfs(word, i + 1, child)) {
                            return true;
                        }
                    }
                    return false;
                } else {
                    if (cur->children[c - 'a'] == nullptr) {
                        return false;
                    }
                    cur = cur->children[c - 'a'];
                }
            }
            return cur->word;
        }
    };

    // 3. Word Search 2:
    // Given a 2-D grid of characters board and a list of strings words, return all words that are present in the grid.

    // For a word to be present it must be possible to form the word with a path in the board with horizontally or vertically neighboring cells. The same cell may not be used more than once in a word.

    class TrieNode {
    public:
        unordered_map<char, TrieNode*> children;
        bool isWord;

        TrieNode() : isWord(false) {}

        void addWord(const string& word) {
            TrieNode* cur = this;
            for (char c : word) {
                if (!cur->children.count(c)) {
                    cur->children[c] = new TrieNode();
                }
                cur = cur->children[c];
            }
            cur->isWord = true;
        }
    };

    class Solution {
        unordered_set<string> res;
        vector<vector<bool>> visit;
    public:
        vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
            TrieNode* root = new TrieNode();
            for (const string& word : words) {
                root->addWord(word);
            }

            int ROWS = board.size(), COLS = board[0].size();
            visit.assign(ROWS, vector<bool>(COLS, false));

            for (int r = 0; r < ROWS; ++r) {
                for (int c = 0; c < COLS; ++c) {
                    dfs(board, r, c, root, "");
                }
            }
            return vector<string>(res.begin(), res.end());
        }

    private:
        void dfs(vector<vector<char>>& board, int r, int c, TrieNode* node, string word) {
            int ROWS = board.size(), COLS = board[0].size();
            if (r < 0 || c < 0 || r >= ROWS || 
                c >= COLS || visit[r][c] || 
                !node->children.count(board[r][c])) {
                return;
            }

            visit[r][c] = true;
            node = node->children[board[r][c]];
            word += board[r][c];
            if (node->isWord) {
                res.insert(word);
            }

            dfs(board, r + 1, c, node, word);
            dfs(board, r - 1, c, node, word);
            dfs(board, r, c + 1, node, word);
            dfs(board, r, c - 1, node, word);

            visit[r][c] = false;
        }
    };

private:
    // No internal members yet
};