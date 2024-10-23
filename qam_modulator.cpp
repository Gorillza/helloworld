#include "qam_modulator.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
QAMModulator::QAMModulator(int M) : M(M) {
    // Проверка, что M — степень двойки
    if (M != 16 && M != 64) {
        throw std::invalid_argument("This implementation supports only 16-QAM and 64-QAM.");
    }
    dimension = static_cast<int>(std::sqrt(M));  // Количество уровней по каждой оси (4 для 16-QAM, 8 для 64-QAM)
    generateTable();  // Генерируем созвездие
    normalizeConstellation();  // Нормализуем созвездие по средней мощности
}

void QAMModulator::generateTable() {
    // Генерация квадратного созвездия для M-QAM
    Table.clear();

    // Амплитуды точек созвездия (центруем точки вокруг нуля)
    double stepSize = 2.0;
    double minValue = -(dimension - 1);  // Минимальное значение по оси

    for (int j = 0; j < dimension; ++j) {  // По оси Y (мнимая часть)
        for (int i = 0; i < dimension; ++i) {  // По оси X (реальная часть)
            double realPart = minValue + i * stepSize;
            double imagPart = minValue + j * stepSize;
            Table.push_back({realPart, imagPart});
        }
    }
}

void QAMModulator::normalizeConstellation() {
    // Рассчитываем среднюю мощность созвездия
    double avgPower = 0.0;
    for (const auto& point : Table) {
        avgPower += std::norm(point);  // Мощность точки — это квадрат амплитуды (реальная + мнимая часть)
    }
    avgPower /= Table.size();  // Усредняем по количеству точек

    // Нормализуем созвездие, деля каждую точку на квадратный корень из средней мощности
    double normalizationFactor = std::sqrt(avgPower);
    for (auto& point : Table) {
        point /= normalizationFactor;  // Нормализуем символы
    }
}

std::vector<std::complex<double>> QAMModulator::modulate(const std::vector<int> inputBits) {
    std::vector<std::complex<double>> modulatedSignal;

    // Вычисляем количество битов на символ
    int bitsPerSymbol = static_cast<int>(std::log2(M));

    // Модуляция битовых данных
    for (size_t i = 0; i < inputBits.size(); i += bitsPerSymbol) {
        int symbolIndex = 0;

        // Переводим биты в индекс, сохраняя прямой порядок
        for (int b = 0; b < bitsPerSymbol; ++b) {
            symbolIndex |= (inputBits[i + b] << (bitsPerSymbol - 1 - b));  // Инверсия порядка битов
        }

        modulatedSignal.push_back(Table[symbolIndex]);
    }

    return modulatedSignal;
}
