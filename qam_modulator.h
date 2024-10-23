#ifndef QAM_MODULATOR_H
#define QAM_MODULATOR_H

#include <vector>
#include <complex>

class QAMModulator {
public:
    // Конструктор, который принимает количество уровней модуляции (например, 16 или 64)
    QAMModulator(int M);

    // Функция модуляции: преобразует биты в символы QAM
    std::vector<std::complex<double>> modulate(const std::vector<int> inputBits);

private:
    int M;  // Количество уровней модуляции
    int dimension;  // Количество точек по каждой оси для квадратного созвездия
    std::vector<std::complex<double>> Table;  // Созвездие QAM

    // Генерация точек созвездия для QAM
    void generateTable();

    // Нормализация созвездия по средней мощности
    void normalizeConstellation();
};

#endif // QAM_MODULATOR_H
