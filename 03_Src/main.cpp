#include <iostream>
#include <clocale>

#ifdef _WIN32
#include <windows.h>
#endif

void setup_locale() {
    #ifdef _WIN32
    // Для Windows задаем кодировку UTF-8 в консоли
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    #else
    // Для Linux/macOS устанавливаем системную UTF-8 локаль
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    #endif
}


// Функция возвращает количество элементов, строго больших reference_point
int count_greater(const int arr[], int size, int reference_point) {
    int left = 0;
    int right = size - 1;
    int index = size; // По умолчанию считаем, что больших элементов нет

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] > reference_point) {
            index = mid;     // Запоминаем возможный кандидат
            right = mid - 1; // Продолжаем искать левее
        } else {
            left = mid + 1;  // Идем вправу, так как arr[mid] <= reference_point
        }
    }

    return size - index;
}

int main() {
    setup_locale();
    const int SIZE = 9;
    int arr[SIZE] = {14, 16, 19, 32, 32, 32, 56, 69, 72};

    int reference_point = 0;
    std::cout << "Введите точку отсчёта: ";
    std::cin >> reference_point;

    int count = count_greater(arr, SIZE, reference_point);
    std::cout << "Количество элементов в массиве больших, чем "
    << reference_point << ": " << count << std::endl;

    return 0;
}
