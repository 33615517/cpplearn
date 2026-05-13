#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <ctime>

void Benchmark() {
    const size_t N = 1000000; // 测试数据量：100万
    std::vector<int> v;

    // 提前为 vector 预留空间，避免 push_back 过程中不断开辟新内存带来额外的时间开销
    v.reserve(N);
    srand(time(0));

    // 构造测试数据
    // 使用 rand() + i 可以一定程度上减少海量重复值的产生，模拟更接近真实的散列分布场景
    for (size_t i = 0; i < N; ++i) {
        v.push_back(rand() + i);
    }

    std::set<int> s;
    std::unordered_set<int> us;

    std::cout << "================ 性能压测开始 (数据量: " << N << ") ================\n";

    // --- 1. 插入 (Insert) 性能测试 ---
    size_t b1 = clock();
    for (auto e : v) {
        s.insert(e); // 红黑树插入，单次时间复杂度 O(logN)
    }
    size_t e1 = clock();

    size_t b2 = clock();
    // 【性能优化的核心考点】
    // 哈希表在元素增多时会触发扩容(Rehash)，极其耗时。
    // 如果已知数据规模，提前 reserve 预留好哈希桶的空间，能大幅提升插入性能！
    us.reserve(N);
    for (auto e : v) {
        us.insert(e); // 哈希表插入，单次平均时间复杂度 O(1)
    }
    size_t e2 = clock();

    std::cout << "[插入测试]\n";
    std::cout << "  -> 红黑树 (set)           耗时: " << e1 - b1 << " ms\n";
    std::cout << "  -> 哈希表 (unordered_set) 耗时: " << e2 - b2 << " ms\n";
    std::cout << "--------------------------------------------------------\n";

    // --- 2. 查找 (Find) 性能测试 ---
    size_t b3 = clock();
    for (auto e : v) {
        s.find(e); // 红黑树查找，单次时间复杂度 O(logN)
    }
    size_t e3 = clock();

    size_t b4 = clock();
    for (auto e : v) {
        us.find(e); // 哈希表查找，单次平均时间复杂度 O(1)
    }
    size_t e4 = clock();

    std::cout << "[查找测试]\n";
    std::cout << "  -> 红黑树 (set)           耗时: " << e3 - b3 << " ms\n";
    std::cout << "  -> 哈希表 (unordered_set) 耗时: " << e4 - b4 << " ms\n";
    std::cout << "========================================================\n";
}
int main()
{
    Benchmark();
	return 0;
}
