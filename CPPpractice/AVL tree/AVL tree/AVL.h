#pragma once
#include <utility>  // ?? 必须包含这个才能用 std::pair 喵！
#include <cassert>  // ?? 必须包含这个才能用 assert 喵！
#include <iostream> 
#include <algorithm> // ?? 等会儿算高度要用到 std::max
template<class K, class V>
struct AVLTreeNode
{
	// 需要parent指针，后续更新平衡因子可以看到
	pair<K, V> _kv;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf; // balance factor
	AVLTreeNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
	{
	}
};
template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	//...
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(kv);
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;
		// 更新平衡因子
		while (parent)
		{
			// 更新平衡因子
			if (cur == parent->_left)
				parent->_bf--;
			else
				parent->_bf++;
			if (parent->_bf == 0)
			{
				// 更新结束
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				// 继续往上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{

				// 不平衡了，旋转处理喵！
				if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateR(parent);     // 单一左偏，右旋处理
				}
				else if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateL(parent);     // 单一右偏，左旋处理
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					RotateLR(parent);    // ?? 补上：折线左偏，左右双旋
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					RotateRL(parent);    // ?? 补上：折线右偏，右左双旋
				}
				break; // 旋转完必定平衡，可以直接退出大循环了喵！
			}
			else
			{
				assert(false);
			}
		}
		return true;
	}
	void RotateR(Node* parent)
	{
		if (parent == nullptr || parent->_left == nullptr) return;
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;
		parent->_left = subLR;
		if (subLR != nullptr)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		parent->_parent = subL;
		if (parent == _root)
		{
			_root = subL; 
			_root->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}
		subL->_bf = 0;
		parent->_bf = 0;
	}
	void RotateL(Node* parent)
	{
		if (parent == nullptr || parent->_right == nullptr) return;
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* ppNode = parent->_parent;
		parent->_right = subRL;
		if (subRL != nullptr)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		parent->_parent = subR;
		if (parent == _root)
		{
			_root = subR; 
			_root->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}
		subR->_bf = 0;
		parent->_bf = 0;
	}
	// ?? 左右双旋 (RotateLR) - 应对新节点插在左孩子的右子树的场景喵！
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		// [防御性编程] 抓取命运的毛线球：必须提前缓存 subLR 的平衡因子！
		// 因为一旦复用单旋，平衡因子会被错误地全部清零喵
		int bf = subLR->_bf;

		// 1. 结构化旋转：先让左孩子向左转，再让父亲向右转
		RotateL(parent->_left);
		RotateR(parent);

		// 2. 降维打击：根据缓存的 bf 重新分配平衡因子
		if (bf == 0)
		{
			// 情况 A：subLR 自己就是那个新插入的节点
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			// 情况 B：新节点插在了 subLR 的左子树
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == 1)
		{
			// 情况 C：新节点插在了 subLR 的右子树
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else
		{
			// 抓虫！如果遇到其他值，说明树在旋转前就已经坏掉了，果断崩溃报错喵！
			assert(false);
		}
	}

	// ?? 右左双旋 (RotateRL) - 应对新节点插在右孩子的左子树的场景喵！
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		// [防御性编程] 同样，提前记录双旋枢纽节点 subRL 的平衡因子喵
		int bf = subRL->_bf;

		// 1. 结构化旋转：先让右孩子向右转，再让父亲向左转
		RotateR(parent->_right);
		RotateL(parent);

		// 2. 平衡因子精准打击
		if (bf == 0)
		{
			// 情况 A：subRL 自己就是新插入的小猫咪
			parent->_bf = 0;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			// 情况 B：新节点插在了 subRL 的右子树
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == -1)
		{
			// 情况 C：新节点插在了 subRL 的左子树
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else
		{
			assert(false); // 绝不容忍异常状态喵！
		}
	}
	void InOrder()
	{
		_InOrder(_root);
		std::cout << std::endl;
	}
	bool IsBalanceTree()
	{
		return _IsBalanceTree(_root);
	}
	int Height()
	{
		return _Height(_root);
	}
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key)
			{
				cur = cur->_right;
			}
			else if (cur->_kv.first > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}

		return nullptr;
	}
	int Size()
	{
		return _Size(_root);
	}
private:
	int _Size(Node* root)
	{
		if (root == nullptr)
			return 0;

		return _Size(root->_left) + _Size(root->_right) + 1;
	}
	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}
	bool _IsBalanceTree(Node* root)
	{
		// 空树也是AVL树
		if (nullptr == root)
			return true;
		// 计算pRoot结点的平衡因子：即pRoot左右子树的高度差
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		int diff = rightHeight - leftHeight;
		// 如果计算出的平衡因子与pRoot的平衡因子不相等，或者
// pRoot平衡因子的绝对值超过1，则一定不是AVL树
		if (abs(diff) >= 2)
		{
			cout << root->_kv.first << "高度差异常" << endl;
			return false;
		}
		if (root->_bf != diff)
		{
			cout << root->_kv.first << "平衡因子异常" << endl;
			return false;
		}
		// pRoot的左和右如果都是AVL树，则该树一定是AVL树
		return _IsBalanceTree(root->_left) && _IsBalanceTree(root->_right);
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr) return;
		_InOrder(root->_left);
		std::cout << root->_kv.first << ":" << root->_kv.second << std::endl;
		_InOrder(root->_right);
	}
	Node* _root = nullptr;
};