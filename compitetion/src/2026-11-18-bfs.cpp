#include <iostream>
#include <queue>
#include <vector>

int main() {
    int vertex_count = 0;
    int edge_count = 0;
    std::cin >> vertex_count >> edge_count;

    std::vector<std::vector<int>> graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int from = 0;
        int to = 0;
        std::cin >> from >> to;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    std::vector<bool> visited(vertex_count, false);
    std::queue<int> pending;
    pending.push(0);
    visited[0] = true;

    while (!pending.empty()) {
        const int current = pending.front();
        pending.pop();
        std::cout << current << ' ';
        for (const int next : graph[current]) {
            if (!visited[next]) {
                visited[next] = true;
                pending.push(next);
            }
        }
    }
    std::cout << '\n';
    return 0;
}
