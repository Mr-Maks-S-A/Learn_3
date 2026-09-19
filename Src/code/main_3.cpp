/**
 * @file main_3.cpp
 * @brief Домашнее задание: Динамический массив. Списки. Деки.
 * 
 * Задача 3*. Удаление первого элемента из изменяемого динамического массива.
 */

#include <iostream>
#include <string>
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

    // Интерактивный цикл удаления элементов
    while (true) {
        std::string answer = get_input<std::string>("Удалить первый элемент? ");

        if (answer == "да") {
            if (logical_size == 0) {
                std::cout << "Невозможно удалить первый элемент, так как массив пустой. До свидания!\n";
                break;
            }

            remove_dynamic_array_head(arr, logical_size, actual_size);

            std::cout << "Динамический массив: ";
            print_dynamic_array(arr, logical_size, actual_size);
        } 
        else if (answer == "нет") {
            std::cout << "Спасибо! Ваш динамический массив: ";
            print_dynamic_array(arr, logical_size, actual_size);
            break;
        }
    }

    // Освобождение памяти
    delete[] arr;
    return 0;
}