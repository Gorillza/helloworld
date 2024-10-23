#include "qam_demodulator.h"
#include <cmath>
#include <stdexcept>

QAMDemodulator::QAMDemodulator(int M) : M(M) {
    // Проверка, что M — степень двойки
    if (M != 16 && M != 64) {
        throw std::invalid_argument("This implementation supports only 16-QAM and 64-QAM.");
    }
    dimension = static_cast<int>(std::sqrt(M));  // Количество уровней по каждой оси (4 для 16-QAM, 8 для 64-QAM)
    generateTable();  // Генерируем созвездие
    normalizeConstellation();  // Нормализуем созвездие по средней мощности
}

void QAMDemodulator::generateTable() {
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

void QAMDemodulator::normalizeConstellation() {
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

std::vector<int> QAMDemodulator::demodulate(const std::vector<std::complex<double>>& receivedSignal) {
    std::vector<int> demodulatedBits;

    int bitsPerSymbol = static_cast<int>(std::log2(M));

    for (const auto& symbol : receivedSignal) {
        // Найдем ближайшую точку в созвездии (Table)
        int nearestIndex = 0;
        double minDistance = std::norm(symbol - Table[0]);

        for (int i = 1; i < M; ++i) {
            double distance = std::norm(symbol - Table[i]);
            if (distance < minDistance) {
                minDistance = distance;
                nearestIndex = i;
            }
        }

        // Преобразуем индекс обратно в биты
        for (int b = bitsPerSymbol - 1; b >= 0; --b) {
            demodulatedBits.push_back((nearestIndex >> b) & 1);
        }
    }

    return demodulatedBits;
}
