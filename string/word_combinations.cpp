#include<bits/stdc++.h>
using namespace std;


class Trie {
    class TrieNode {
        static int R;
        int _val;
        bool _has_val;
        vector<TrieNode*> _children;
    public:
        TrieNode(int val): _val(val), _has_val(false), _children(vector<TrieNode*>(26, nullptr)) {}
        
        int get_val() { return _val; }
        void set_val(int val) { _val = val, _has_val = true; }
        bool has_val() { return _has_val; }
        vector<TrieNode*>& get_children() { return _children; }
        TrieNode*& get_child(char ch) { return _children[ch - 'a']; }
        void set_child(char ch, TrieNode *val) { _children[ch - 'a'] = val; }
    };
    int R = 26; 
    static int NO_VALUE;
    TrieNode* _root;

    TrieNode *get(TrieNode *root, int ind, const string &key) {
        if (!root || ind == key.size()) return root;
        return get(root->get_child(key[ind]), ind + 1, key);
    }

    TrieNode *put(TrieNode *root, int ind, const string &key, int val) {
        if (!root) root = new TrieNode(NO_VALUE);
        if (ind == key.size()) { root->set_val(val); return root; }
        root->set_child(key[ind], put(root->get_child(key[ind]), ind + 1, key, val));
        return root;
    }
    
    void destroy(TrieNode *root) {
        if (!root) return;
        for (TrieNode* child: root->get_children()) 
            destroy(child);
        
        delete root;
    }

public:
    Trie(): _root(new TrieNode(NO_VALUE)) {}
    ~Trie() { destroy(_root); _root = nullptr; }

    int get(const string &key) {
        TrieNode *node = get(_root, 0, key);
        return (node == nullptr || !node->has_val()) ? NO_VALUE : node->get_val();
    }

    void put(const string &key, int val) { _root = put(_root, 0, key, val); }

    
    class Iterator {
        TrieNode *_root;
        TrieNode *_curr_node;
    
    public:
        Iterator(TrieNode *root): _root(root), _curr_node(root) {}
        
        //* returns true if there is a child node via {ch} edge from current iterator node
        //* otherwise returns false
        bool move(char ch) {
            if (!_curr_node || !_curr_node->get_child(ch)) return false;
            _curr_node = _curr_node->get_child(ch);
            return true; 
        }
    };

    Iterator getIterator() {
        return Iterator(_root);
    }

};

int Trie::NO_VALUE = 0;

class Solver {
    const long long MOD = 1e9 + 7;

    const string &str;
    const unordered_set<string> &dict;
    Trie trie;

    vector<int> memo;

    long long ways(int i) {
        if (i == str.size()) return 1;
        if (memo[i] != -1) return memo[i];

        long long res = 0;
        string substr;
        Trie::Iterator trie_itr = trie.getIterator();
        for (int j = i; j < str.size(); ++j) {
            substr.push_back(str[j]);
            if (!trie_itr.move(str[j])) break;
            res = (res + ways(j + 1)) % MOD;
        }   
        return memo[i] = res;
    }
public:
    Solver(const string &str, const unordered_set<string> &dict) :str(str), dict(dict) {
        trie = Trie();
        for (const string &dict_string: dict) {
            trie.put(dict_string, true);
        }
    }

    long long countWays() {
        memo = vector<int>(str.size(), -1);
        return ways(0);
    }
};


int main() {
    string str;
    int k;
    unordered_set<string> dict;
    cin >> str;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        string temp;
        cin >> temp;
        dict.insert(temp);
    }    
    printf("%lld", Solver(str, dict).countWays());
    return 0;
}