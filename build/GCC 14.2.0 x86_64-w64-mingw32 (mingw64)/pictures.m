% Открываем файл для чтения практических данных
fid = fopen('QAM16.txt', 'r');

% Пропускаем первую строку с заголовками
fgetl(fid);

% Читаем данные из файла (SNR, количество ошибок, практическое BER, мощность сигнала, мощность шума)
data = textscan(fid, '%f %f %f %f %f'); 

% Закрываем файл
fclose(fid);

% Извлекаем данные
snr_db = data{1};        % Первая колонка - SNR
errors = data{2};        % Вторая колонка - Количество ошибок
ber_practical = data{3}; % Третья колонка - Практический BER
signal_power = data{4};  % Четвертая колонка - Мощность сигнала

% Рассчитываем теоретический BER для 16-QAM
M = 16;  % Для 16-QAM
eb_n0_db = snr_db;  % Используем те же значения SNR

% Перевод SNR из дБ в линейную шкалу
eb_n0 = 10.^(eb_n0_db / 10);

% Теоретический расчет BER для 16-QAM
ber_theoretical = (2 * (M - 1) / (M * log2(M))) .* qfunc(sqrt((3 * log2(M) * eb_n0) / (M - 1)));

% Построение графиков

% График BER (практическое и теоретическое)
figure;
semilogy(snr_db, ber_practical, '-o', 'LineWidth', 2);  % График практического BER
hold on;
semilogy(snr_db, ber_theoretical, '--r', 'LineWidth', 2); % График теоретического BER
grid on;
xlabel('SNR (dB)');
ylabel('Bit Error Rate (BER)');
title('BER for 16-QAM: Practical vs Theoretical');
legend('Practical BER (16-QAM)', 'Theoretical BER (16-QAM)');
hold off;
%% //---------------------------------------------------------------------------------------------------------
% Открываем файл для чтения практических данных
fid = fopen('QAM64.txt', 'r');

% Пропускаем первую строку с заголовками
fgetl(fid);

% Читаем данные из файла (SNR, количество ошибок, практическое BER, мощность сигнала, мощность шума)
data = textscan(fid, '%f %f %f %f %f'); 

% Закрываем файл
fclose(fid);

% Извлекаем данные
snr_db = data{1};        % Первая колонка - SNR
errors = data{2};        % Вторая колонка - Количество ошибок
ber_practical = data{3}; % Третья колонка - Практический BER
signal_power = data{4};  % Четвертая колонка - Мощность сигнала

% Рассчитываем теоретический BER для 64-QAM
M = 64;  % Для 64-QAM
eb_n0_db = snr_db;  % Используем те же значения SNR

% Перевод SNR из дБ в линейную шкалу
eb_n0 = 10.^(eb_n0_db / 10);

% Теоретический расчет BER для 64-QAM
ber_theoretical = (2 * (M - 1) / (M * log2(M))) .* qfunc(sqrt((3 * log2(M) * eb_n0) / (M - 1)));

% Построение графиков

% График BER (практическое и теоретическое)
figure;
semilogy(snr_db, ber_practical, '-o', 'LineWidth', 2);  % График практического BER
hold on;
semilogy(snr_db, ber_theoretical, '--r', 'LineWidth', 2); % График теоретического BER
grid on;
xlabel('SNR (dB)');
ylabel('Bit Error Rate (BER)');
title('BER for 64-QAM: Practical vs Theoretical');
legend('Practical BER (64-QAM)', 'Theoretical BER (64-QAM)');
hold off;



