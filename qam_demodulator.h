#ifndef QAM_DEMODULATOR_H
#define QAM_DEMODULATOR_H

#include <vector>
#include <complex>

class QAMDemodulator {
public:
    // Конструктор, который принимает количество уровней модуляции (например, 16 или 64)
    QAMDemodulator(int M);

    // Функция демодуляции: преобразует символы обратно в биты
    std::vector<int> demodulate(const std::vector<std::complex<double>>& receivedSignal);

private:
    int M;  // Количество уровней модуляции
    int dimension;  // Количество точек по каждой оси для квадратного созвездия
    std::vector<std::complex<double>> Table;  // Созвездие QAM

    // Генерация точек созвездия для QAM
    void generateTable();

    // Нормализация созвездия по средней мощности
    void normalizeConstellation();
};

#endif // QAM_DEMODULATOR_H
