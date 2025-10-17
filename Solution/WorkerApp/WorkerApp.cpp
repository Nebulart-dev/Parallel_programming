#include <iostream>
#include <windows.h>
#include <locale>
#include <cmath>
#include <vector>
#include <string>
#include <thread>

using namespace std;

bool isPrime(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    for (long long i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    if (argc < 3) {
        cout << "Использование: WorkerApp <start> <end>\n";
        return 1;
    }

    long long start = atoll(argv[1]);
    long long end = atoll(argv[2]);

    cout << "Процесс обрабатывает диапазон [" << start << ", " << end << "]\n";
    cout << "Загрузка...";
    long long countTwins = 0;
    long long prevPrime = -1;
    for (long long i = start; i <= end; i++) {
        if (isPrime(i)) {
            if (prevPrime != -1 && i - prevPrime == 2)
                countTwins++;
            prevPrime = i;
        }
    }

    cout << "\nНайдено " << countTwins << " пар чисел-близнецов в диапазоне ["
        << start << " - " << end << "]\n";

    system("pause");
    return 0;
}