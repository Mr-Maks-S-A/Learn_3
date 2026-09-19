#include <iostream>
#include <fstream>
#include <string>

void free_matrix(int** matrix, int rows) {
    if (matrix == nullptr) return;
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    std::string filename = "Source/input.txt";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << "\n";
        return 1;
    }

    int N = 0;
    if (!(file >> N) || N <= 0) {
        std::cerr << "Ошибка чтения N из файла.\n";
        file.close();
        return 1;
    }

    // Выделение памяти под матрицу смежности N x N
    int** matrix = new int*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N];
    }

    // Считывание матрицы смежности
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            file >> matrix[i][j];
        }
    }
    file.close();

    std::cout << "Текстовый вид орграфа:\n";

    for (int i = 0; i < N; ++i) {
        std::cout << (i + 1) << ": ";
        bool has_neighbors = false;

        for (int j = 0; j < N; ++j) {
            if (matrix[i][j] == 1) {
                std::cout << (j + 1) << " ";
                has_neighbors = true;
            }
        }

        if (!has_neighbors) {
            std::cout << "нет";
        }
        std::cout << "\n";
    }

    free_matrix(matrix, N);
    return 0;
}