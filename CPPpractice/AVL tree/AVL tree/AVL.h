#pragma once
#include <utility>  //  必须包含这个才能用 std::pair 喵！
#include <cassert>  //  必须包含这个才能用 assert 喵！
#include <iostream> 
#include <algorithm> //  等会儿算高度要用到 std::max
template<class K, class V>
struct AVLTreeNode
{
	// 需要parent指针，后续更新平衡因子可以看到
	pair<K, V> _kv;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf; // 平衡因子
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
				parent->_bf++;
			else
				parent->_bf--;
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
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateR(parent);     // 单一左偏，右旋处理
				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateL(parent);     // 单一右偏，左旋处理
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					RotateLR(parent);    //  补上：折线左偏，左右双旋
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					RotateRL(parent);    //  补上：折线右偏，右左双旋
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
	// AVL 树删除核心模块实现
	bool Erase(const K& key) {
		Node* parent = nullptr;
		Node* cur = _root;
		Node* del = nullptr; // 真正需要执行物理删除的节点

		// 1. 寻找目标节点
		while (cur) {
			if (cur->_kv.first < key) {
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > key) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				del = cur;
				break;
			}
		}

		if (del == nullptr) return false; // 没找到

		// 2. 准备执行物理删除：处理有两个孩子的情况
		if (del->_left && del->_right) {
			// 寻找右子树最小节点（后继）进行替换
			Node* minRight = del->_right;
			while (minRight->_left) minRight = minRight->_left;

			del->_kv = minRight->_kv; // 替换数据
			del = minRight;           // 转化为删除 minRight
			parent = del->_parent;    // 重置父节点位置
		}

		// 此时 del 只有 0 个或 1 个孩子
		Node* child = del->_left ? del->_left : del->_right;
		Node* actualDelParent = del->_parent; // 记录实际被删节点的父节点

		// 3. 执行物理删除与链接
		if (child) child->_parent = actualDelParent;

		bool isDeleteLeft = false; // 【核心修复】引入布尔值精准记录删除方向，拒绝野指针比较
		if (actualDelParent == nullptr) {
			_root = child;
		}
		else {
			if (actualDelParent->_left == del) {
				actualDelParent->_left = child;
				isDeleteLeft = true;  // 记录：删掉了左边
			}
			else {
				actualDelParent->_right = child;
				isDeleteLeft = false; // 记录：删掉了右边
			}
		}

		// 4. 从实际物理删除节点的父节点开始，向上回溯更新平衡因子
		Node* node = actualDelParent;

		while (node) {
			// 更新 BF (左减右标准)
			if (isDeleteLeft) node->_bf--; // 删了左，左高降低
			else node->_bf++;              // 删了右，右高降低

			// 判定回溯条件
			if (node->_bf == 1 || node->_bf == -1) {
				// 情况 A：高度没变，停止回溯
				break;
			}
			else if (node->_bf == 0) {
				// 情况 B：高度减小，继续回溯。同时判断当前子树是祖先的哪一边！
				Node* ppNode = node->_parent;
				if (ppNode) {
					isDeleteLeft = (ppNode->_left == node);
				}
				node = ppNode;
			}
			else if (node->_bf == 2 || node->_bf == -2) {
				// 情况 C：失衡，需要旋转
				Node* ppNode = node->_parent;
				// 【核心修复】提前记录旋转前，当前失衡子树挂在祖父节点的哪一边
				bool wasLeft = (ppNode && ppNode->_left == node);
				Node* newRoot = nullptr;

				if (node->_bf == 2) { // 左边高
					Node* subL = node->_left;
					if (subL->_bf >= 0) {
						newRoot = subL;
						RotateR(node);
					}
					else {
						newRoot = subL->_right;
						RotateLR(node);
					}
				}
				else { // 右边高
					Node* subR = node->_right;
					if (subR->_bf <= 0) {
						newRoot = subR;
						RotateL(node);
					}
					else {
						newRoot = subR->_left;
						RotateRL(node);
					}
				}

				// 旋转后，如果新根的 BF 为 0，说明高度降低了，需继续回溯
				if (newRoot->_bf == 0) {
					node = ppNode;
					if (node) {
						isDeleteLeft = wasLeft; // 继承旋转前记录的方向
					}
				}
				else {
					// 如果旋转后 BF 不为 0，高度其实没变，停止
					break;
				}
			}
			else {
				assert(false); // 防御性编程，抓取异常状态
			}
		}

		delete del;
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
		//subL->_bf = 0;
		//parent->_bf = 0;
		// 降维打击：兼容删除场景的平衡因子分配
		if (subL->_bf == 0) {
			parent->_bf = 1;
			subL->_bf = -1;
		}
		else {
			parent->_bf = 0;
			subL->_bf = 0;
		}
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
		//subR->_bf = 0;
		//parent->_bf = 0;
		// 降维打击：兼容删除场景的平衡因子分配
		if (subR->_bf == 0) {
			parent->_bf = -1;
			subR->_bf = 1;
		}
		else {
			parent->_bf = 0;
			subR->_bf = 0;
		}
	}
	//  左右双旋 (RotateLR) - 应对新节点插在左孩子的右子树的场景喵！
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		// 2. 降维打击：精准重分配平衡因子 (左减右标准)
		if (bf == 0)
		{
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == 1) // 新节点在 subLR 的左子树
		{
			parent->_bf = -1; // parent 分到右子树(较矮)，所以左-右 = -1
			subL->_bf = 0;    // subL 分到左子树(较高)，正好扯平 = 0
			subLR->_bf = 0;
		}
		else if (bf == -1) // 新节点在 subLR 的右子树
		{
			parent->_bf = 0;  // parent 分到右子树(较高)，正好扯平 = 0
			subL->_bf = 1;    // subL 分到左子树(较矮)，所以左-右 = 1
			subLR->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	//  右左双旋 (RotateRL) - 应对新节点插在右孩子的左子树的场景喵！
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);

		// 2. 平衡因子精准打击 (左减右标准)
		if (bf == 0)
		{
			parent->_bf = 0;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == 1) // 新节点在 subRL 的左子树
		{
			parent->_bf = 0;  // parent 分到左子树(较高)，扯平 = 0
			subR->_bf = -1;   // subR 分到右子树(较矮)，左-右 = -1
			subRL->_bf = 0;
		}
		else if (bf == -1) // 新节点在 subRL 的右子树
		{
			parent->_bf = 1;  // parent 分到左子树(较矮)，左-右 = 1
			subR->_bf = 0;    // subR 分到右子树(较高)，扯平 = 0
			subRL->_bf = 0;
		}
		else
		{
			assert(false);
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
		if (nullptr == root)
			return true;

		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);

		// 必须严格坚持：左边 - 右边 喵！
		int diff = leftHeight - rightHeight;

		if (abs(diff) >= 2)
		{
			cout << root->_kv.first << " 高度差异常" << endl;
			return false;
		}
		if (root->_bf != diff)
		{
			cout << root->_kv.first << " 平衡因子异常，真实差值:" << diff << "，记录值:" << root->_bf << endl;
			return false;
		}
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