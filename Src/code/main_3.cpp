/**
 * @file main.cpp
 * @brief Домашнее задание: Хеширование (Задание 3).
 * 
 * В файле представлены:
 * 1. Реализация упрощённого алгоритма Рабина-Карпа (find_substring_light_rabin_karp).
 * 2. Поиск подстрок в интерактивном цикле до ввода команды "exit".
 */

#include <iostream>
#include <string>
#include <cstdint>

#include <Until/Input.hpp>

// ============================================================================
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// ============================================================================

/**
 * @brief Вычисляет полиномиальный хэш строки.
 */
int real_string_hash(const std::string& s, long long p = 31, long long n = 1'000'000'007) {
    unsigned long long hash = 0;
    unsigned long long p_pow = 1;

    for (char ch : s) {
        unsigned long long char_code = static_cast<unsigned char>(ch);
        hash = (hash + (char_code % n) * p_pow) % n;
        p_pow = (p_pow * (p % n)) % n;
    }

    return static_cast<int>(hash);
}

// ============================================================================
// 1. ЗАДАНИЕ 3. УПРОЩЁННЫЙ АЛГОРИТМ РАБИНА-КАРПА
// ============================================================================

/**
 * @brief Находит индекс первого вхождения подстроки в строке по алгоритму Рабина-Карпа.
 * 
 * @param source Исходная строка, в которой выполняется поиск.
 * @param substring Искомая подстрока.
 * @return int Индекс первого вхождения подстроки или -1, если совпадение не найдено.
 */
int find_substring_light_rabin_karp(const std::string& source, const std::string& substring) {
    size_t source_len = source.length();
    size_t sub_len = substring.length();

    if (sub_len > source_len || sub_len == 0) {
        return -1;
    }

    int sub_hash = real_string_hash(substring);
    int current_hash = real_string_hash(source.substr(0, sub_len));

    for (size_t i = 0; i <= source_len - sub_len; ++i) {
        // Проверяем совпадение хэшей
        if (current_hash == sub_hash) {
            // При совпадении хэшей выполняем посимвольную проверку (коллизии)
            if (source.substr(i, sub_len) == substring) {
                return static_cast<int>(i);
            }
        }

        // Пересчитываем хэш для следующего окна длины sub_len
        if (i < source_len - sub_len) {
            current_hash = real_string_hash(source.substr(i + 1, sub_len));
        }
    }

    return -1;
}

// ============================================================================
// 2. ТЕСТИРОВАНИЕ И MAIN
// ============================================================================

int main() {
    std::cout << "========================================================================================\n";
    std::cout << "                   ДОМАШНЕЕ ЗАДАНИЕ: ХЕШИРОВАНИЕ (ЗАДАНИЕ 3)                             \n";
    std::cout << "========================================================================================\n\n";

    std::string source = get_input<std::string>("Введите строку, в которой будет осуществляться поиск: ", 1);

    std::string substring;

    do {
        substring = get_input<std::string>("Введите подстроку, которую нужно найти [exit => выход из программы]: ", 1);

        int index = find_substring_light_rabin_karp(source, substring);

        if (index != -1) {
            std::cout << "Подстрока " << substring << " найдена по индексу " << index << "\n";
        } else {
            std::cout << "Подстрока " << substring << " не найдена\n";
        }

    } while (substring != "exit");

    std::cout << "\n========================================================================================\n";
    std::cout << "Работа программы завершена.\n";
    std::cout << "========================================================================================\n";

    return 0;
}