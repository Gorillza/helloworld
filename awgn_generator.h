#ifndef AWGN_GENERATOR_H
#define AWGN_GENERATOR_H

#include <vector>
#include <complex>
#include <random>

class AWGNGenerator {
public:
    // Конструктор, принимающий SNR и начальное значение для генератора случайных чисел
    AWGNGenerator(double snrDb, unsigned int seed);

    // Метод добавления шума к входному сигналу
    std::vector<std::complex<double>> addNoise(const std::vector<std::complex<double>>& signal);

private:
    double snrDb;  // SNR в дБ
    std::default_random_engine generator;  // Генератор случайных чисел
    double calculateNoisePower(double signalPower);  // Расчет мощности шума
};

#endif // AWGN_GENERATOR_H
