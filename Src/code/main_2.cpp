#include <iostream>
#include <fstream>
#include <string>

// Рекурсивный обход в глубину (DFS)
void dfs(int current_vertex, int** matrix, bool* visited, int vertices_count, int* order, int& order_index) {
    visited[current_vertex] = true;

    for (int next_vertex = 0; next_vertex < vertices_count; ++next_vertex) {
        if (matrix[current_vertex][next_vertex] == 1 && !visited[next_vertex]) {
            dfs(next_vertex, matrix, visited, vertices_count, order, order_index);
        }
    }

    order[order_index++] = current_vertex;
}

void topological_sort(int** matrix, int N) {
    bool* visited = new bool[N]{false};
    int* order = new int[N];
    int order_index = 0;

    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            dfs(i, matrix, visited, N, order, order_index);
        }
    }

    std::cout << "Топологический порядок вершин: ";
    for (int i = N - 1; i >= 0; --i) {
        std::cout << (order[i] + 1);
        if (i > 0) {
            std::cout << " ";
        }
    }
    std::cout << "\n";

    delete[] visited;
    delete[] order;
}

void free_matrix(int** matrix, int rows) {
    if (matrix == nullptr) return;
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Вспомогательная функция для обработки одного файла
void process_file(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << "\n";
        return;
    }

    int N = 0;
    if (!(file >> N) || N <= 0) {
        std::cerr << "Ошибка чтения N из файла " << filename << "\n";
        file.close();
        return;
    }

    int** matrix = new int*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N];
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            file >> matrix[i][j];
        }
    }
    file.close();

    std::cout << "=== Обработка файла: " << filename << " ===\n";
    topological_sort(matrix, N);
    std::cout << "\n";

    free_matrix(matrix, N);
}

int main() {
    // Вызов функции для обоих входных файлов
    process_file("Source/input.txt");   // Пример 1 (9 вершин)
    process_file("Source/input_2.txt");  // Пример 2 (6 вершин)

    return 0;
}