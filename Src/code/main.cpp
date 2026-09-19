/**
 * @file main.cpp
 * @brief Лабораторная/домашняя работа: Оптимизация вычисления чисел Фибоначчи и анализ сложности.
 * 
 * В данном файле представлены 3 подхода к вычислению чисел Фибоначчи:
 * 1. Наивная рекурсия (Baseline).
 * 2. Динамическое программирование / Мемоизация в Runtime (Динамическая память).
 * 3. Таблица предвычислений на этапе компиляции (constexpr / Статическая память).
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <array>
#include <iomanip>
#include <cstdint>
#include <string>

// ============================================================================
// 1. НАИВНЫЙ РЕКУРСИВНЫЙ ПОДХОД
// ============================================================================

/**
 * @brief Вычисляет n-е число Фибоначчи наивным рекурсивным методом.
 * 
 * @details Каждый вызов генерирует два новых рекурсивных вызова, образуя бинарное
 * дерево вызовов. Это приводит к многократному перевычислению одних и тех же значений.
 * 
 * @param n Индекс числа Фибоначчи (0-based).
 * @return std::uint64_t n-е число Фибоначчи.
 * 
 * @note Сложность по времени:  O(2^n) - экспоненциальная.
 * @note Сложность по памяти:  O(n)   - глубина стека вызовов.
 */
std::uint64_t fibonacci_naive(unsigned int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

// ============================================================================
// 2. ДИНАМИЧЕСКОЕ ПРОГРАММИРОВАНИЕ (МЕМОИЗАЦИЯ В RUNTIME)
// ============================================================================

/**
 * @brief Класс для вычисления чисел Фибоначчи с динамическим кешированием в Runtime.
 * 
 * @details Использует концепцию нисходящего динамического программирования (Memoization).
 * Память под кэш выделяется динамически с помощью std::vector по мере необходимости.
 * 
 * @note Сложность по времени:  O(n) - линейная (каждое подзначение считается 1 раз).
 * @note Сложность по памяти:  O(n) - вектор в куче для хранения результатов.
 */
class DynamicFibonacci {
private:
    /// Кэш ранее computed значений. Значение 0 означает, что число еще не вычислено.
    std::vector<std::uint64_t> cache;

    /**
     * @brief Внутренняя рекурсивная функция для вычисления с использованием кэша.
     * @param n Индекс числа.
     * @return std::uint64_t Значение числа Фибоначчи.
     */
    std::uint64_t compute(unsigned int n) {
        if (n <= 1) return n;
        if (cache[n] != 0) return cache[n];
        
        cache[n] = compute(n - 1) + compute(n - 2);
        return cache[n];
    }

public:
    /**
     * @brief Основной метод расчета числа Фибоначчи.
     * @param n Индекс числа.
     * @return std::uint64_t Значение числа Фибоначчи.
     */
    std::uint64_t calculate(unsigned int n) {
        if (n <= 1) return n;
        if (cache.size() <= n) {
            cache.resize(n + 1, 0);
        }
        return compute(n);
    }
    
    /**
     * @brief Очищает кэш вычисленных значений.
     */
    void clear() {
        cache.clear();
    }
};

// ============================================================================
// 3. CONSTEXPR ПРЕДВЫЧИСЛЕНИЕ (COMPILE-TIME / СТАЦИОНАРНАЯ ПАМЯТЬ)
// ============================================================================

/**
 * @brief Структура для генерации таблицы чисел Фибоначчи во время компиляции.
 * 
 * @tparam N Количество элементов в таблице.
 */
template <std::size_t N>
struct ConstexprFibTable {
    /// Массив значений, вычисляемый на этапе компиляции.
    std::array<std::uint64_t, N> values{};

    /**
     * @brief Конструктор, выполняющий расчеты во время компиляции (constexpr).
     */
    constexpr ConstexprFibTable() {
        if constexpr (N > 0) values[0] = 0;
        if constexpr (N > 1) values[1] = 1;
        for (std::size_t i = 2; i < N; ++i) {
            values[i] = values[i - 1] + values[i - 2];
        }
    }
};

/**
 * @brief Статическая таблица предвычисленных значений Фибоначчи.
 * @details Максимальное 64-битное число Фибоначчи умещается в uint64_t при n = 93.
 */
constexpr auto FIB_LOOKUP_TABLE = ConstexprFibTable<94>();

/**
 * @brief Вычисляет (достает из таблицы) n-е число Фибоначчи за O(1).
 * 
 * @param n Индекс числа.
 * @return constexpr std::uint64_t Значение из предвычисленной таблицы (или 0 при переполнении).
 * 
 * @note Сложность по времени:  O(1) - прямое обращение к массиву в памяти.
 * @note Сложность по памяти:  O(1) runtime (статическая память размером N элементов зашита в бинарник).
 */
constexpr std::uint64_t fibonacci_constexpr(unsigned int n) {
    if (n >= 94) {
        return 0; // Защита от переполнения uint64_t
    }
    return FIB_LOOKUP_TABLE.values[n];
}

// ============================================================================
// 4. БЕНЧМАРК И ТЕСТИРОВАНИЕ
// ============================================================================

/**
 * @brief Функция-бенчмарк для замеров времени выполнения алгоритма.
 * 
 * @tparam Func Тип передаваемого callable-объекта (функция, лямбда).
 * @param label Название метода для вывода в консоль.
 * @param func Вызываемая функция.
 * @param n Индекс вычисляемого числа Фибоначчи.
 */
template <typename Func>
void benchmark(const std::string& label, Func func, unsigned int n) {
    auto start = std::chrono::high_resolution_clock::now();
    std::uint64_t result = func(n);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::nano> elapsed_ns = end - start;
    
    std::cout << std::left  << std::setw(34) << label 
              << " | Fib(" << std::setw(2) << n << ") = " 
              << std::setw(20) << result 
              << " | Время: " << std::fixed << std::setprecision(3) 
              << std::right << std::setw(10) << elapsed_ns.count() << " нс\n";
}

/**
 * @brief Точка входа в программу. Выполнение тестов и сравнение производительности.
 */
int main() {
    std::cout << "========================================================================================\n";
    std::cout << "           СРАВНЕНИЕ ПРОИЗВОДИТЕЛЬНОСТИ АЛГОРИТМОВ ФИБОНАЧЧИ                     \n";
    std::cout << "========================================================================================\n\n";


    // 3 разных числа для проверки тенденций: малое, среднее, большое
    std::array<unsigned int, 3> test_values = {10, 25, 40};

    std::cout << "--- 1. Базовый рекурсивный вариант (Naive Recursion) O(2^n) ---\n";
    for (unsigned int n : test_values) {
        benchmark("Наивная рекурсия", [](unsigned int n) { return fibonacci_naive(n); }, n);
    }

    std::cout << "\n--- 2. Динамическое программирование (Runtime Cache) O(n) ---\n";
    for (unsigned int n : test_values) {
        DynamicFibonacci dp_solver; // Создаем новый объект для каждого числа (чистый кэш)
        
        // Первый проход - заполнение кэша (Cold Cache)
        benchmark("DP (Первый запуск)          ", [&dp_solver](unsigned int n) { return dp_solver.calculate(n); }, n);
        
        // Второй проход - чтение из кэша (Hot Cache)
        benchmark("DP (Из кэша)", [&dp_solver](unsigned int n) { return dp_solver.calculate(n); }, n);
        std::cout << "-\n";
    }

    std::cout << "\n--- 3. Constexpr Вычисления на этапе компиляции O(1) ---\n";
    for (unsigned int n : test_values) {
        benchmark("Constexpr Таблица", [](unsigned int n) { return fibonacci_constexpr(n); }, n);
    }

    std::cout << "\n========================================================================================\n";
    std::cout << "Сводка по алгоритмической сложности (Big O):\n";
    std::cout << " 1. Наивный подход:  Время: O(2^n),  Память: O(n) (стек вызовов)\n";
    std::cout << " 2. DP (Runtime):    Время: O(n),    Память: O(n) (динамический вектор)\n";
    std::cout << " 3. Constexpr (CT):  Время: O(1),    Память: O(1) в Runtime (статический массив)\n";
    std::cout << "========================================================================================\n";

    return 0;
}