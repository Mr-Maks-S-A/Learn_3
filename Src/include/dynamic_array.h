#pragma once

#include <iostream>
#include <string>
#include <Until/Input.hpp>

// ============================================================================
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ И ВЫВОД
// ============================================================================

/**
 * @brief Выводит элементы динамического массива на консоль.
 * 
 * @details Выводит элементы в пределах logical_size как значения, 
 *          а неиспользуемый запас (до actual_size) заменяет символом '_'.
 * 
 * @param arr Указатель на динамический массив.
 * @param logical_size Количество фактически записанных элементов.
 * @param actual_size Выделенный размер памяти под массив.
 */
inline void print_dynamic_array(const int* arr, int logical_size, int actual_size) {
    for (int i = 0; i < actual_size; ++i) {
        if (i < logical_size) {
            std::cout << arr[i];
        } else {
            std::cout << "_";
        }

        if (i < actual_size - 1) {
            std::cout << " ";
        }
    }
    std::cout << "\n";
}

/**
 * @brief Осуществляет ввод параметров и элементов динамического массива с консоли.
 * 
 * @param[out] arr Ссылка на указатель для создаваемого массива.
 * @param[out] logical_size Ссылка на переменную логического размера.
 * @param[out] actual_size Ссылка на переменную фактического размера.
 * 
 * @return true, если ввод успешен и размеры валидны;
 *         false, если логический размер превышает фактический.
 */
inline bool input_dynamic_array(int*& arr, int& logical_size, int& actual_size) {
    actual_size = get_input<int>("Введите фактичеcкий размер массива: ", 1);
    logical_size = get_input<int>("Введите логический размер массива: ", 0);

    if (logical_size > actual_size) {
        std::cout << "Ошибка! Логический размер массива не может превышать фактический!\n";
        return false;
    }

    arr = new int[actual_size];

    for (int i = 0; i < logical_size; ++i) {
        std::string prompt = "Введите arr[" + std::to_string(i) + "]: ";
        arr[i] = get_input<int>(prompt);
    }

    return true;
}

// ============================================================================
// 2. МОДИФИКАЦИЯ МАССИВА (ДОБАВЛЕНИЕ)
// ============================================================================

/**
 * @brief Добавляет новый элемент в конец динамического массива.
 * 
 * @details Если logical_size < actual_size, элемент помещается в имеющийся запас.
 *          Если logical_size == actual_size, выделяется новый массив удвоенного
 *          размера, данные копируются, старый массив удаляется.
 * 
 * @param[in,out] arr Ссылка на указатель динамического массива.
 * @param[in,out] logical_size Ссылка на логический размер массива.
 * @param[in,out] actual_size Ссылка на фактический размер массива.
 * @param[in] value Значение для добавления.
 * 
 * @return Указатель на актуальный (возможно, перевыделенный) массив.
 */
inline int* append_to_dynamic_array(int*& arr, int& logical_size, int& actual_size, int value) {
    if (logical_size < actual_size) {
        arr[logical_size] = value;
        logical_size++;
    } else {
        actual_size = (actual_size == 0) ? 1 : actual_size * 2;
        int* new_arr = new int[actual_size];

        for (int i = 0; i < logical_size; ++i) {
            new_arr[i] = arr[i];
        }

        new_arr[logical_size] = value;
        logical_size++;

        delete[] arr;
        arr = new_arr;
    }
    return arr;
}


// ============================================================================
// 3. МОДИФИКАЦИЯ МАССИВА (УДАЛЕНИЕ)
// ============================================================================

/**
 * @brief Удаляет первый элемент из динамического массива.
 * 
 * @details Если (logical_size - 1) > actual_size / 3, сдвигает элементы влево.
 *          Иначе перевыделяет массив с уменьшением фактического размера в 3 раза.
 * 
 * @param[in,out] arr Ссылка на указатель динамического массива.
 * @param[in,out] logical_size Ссылка на логический размер массива.
 * @param[in,out] actual_size Ссылка на фактический размер массива.
 * 
 * @return Указатель на актуальный массив.
 */
inline int* remove_dynamic_array_head(int*& arr, int& logical_size, int& actual_size) {
    if (logical_size <= 0) {
        return arr;
    }

    if (logical_size - 1 > actual_size / 3) {
        for (int i = 0; i < logical_size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        logical_size--;
    } else {
        actual_size /= 3;
        if (actual_size < 1) actual_size = 1;

        int* new_arr = new int[actual_size];
        for (int i = 0; i < logical_size - 1; ++i) {
            new_arr[i] = arr[i + 1];
        }

        logical_size--;
        delete[] arr;
        arr = new_arr;
    }

    return arr;
}