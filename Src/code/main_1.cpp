/**
 * @file main_1.cpp
 * @brief Домашнее задание: Динамический массив. Списки. Деки.
 * 
 * Задача 1. Вывод изменяемого динамического массива.
 */

#include <iostream>
#include <dynamic_array.h>

// ============================================================================
// ГЛАВНАЯ ФУНКЦИЯ
// ============================================================================

int main() {
    int* arr = nullptr;
    int actual_size = 0;
    int logical_size = 0;

    // Ввод массива с валидацией размеров
    if (!input_dynamic_array(arr, logical_size, actual_size)) {
        return 0;
    }

    // Вывод массива согласно формату
    std::cout << "Динамический массив: ";
    print_dynamic_array(arr, logical_size, actual_size);

    // Освобождение памяти
    delete[] arr;
    return 0;
}