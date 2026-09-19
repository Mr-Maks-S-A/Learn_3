/**
 * @file main_4.cpp
 * @brief Домашнее задание: Графы (Задание 4*. Поиск компонентов связности).
 * 
 * В файле представлены:
 * 1. Чтение матрицы смежности из нескольких файлов (input.txt и input_2.txt).
 * 2. Рекурсивный алгоритм выделения компонент связности через DFS.
 * 3. Форматированный вывод результатов работы алгоритма.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <Until/Input.hpp>

// ============================================================================
// 1. ВСПOМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ РАБОТЫ С ПАМЯТЬЮ
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
// 2. АЛГОРИТМ ПОИСКА КОМПОНЕНТ СВЯЗНОСТИ (DFS)
// ============================================================================

/**
 * @brief Рекурсивная функция обхода для разметки одной компоненты связности.
 * 
 * @param current_vertex Текущая рассматриваемая вершина (0-indexed).
 * @param component_id Номер текущей компоненты связности (начиная с 1).
 * @param matrix Матрица смежности.
 * @param components Массив номеров компонент для каждой вершины (0 = не посещена).
 * @param vertices_count Общее количество вершин N.
 */
void mark_component_dfs(int current_vertex, int component_id, int** matrix, int* components, int vertices_count) {
    components[current_vertex] = component_id;

    for (int next_vertex = 0; next_vertex < vertices_count; ++next_vertex) {
        // Если есть ребро и соседняя вершина ещё не имеет компонента
        if (matrix[current_vertex][next_vertex] == 1 && components[next_vertex] == 0) {
            mark_component_dfs(next_vertex, component_id, matrix, components, vertices_count);
        }
    }
}

/**
 * @brief Вычисляет компоненты связности для всего графа.
 * 
 * @param matrix Матрица смежности.
 * @param vertices_count Общее количество вершин N.
 * @param components Выходной одномерный динамический массив с номерами компонент.
 * @return int Итоговое количество компонент связности.
 */
int find_connected_components(int** matrix, int vertices_count, int* components) {
    int current_component = 0;

    for (int i = 0; i < vertices_count; ++i) {
        // Если вершина i ещё не относится ни к одной компоненте
        if (components[i] == 0) {
            ++current_component;
            mark_component_dfs(i, current_component, matrix, components, vertices_count);
        }
    }

    return current_component;
}

// ============================================================================
// 3. ФУНКЦИЯ ОБРАБОТКИ ФАЙЛА
// ============================================================================

/**
 * @brief Загружает граф из файла, находит компоненты связности и выводит результат.
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

    // Выделение памяти под матрицу смежности N x N
    int** matrix = new int*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N];
    }

    // Чтение матрицы
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            file >> matrix[i][j];
        }
    }

    file.close();

    // Динамический одномерный массив для хранения номеров компонент (0 = не посещена)
    int* components = new int[N]{0};

    int components_count = find_connected_components(matrix, N, components);

    // Вывод результатов
    std::cout << "Принадлежность вершин компонентам связности:\n";
    for (int i = 0; i < N; ++i) {
        std::cout << (i + 1) << " - " << components[i] << "\n";
    }
    std::cout << "Количество компонентов связности в графе: " << components_count << "\n";

    // Освобождение динамической памяти
    delete[] components;
    free_matrix(matrix, N);
    std::cout << "\n";
}

// ============================================================================
// 4. MAIN
// ============================================================================

int main() {
    std::cout << "========================================================================================\n";
    std::cout << "            ДОМАШНЕЕ ЗАДАНИЕ: ГРАФЫ (ЗАДАНИЕ 4*. ПОИСК КОМПОНЕНТ СВЯЗНОСТИ)            \n";
    std::cout << "========================================================================================\n\n";

    std::vector<std::string> test_files = {
        "Source/input.txt",
        "Source/input_3.txt"
    };

    for (const auto& filepath : test_files) {
        process_graph_file(filepath);
    }

    std::cout << "========================================================================================\n";
    std::cout << "Работа программы завершена.\n";
    std::cout << "========================================================================================\n";

    return 0;
}