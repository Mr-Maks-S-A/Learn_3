/**
 * @file main_2.cpp
 * @brief Домашнее задание: Динамический массив. Списки. Деки.
 * 
 * Задача 2. Добавление в изменяемый динамический массив.
 */

#include <iostream>
#include "dynamic_array.h"

// ============================================================================
// ГЛАВНАЯ ФУНКЦИЯ
// ============================================================================

int main() {
    int* arr = nullptr;
    int actual_size = 0;
    int logical_size = 0;

    // Ввод исходного состояния массива
    if (!input_dynamic_array(arr, logical_size, actual_size)) {
        return 0;
    }

    std::cout << "Динамический массив: ";
    print_dynamic_array(arr, logical_size, actual_size);

    // Интерактивный цикл добавления элементов
    while (true) {
        int value = get_input<int>("Введите элемент для добавления: ");

        if (value == 0) {
            std::cout << "Спасибо! Ваш массив: ";
            print_dynamic_array(arr, logical_size, actual_size);
            break;
        }

        append_to_dynamic_array(arr, logical_size, actual_size, value);

        std::cout << "Динамический массив: ";
        print_dynamic_array(arr, logical_size, actual_size);
    }

    // Освобождение памяти
    delete[] arr;
    return 0;
}