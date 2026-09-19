/**
 * @file main.cpp
 * @brief Лабораторная работа: Реализация и анализ алгоритмов сортировки.
 * 
 * В файле представлены 3 алгоритма сортировки:
 * 1. Сортировка слиянием (Merge Sort).
 * 2. Быстрая сортировка (Quick Sort).
 * 3. Сортировка подсчётом (Counting Sort).
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <string>

// ============================================================================
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// ============================================================================

/**
 * @brief Выводит элементы массива в консоль.
 * @param arr Указатель на массив.
 * @param size Размер массива.
 */
void print_array(const int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << (i == size - 1 ? "" : " ");
    }
    std::cout << "\n";
}

// ============================================================================
// 1. СОРТИРОВКА СЛИЯНИЕМ (MERGE SORT)
// ============================================================================

/**
 * @brief Вспомогательная функция для слияния двух отсортированных подмассивов.
 */
void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

/**
 * @brief Рекурсивная реализация сортировки слиянием.
 */
void merge_sort_recursive(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_recursive(arr, left, mid);
        merge_sort_recursive(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/**
 * @brief Сортировка массива методом слияния.
 * 
 * @param arr Указатель на массив.
 * @param size Размер массива.
 * 
 * @note Сложность по времени:  O(n log n) - во всех случаях.
 * @note Сложность по памяти:  O(n) - дополнительный буфер под элементы.
 */
void merge_sort(int* arr, int size) {
    if (arr == nullptr || size <= 1) return;
    merge_sort_recursive(arr, 0, size - 1);
}

// ============================================================================
// 2. БЫСТРАЯ СОРТИРОВКА (QUICK SORT)
// ============================================================================

/**
 * @brief Вспомогательная функция разделения (Lomuto partition scheme).
 */
int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

/**
 * @brief Рекурсивная реализация быстрой сортировки.
 */
void quick_sort_recursive(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_recursive(arr, low, pi - 1);
        quick_sort_recursive(arr, pi + 1, high);
    }
}

/**
 * @brief Сортировка массива методом «быстрая сортировка».
 * 
 * @param arr Указатель на массив.
 * @param size Размер массива.
 * 
 * @note Сложность по времени:  O(n log n) в среднем, O(n^2) в худшем.
 * @note Сложность по памяти:  O(log n) - стек рекурсии.
 */
void quick_sort(int* arr, int size) {
    if (arr == nullptr || size <= 1) return;
    quick_sort_recursive(arr, 0, size - 1);
}

// ============================================================================
// 3. СОРТИРОВКА ПОДСЧЁТОМ (COUNTING SORT)
// ============================================================================

/**
 * @brief Сортировка массива методом «сортировка подсчётом».
 * 
 * @details Рассчитана на диапазон значений от 10 до 24.
 * 
 * @param arr Указатель на массив.
 * @param size Размер массива.
 * 
 * @note Сложность по времени:  O(n + K), где K — диапазон значений.
 * @note Сложность по памяти:  O(K) — вспомогательный массив частот.
 */
void count_sort(int* arr, int size) {
    if (arr == nullptr || size <= 1) return;

    constexpr int MIN_VAL = 10;
    constexpr int MAX_VAL = 24;
    constexpr int RANGE = MAX_VAL - MIN_VAL + 1;

    std::vector<int> count(RANGE, 0);

    for (int i = 0; i < size; ++i) {
        count[arr[i] - MIN_VAL]++;
    }

    int index = 0;
    for (int i = 0; i < RANGE; ++i) {
        while (count[i] > 0) {
            arr[index++] = i + MIN_VAL;
            count[i]--;
        }
    }
}

// ============================================================================
// 4. ТЕСТИРОВАНИЕ И БЕНЧМАРКИ
// ============================================================================

/**
 * @brief Обертка для проведения тестов, замера времени и вывода результатов.
 */
template <typename SortFunc>
void run_test(const std::string& title, const std::vector<int>& input_data, SortFunc sort_fn) {
    std::vector<int> buffer = input_data;
    
    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << "Тест: " << title << " (Размер: " << buffer.size() << " элементов)\n";
    std::cout << "Исходный массив:      ";
    print_array(buffer.data(), static_cast<int>(buffer.size()));

    auto start = std::chrono::high_resolution_clock::now();
    sort_fn(buffer.data(), static_cast<int>(buffer.size()));
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::nano> elapsed_ns = end - start;

    std::cout << "Отсортированный массив: ";
    print_array(buffer.data(), static_cast<int>(buffer.size()));
    std::cout << "Время выполнения:       " << std::fixed << std::setprecision(2) << elapsed_ns.count() << " нс\n";
}

int main() {
    std::cout << "========================================================================================\n";
    std::cout << "                         СРАВНИТЕЛЬНЫЙ АНАЛИЗ СОРТИРОВОК                                \n";
    std::cout << "========================================================================================\n\n";

    // Наборы данных для Задач 1 и 2
    const std::vector<std::vector<int>> general_datasets = {
        {3, 43, 38, 29, 18, 72, 57, 61, 2, 33},
        {88, 91, 87, 59, 53, 49, 29, 16, 4, 27, 28, 89, 2, 25, 74},
        {24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62}
    };

    // Наборы данных для Задачи 3 (диапазон 10-24)
    const std::vector<std::vector<int>> count_datasets = {
        {19, 14, 22, 22, 17, 22, 13, 21, 20, 24, 18, 10, 17, 16, 17, 20, 22, 11, 20, 16, 14, 13, 10, 22, 18, 14, 16, 24, 19, 17},
        {16, 17, 14, 20, 22, 20, 17, 22, 16, 19, 23, 24, 20, 22, 21, 18, 14, 16, 17, 21, 10, 11, 19, 23, 11, 11, 17, 17, 11, 21, 17, 11, 17, 16, 12, 11, 16, 22, 23, 16},
        {21, 15, 19, 18, 23, 12, 18, 18, 19, 23, 12, 20, 15, 22, 21, 18, 19, 20, 12, 16, 20, 14, 17, 13, 10, 23, 19, 14, 10, 22, 19, 12, 24, 23, 22, 15, 13, 22, 18, 18, 11, 23, 24, 17, 10}
    };

    // --- ЗАДАЧА 1 ---
    std::cout << "========================================================================================\n";
    std::cout << "ЗАДАЧА 1. СОРТИРОВКА СЛИЯНИЕМ (MERGE SORT)\n";
    std::cout << "========================================================================================\n";
    for (size_t i = 0; i < general_datasets.size(); ++i) {
        run_test("Merge Sort #" + std::to_string(i + 1), general_datasets[i], merge_sort);
    }

    // --- ЗАДАЧА 2 ---
    std::cout << "\n========================================================================================\n";
    std::cout << "ЗАДАЧА 2. БЫСТРАЯ СОРТИРОВКА (QUICK SORT)\n";
    std::cout << "========================================================================================\n";
    for (size_t i = 0; i < general_datasets.size(); ++i) {
        run_test("Quick Sort #" + std::to_string(i + 1), general_datasets[i], quick_sort);
    }

    // --- ЗАДАЧА 3 ---
    std::cout << "\n========================================================================================\n";
    std::cout << "ЗАДАЧА 3. СОРТИРОВКА ПОДСЧЁТОМ (COUNTING SORT)\n";
    std::cout << "========================================================================================\n";
    for (size_t i = 0; i < count_datasets.size(); ++i) {
        run_test("Count Sort #" + std::to_string(i + 1), count_datasets[i], count_sort);
    }

    std::cout << "\n========================================================================================\n";
    std::cout << "Сводка по алгоритмической сложности (Big O):\n";
    std::cout << " 1. Merge Sort:  Время: O(n log n), Память: O(n)\n";
    std::cout << " 2. Quick Sort:  Время: O(n log n), Память: O(log n)\n";
    std::cout << " 3. Count Sort:  Время: O(n + K),   Память: O(K) (где K — размер диапазона values)\n";
    std::cout << "========================================================================================\n";

    return 0;
}