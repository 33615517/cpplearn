#include <iostream>
#include <string>
#include <utility> // std::move 的头文件喵

int main() {
    // s1 是一个左值，肚子里有一块动态分配的堆内存喵
    std::string s1 = "本喵的超级无敌大鱼干！";

    // 1. ? 错误做法：直接引用左值
    // std::string&& r1 = s1; // 编译报错！编译器嘶吼：不准抢家猫！

    // 2. ? 正确做法：使用 std::move 强转为右值
    // 签发免责声明，r2 成功绑定喵！
    std::string&& r2 = std::move(s1);

    // 3. ?? 性能压榨：触发移动构造
    // 这里会直接把 r2（也就是原来 s1）底层的 char* 指针“偷”走，时间复杂度 O(1)！
    std::string s2 = std::move(r2);

    // ?? 极其危险的坑点：
    // 此时 s1 的资源已经被偷空了，变成了一个处于“有效但未指定状态”的空壳！
    // 绝对不要再去读取 s1 里面的内容喵！
    std::cout << "s2 的内容：" << s2 << "\n";
    std::cout << "r2 的内容：" << r2 << "\n";
    std::cout << "s1 的内容（已经榨干啦）：" << s1 << "\n";

    return 0;
}