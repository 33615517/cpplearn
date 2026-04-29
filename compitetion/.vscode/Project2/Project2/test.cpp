#include <iostream>
#include <vector>
#include"add.h"

void TestBSTree() {
    BSTree<int> bst;

    // 使用经典测试用例构建树：8 3 10 1 6 14 4 7 13
    std::vector<int> arr = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };

    std::cout << "=== 1. 测试插入与中序遍历 ===" << std::endl;
    for (int e : arr) {
        bst.Insert(e);
    }
    std::cout << "预期输出 (严格递增): 1 3 4 6 7 8 10 13 14" << std::endl;
    std::cout << "实际输出:           ";
    bst.InOrder();

    std::cout << "\n=== 2. 测试重复插入 (容错性) ===" << std::endl;
    bool isInsertDup = bst.Insert(8);
    std::cout << "尝试插入已存在的 8, 返回值预期为 0 (false), 实际为: " << isInsertDup << std::endl;

    std::cout << "\n=== 3. 测试查找逻辑 ===" << std::endl;
    std::cout << "查找存在的元素 6, 预期 1, 实际: " << bst.Find(6) << std::endl;
    std::cout << "查找不存在的元素 100, 预期 0, 实际: " << bst.Find(100) << std::endl;

    std::cout << "\n=== 4. 测试删除逻辑 (核心边界覆盖) ===" << std::endl;

    // 测试情况1：删除叶子节点
    std::cout << "[删除叶子节点] 删除 4: " << std::endl;
    bst.Erase(4);
    bst.InOrder(); // 预期: 1 3 6 7 8 10 13 14

    // 测试情况2/3：删除只有一个孩子的节点
    std::cout << "[删除单孩子节点] 删除 14 (只有左孩子13): " << std::endl;
    bst.Erase(14);
    bst.InOrder(); // 预期: 1 3 6 7 8 10 13

    // 测试情况4：删除有两个孩子的节点
    std::cout << "[删除双孩子节点(替换法)] 删除 3 (左右都有孩子): " << std::endl;
    bst.Erase(3);
    bst.InOrder(); // 预期: 1 6 7 8 10 13

    // 极端情况测试：删除根节点
    std::cout << "[删除根节点] 删除 8 (原树的根): " << std::endl;
    bst.Erase(8);
    bst.InOrder(); // 预期: 1 6 7 10 13

    // 扫尾测试：删除所有剩余节点
    std::cout << "\n=== 5. 清空树测试 ===" << std::endl;
    std::vector<int> remain = { 1, 6, 7, 10, 13 };
    for (int e : remain) {
        bst.Erase(e);
    }
    std::cout << "全部删除后遍历树 (预期无输出): ";
    bst.InOrder();
    std::cout << "清空后查找 10: " << bst.Find(10) << " (预期为 0)" << std::endl;
}

int main() {
    TestBSTree();
    return 0;
}