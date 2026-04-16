#pragma once
#include <iostream>
#include <utility>
namespace key_value
{
    template<class K, class V>
    struct BSTNode
    {
        K _key;
        V _value;
        BSTNode<K, V>* _left;
        BSTNode<K, V>* _right;

        BSTNode(const K& key, const V& value)
            : _key(key)
            , _value(value)
            , _left(nullptr)
            , _right(nullptr)
        {
        }
    };

    template<class K, class V>
    class BSTree
    {
        using Node = BSTNode<K, V>;
    public:
        BSTree() = default;

        BSTree(const BSTree& t)
        {
            _root = Copy(t._root);
        }
        BSTree& operator=(BSTree tmp)
        {
            std::swap(_root, tmp._root);
            return *this;
        }

        ~BSTree()
        {
            _Destroy(_root);
            _root = nullptr;
        }

        bool insert(const K& key, const V& value)
        {
            if (_root == nullptr)
            {
                _root = new Node(key, value);
                return true;
            }
            Node* parent = nullptr;
            Node* cur = _root;
            while (cur)
            {
                if (cur->_key < key) { parent = cur; cur = cur->_right; }
                else if (cur->_key > key) { parent = cur; cur = cur->_left; }
                else return false;
            }

            cur = new Node(key, value);
            if (parent->_key < key) parent->_right = cur;
            else parent->_left = cur;
            return true;
        }

        bool erase(const K& key)
        {
            Node* parent = nullptr;
            Node* cur = _root;
            while (cur)
            {
                if (key < cur->_key) { parent = cur; cur = cur->_left; }
                else if (key > cur->_key) { parent = cur; cur = cur->_right; }
                else break;
            }
            if (cur == nullptr) return false;

            if (cur->_left == nullptr)
            {
                if (cur == _root) _root = cur->_right;
                else if (parent->_left == cur) parent->_left = cur->_right;
                else parent->_right = cur->_right;
                delete cur;
            }
            else if (cur->_right == nullptr)
            {
                if (cur == _root) _root = cur->_left;
                else if (parent->_left == cur) parent->_left = cur->_left;
                else parent->_right = cur->_left;
                delete cur;
            }
            else
            {
                Node* rightMinParent = cur;
                Node* rightMin = cur->_right;

                while (rightMin->_left)
                {
                    rightMinParent = rightMin;
                    rightMin = rightMin->_left;
                }
                cur->_key = rightMin->_key;
                cur->_value = rightMin->_value;

                if (rightMinParent->_left == rightMin) rightMinParent->_left = rightMin->_right;
                else rightMinParent->_right = rightMin->_right;

                delete rightMin;
            }
            return true;
        }
        V* Find(const K& key)
        {
            Node* cur = _root;
            while (cur)
            {
                if (cur->_key < key) cur = cur->_right;
                else if (cur->_key > key) cur = cur->_left;
                else return &(cur->_value);
            }
            return nullptr;
        }

        void InOrder()
        {
            _InOrder(_root);
            std::cout << std::endl;
        }

    private:
        Node* Copy(Node* root)
        {
            if (root == nullptr) return nullptr;
            Node* newNode = new Node(root->_key, root->_value);
            newNode->_left = Copy(root->_left);
            newNode->_right = Copy(root->_right);
            return newNode;
        }

        void _Destroy(Node* root)
        {
            if (root == nullptr) return;
            _Destroy(root->_left);
            _Destroy(root->_right);
            delete root;
        }

        void _InOrder(Node* root)
        {
            if (root == nullptr) return;
            _InOrder(root->_left);
            std::cout << root->_key << ":" << root->_value << std::endl;
            _InOrder(root->_right);
        }

        Node* _root = nullptr;
    };
}
namespace key
{
    template<class K>
    struct BSTNode
    {
        K _key;
        BSTNode<K>* _left;
        BSTNode<K>* _right;

        BSTNode(const K& key)
            : _key(key)
            , _left(nullptr)
            , _right(nullptr)
        {
        }
    };

    template<class K>
    class BSTree
    {
        using Node = BSTNode<K>;
    public:
        BSTree() = default;

        BSTree(const BSTree& t)
        {
            _root = Copy(t._root);
        }

        BSTree& operator=(BSTree tmp)
        {
            std::swap(_root, tmp._root);
            return *this;
        }

        ~BSTree()
        {
            _Destroy(_root);
            _root = nullptr;
        }

        bool insert(const K& key)
        {
            if (_root == nullptr)
            {
                _root = new Node(key);
                return true;
            }
            Node* parent = nullptr;
            Node* cur = _root;
            while (cur)
            {
                if (cur->_key < key) { parent = cur; cur = cur->_right; }
                else if (cur->_key > key) { parent = cur; cur = cur->_left; }
                else return false;
            }

            cur = new Node(key);
            if (parent->_key < key) parent->_right = cur;
            else parent->_left = cur;

            return true;
        }

        bool erase(const K& key)
        {
            Node* parent = nullptr;
            Node* cur = _root;
            while (cur)
            {
                if (key < cur->_key) { parent = cur; cur = cur->_left; }
                else if (key > cur->_key) { parent = cur; cur = cur->_right; }
                else break;
            }
            if (cur == nullptr) return false;

            if (cur->_left == nullptr)
            {
                if (cur == _root) _root = cur->_right;
                else if (parent->_left == cur) parent->_left = cur->_right;
                else parent->_right = cur->_right;
                delete cur;
            }
            else if (cur->_right == nullptr)
            {
                if (cur == _root) _root = cur->_left;
                else if (parent->_left == cur) parent->_left = cur->_left;
                else parent->_right = cur->_left;
                delete cur;
            }
            else
            {
                Node* rightMinParent = cur;
                Node* rightMin = cur->_right;

                while (rightMin->_left)
                {
                    rightMinParent = rightMin;
                    rightMin = rightMin->_left;
                }
                cur->_key = rightMin->_key;

                if (rightMinParent->_left == rightMin) rightMinParent->_left = rightMin->_right;
                else rightMinParent->_right = rightMin->_right;

                delete rightMin;
            }
            return true;
        }

        bool Find(const K& key)
        {
            Node* cur = _root;
            while (cur)
            {
                if (cur->_key < key) cur = cur->_right;
                else if (cur->_key > key) cur = cur->_left;
                else return true;
            }
            return false;
        }

        void InOrder()
        {
            _InOrder(_root);
            std::cout << std::endl;
        }

    private:
        Node* Copy(Node* root)
        {
            if (root == nullptr) return nullptr;
            Node* newNode = new Node(root->_key);
            newNode->_left = Copy(root->_left);
            newNode->_right = Copy(root->_right);
            return newNode;
        }

        void _Destroy(Node* root)
        {
            if (root == nullptr) return;
            _Destroy(root->_left);
            _Destroy(root->_right);
            delete root;
        }

        void _InOrder(Node* root)
        {
            if (root == nullptr) return;

            _InOrder(root->_left);
            std::cout << root->_key << " "; 
            _InOrder(root->_right);
        }

        Node* _root = nullptr;
    };
}