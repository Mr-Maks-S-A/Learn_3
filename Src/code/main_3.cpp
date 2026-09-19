/**
 * @file main_3.cpp
 * @brief Домашнее задание: Графы (Задание 3*. Поиск циклов).
 * 
 * В файле представлены:
 * 1. Чтение матрицы смежности из нескольких файлов (input.txt и input_2.txt).
 * 2. Рекурсивный алгоритм поиска циклов в неориентированном графе с помощью DFS.
 * 3. Автоматическое освобождение динамической памяти.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <Until/Input.hpp>

// ============================================================================
// 1. Вспомогательные функции для памяти
// ============================================================================

/**
 * @brief Освобождает динамическую память, выделенную под матрицу смежности.
 */
void free_matrix(int** matrix, int rows) {
    if (matrix == nullptr) return;
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// ============================================================================
// 2. АЛГОРИТМ ПОИСКА ЦИКЛОВ (DFS)
// ============================================================================

/**
 * @brief Рекурсивный поиск цикла в графе через DFS.
 */
bool has_cycle_dfs(int current_vertex, int parent_vertex, int** matrix, bool* visited, int vertices_count) {
    visited[current_vertex] = true;

    for (int next_vertex = 0; next_vertex < vertices_count; ++next_vertex) {
        if (matrix[current_vertex][next_vertex] == 1) {
            if (!visited[next_vertex]) {
                if (has_cycle_dfs(next_vertex, current_vertex, matrix, visited, vertices_count)) {
                    return true;
                }
            } 
            else if (next_vertex != parent_vertex) {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Проверяет наличие хотя бы одного цикла во всём графе.
 */
bool contains_cycle(int** matrix, int vertices_count) {
    bool* visited = new bool[vertices_count]{false};

    for (int i = 0; i < vertices_count; ++i) {
        if (!visited[i]) {
            if (has_cycle_dfs(i, -1, matrix, visited, vertices_count)) {
                delete[] visited;
                return true;
            }
        }
    }

    delete[] visited;
    return false;
}

// ============================================================================
// 3. ФУНКЦИЯ ОБРАБОТКИ ФАЙЛА
// ============================================================================

/**
 * @brief Читает граф из файла и выполняет проверку на циклы.
 */
void process_graph_file(const std::string& filepath) {
    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << "Анализ файла: " << filepath << "\n";

    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filepath << "\n\n";
        return;
    }

    int N = 0;
    if (!(file >> N) || N <= 0) {
        std::cerr << "Ошибка: некорректный формат файла или N <= 0.\n\n";
        file.close();
        return;
    }

    // Выделение динамической памяти под матрицу
    int** matrix = new int*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N];
    }

    // Считывание матрицы
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            file >> matrix[i][j];
        }
    }

    file.close();

    // Проверка на циклы и вывод результата
    if (contains_cycle(matrix, N)) {
        std::cout << "Результат: В графе есть цикл!\n";
    } else {
        std::cout << "Результат: В графе нет циклов\n";
    }

    // Освобождение памяти
    free_matrix(matrix, N);
    std::cout << "\n";
}

// ============================================================================
// 4. MAIN
// ============================================================================

int main() {
    std::cout << "========================================================================================\n";
    std::cout << "                   ДОМАШНЕЕ ЗАДАНИЕ: ГРАФЫ (ЗАДАНИЕ 3*. ПОИСК ЦИКЛОВ)                   \n";
    std::cout << "========================================================================================\n\n";

    // Список файлов для тестирования
    std::vector<std::string> test_files = {
        "Source/input.txt",
        "Source/input_2.txt"
    };

    for (const auto& filepath : test_files) {
        process_graph_file(filepath);
    }

    std::cout << "========================================================================================\n";
    std::cout << "Работа программы завершена.\n";
    std::cout << "========================================================================================\n";

    return 0;
}