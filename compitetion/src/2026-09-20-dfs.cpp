#include <iostream>
#include <vector>

void depth_first_search(
    int current,
    const std::vector<std::vector<int>>& graph,
    std::vector<bool>& visited
) {
    visited[current] = true;
    std::cout << current << ' ';
    for (const int next : graph[current]) {
        if (!visited[next]) {
            depth_first_search(next, graph, visited);
        }
    }
}

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
    if (vertex_count > 0) {
        depth_first_search(0, graph, visited);
    }
    std::cout << '\n';
    return 0;
}
