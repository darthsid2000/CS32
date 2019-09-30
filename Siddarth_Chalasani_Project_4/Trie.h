#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;
    
    // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
    struct Node {
        std::vector<ValueType> values;
        char label;
        std::vector<Node*> children;
    };
    Node* m_head;
    
    void deleteHelper(Node* n) {
        if (n == nullptr)
            return;
        for (int i = 0; i < n->children.size(); i++)
            deleteHelper(n->children[i]);
        delete n;
        n = nullptr;
    }
    
    void findHelper(const std::string& key, bool exactMatchOnly, Node* n, std::vector<ValueType>& sum) const {
        if (n == nullptr)
            return;
        if (key.size() == 0) {
            for (int i = 0; i < n->values.size(); i++)
                sum.push_back(n->values[i]);
            return;
        }
        for (int i = 0; i < n->children.size(); i++)
            if (n->children[i]->label == key[0]) {
                findHelper(&key[1], exactMatchOnly, n->children[i], sum);
                return;
            }
        if (!exactMatchOnly) {
            for (int i = 0; i < n->children.size(); i++)
                findHelper(&key[1], true, n->children[i], sum);
        }
    }
};

template <typename ValueType>
Trie<ValueType>::Trie() {
    m_head = new Node;
}

template <typename ValueType>
Trie<ValueType>::~Trie() {
    deleteHelper(m_head);
}

template <typename ValueType>
void Trie<ValueType>::reset() {
    deleteHelper(m_head);
    m_head = new Node;
}

template <typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value) {
    Node* n = m_head;
    bool foundNode = false;
    for (int i = 0; i < key.size(); i++) {
        for (int j = 0; j < n->children.size(); j++)
            if (n->children[j]->label == key[i]) {
                foundNode = true;
                n = n->children[j];
                break;
            }
        if (foundNode) {
            foundNode = false;
            continue;
        }
        Node* temp = new Node;
        temp->label = key[i];
        n->children.push_back(temp);
        n = temp;
    }
    n->values.push_back(value);
}

template <typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const {
    std::vector<ValueType> matches;
    for (int i = 0; i < m_head->children.size(); i++)
        if (m_head->children[i]->label == key[0])
            findHelper(&key[1], exactMatchOnly, m_head->children[i], matches);
    return matches;
}

#endif // TRIE_INCLUDED
