#include <iostream>
using namespace std;

// === 1. 定义树的节点结构 ===
template<class K>
struct BSTNode
{
    K _key;
    BSTNode<K>* _left;
    BSTNode<K>* _right;

    BSTNode(const K& key)
        : _key(key), _left(nullptr), _right(nullptr) {
    }
};

// === 2. 二叉搜索树类封装 ===
template<class K>
class BSTree
{
    typedef BSTNode<K> Node;


public:
    // === 3. 公有接口：插入 ===
    bool Insert(const K& key) {
        if (_root == nullptr) {
            _root = new Node(key);
            return true;
        }

        Node* parent = nullptr;
        Node* cur = _root;

        while (cur) {
            if (cur->_key < key) {
                parent = cur;
                cur = cur->_right;
            }
            else if (cur->_key > key) {
                parent = cur;
                cur = cur->_left;
            }
            else {
                return false;
            }
        }

        cur = new Node(key);
        if (parent->_key < key) {
            parent->_right = cur;
        }
        else {
            parent->_left = cur;
        }
        return true;
    }

    // === 4. 公有接口：查找 ===
    bool Find(const K& key) {
        Node* cur = _root;
        while (cur) {
            if (cur->_key < key) {
                cur = cur->_right;
            }
            else if (cur->_key > key) {
                cur = cur->_left;
            }
            else {
                return true;
            }
        }
        return false;
    }

    // === 5. 公有接口：删除 ===
    bool Erase(const K& key) {
        Node* parent = nullptr;
        Node* cur = _root;

        while (cur) {
            if (cur->_key < key) {
                parent = cur;
                cur = cur->_right;
            }
            else if (cur->_key > key) {
                parent = cur;
                cur = cur->_left;
            }
            else {
                if (cur->_left == nullptr) {
                    if (parent == nullptr) {
                        _root = cur->_right;
                    }
                    else {
                        if (parent->_left == cur) parent->_left = cur->_right;
                        else parent->_right = cur->_right;
                    }
                    delete cur;
                    return true;

                }
                else if (cur->_right == nullptr) {
                    if (parent == nullptr) {
                        _root = cur->_left;
                    }
                    else {
                        if (parent->_left == cur) parent->_left = cur->_left;
                        else parent->_right = cur->_left;
                    }
                    delete cur;
                    return true;

                }
                else {
                    Node* rightMinP = cur;
                    Node* rightMin = cur->_right;

                    while (rightMin->_left) {
                        rightMinP = rightMin;
                        rightMin = rightMin->_left;
                    }

                    cur->_key = rightMin->_key;

                    if (rightMinP->_left == rightMin) {
                        rightMinP->_left = rightMin->_right;
                    }
                    else {
                        rightMinP->_right = rightMin->_right;
                    }

                    delete rightMin;
                    return true;
                }
            }
        }
        return false;
    }

    // === 6. 公有接口：中序遍历入口 ===
    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }

private:
    Node* _root = nullptr;

    // === 6. 私有递归：中序遍历 ===
    void _InOrder(Node* root) {
        if (root == nullptr) return;
        _InOrder(root->_left);
        cout << root->_key << " ";
        _InOrder(root->_right);
    }
};