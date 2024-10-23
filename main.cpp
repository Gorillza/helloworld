#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <complex>
#include <random>
#include <ctime>
#include "qam_modulator.h"
#include "awgn_generator.h"
#include "qam_demodulator.h"

// Error Rate Calculation для расчета BER
std::pair<int, double> errorRateCalculation(const std::vector<int>& txBits, const std::vector<int>& rxBits) {
    int errors = 0;  // Количество ошибок
    size_t totalBits = txBits.size();  // Общее количество бит

    // Сравниваем переданные и полученные биты
    for (size_t i = 0; i < totalBits; ++i) {
        if (txBits[i] != rxBits[i]) {
            ++errors;
        }
    }

    // Вычисляем BER
    double ber = static_cast<double>(errors) / static_cast<double>(totalBits);  // Явное приведение к double

    return {errors, ber};  // Возвращаем количество ошибок и BER
}

int main() {
    // Увеличиваем размер входных данных до около 1e6 бит
    size_t num_bits = 10000000;

    // Генерация случайных битов (0 и 1) для входных данных
    std::vector<int> inputBits(num_bits);
    std::default_random_engine generator(static_cast<unsigned int>(time(0)));
    std::uniform_int_distribution<int> binaryDist(0, 1);

    for (size_t i = 0; i < num_bits; ++i) {
        inputBits[i] = binaryDist(generator);
    }

    // Создаем модулятор для 16-QAM
    QAMModulator mod16(16);
    auto modulatedSignal_16 = mod16.modulate(inputBits);

    // Создаем модулятор для 64-QAM
    QAMModulator mod64(64);
    auto modulatedSignal_64 = mod64.modulate(inputBits);

    // Создаем демодулятор для 16-QAM
    QAMDemodulator demod16(16);

    // Создаем демодулятор для 64-QAM
    QAMDemodulator demod64(64);

    {   //Тест
        auto demodulatedSignal_16 = demod16.demodulate(modulatedSignal_16);
        auto demodulatedSignal_64 = demod64.demodulate(modulatedSignal_64);

        auto [errors_16, ber_practical_16] = errorRateCalculation(inputBits, demodulatedSignal_16);
        auto [errors_64, ber_practical_64] = errorRateCalculation(inputBits, demodulatedSignal_64);

        std::cout << "functionality check whitout AWG QAM-16: " << std::endl << "Errors: " << errors_16
                    << ", Practical BER: " << ber_practical_16 << std::endl << std::endl;

        std::cout << "functionality check whitout AWG QAM-64: " << std::endl << "Errors: " << errors_64
                    << ", Practical BER: " << ber_practical_64 << std::endl << std::endl;
    }
    // Открываем файл для записи
    std::ofstream outputFile16("QAM16.txt");

    // Открываем файл для записи
    std::ofstream outputFile64("QAM64.txt");

    // Проверяем, открыт ли файл
    if (!outputFile16.is_open() && !outputFile64.is_open()) {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return 1;
    }

    // Устанавливаем высокую точность вывода
    outputFile16 << std::setprecision(10) << std::scientific;
    outputFile64 << std::setprecision(10) << std::scientific;
    std::cout << std::setprecision(10) << std::scientific;

    // Тестируем на различных значениях SNR
    outputFile16 << "SNR(dB) Errors Practical_BER" << std::endl;
    outputFile64 << "SNR(dB) Errors Practical_BER" << std::endl;

    for (double snr_db = 0.0; snr_db <= 16.0; snr_db += 1.0) {
        // Создаем генератор белого гауссовского шума с заданным SNR
        AWGNGenerator noiseGen(snr_db, 67);
        //модулируем сигнал
        auto modulatedSignal_16 = mod16.modulate(inputBits);
        auto modulatedSignal_64 = mod64.modulate(inputBits);

        // Добавляем шум к модулированному сигналу
        auto noisySignal_16 = noiseGen.addNoise(modulatedSignal_16);
        auto noisySignal_64 = noiseGen.addNoise(modulatedSignal_64);

        // Демодулируем сигнал
        auto demodulatedSignal_16 = demod16.demodulate(noisySignal_16);
        auto demodulatedSignal_64 = demod64.demodulate(noisySignal_64);

        // Используем блок "Error Rate Calculation"
        auto [errors_16, ber_practical_16] = errorRateCalculation(inputBits, demodulatedSignal_16);
        auto [errors_64, ber_practical_64] = errorRateCalculation(inputBits, demodulatedSignal_64);

        // Записываем результаты в файл: SNR, количество ошибок, практическое BER, мощность сигнала, мощность шума
        outputFile16 << snr_db << " " << errors_16 << " " << ber_practical_16
                   << " "  << std::endl;
        outputFile64 << snr_db << " " << errors_64 << " " << ber_practical_64
                   << " "  << std::endl;

        std::cout<<"snr_db: " << snr_db<< std::endl;
    }

    // Закрываем файл
    outputFile16.close();
    outputFile64.close();

    std::cout << "data succsecfull writhe QAM16.txt and QAM64.txt." << std::endl;

    return 0;
}
