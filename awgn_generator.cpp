#include "awgn_generator.h"
#include <cmath>

AWGNGenerator::AWGNGenerator(double snrDb, unsigned int seed) : snrDb(snrDb), generator(seed) {}

double AWGNGenerator::calculateNoisePower(double signalPower) {
    // Преобразуем SNR из дБ в линейную шкалу
    double snrLinear = std::pow(10, snrDb / 10.0);
    return signalPower / snrLinear;  // Мощность шума
}

std::vector<std::complex<double>> AWGNGenerator::addNoise(const std::vector<std::complex<double>>& signal) {
    std::vector<std::complex<double>> noisySignal = signal;

    // Рассчитываем среднюю мощность сигнала
    double signalPower = 0.0;
    for (const auto& s : signal) {
        signalPower += std::norm(s);  // Мощность сигнала — квадрат амплитуды
    }
    signalPower /= signal.size();  // Усредненная мощность сигнала

    // Рассчитываем мощность шума
    double noisePower = calculateNoisePower(signalPower);

    // Генерируем белый гауссовский шум
    std::normal_distribution<double> distribution(0.0, std::sqrt(noisePower));

    for (auto& s : noisySignal) {
        double noiseReal = distribution(generator);
        double noiseImag = distribution(generator);
        s += std::complex<double>(noiseReal, noiseImag);  // Добавляем шум
    }

    return noisySignal;
}
