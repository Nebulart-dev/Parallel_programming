#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <locale>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    long long totalStart = 10;
    long long totalEnd = 100000000;
    int numParts = 4;
    long long range = (totalEnd - totalStart + 1) / numParts;
    vector<PROCESS_INFORMATION> processes;

    for (int i = 0; i < numParts; i++) {
        long long start = totalStart + i * range;
        long long end = (i == numParts - 1) ? totalEnd : start + range - 1;
        string command = "WorkerApp.exe " + to_string(start) + " " + to_string(end);
        cout << "Запуск: " << command << endl;
        vector<char> buffer(command.begin(), command.end());
        buffer.push_back('\0'); 

        STARTUPINFOA si{};
        PROCESS_INFORMATION pi{};
        si.cb = sizeof(si);

        if (CreateProcessA(
            NULL,
            buffer.data(),
            NULL, NULL, FALSE,
            0, NULL, NULL,
            &si, &pi))
        {
            processes.push_back(pi);
        }
        else {
            cout << "Ошибка запуска WorkerApp!" << endl;
        }
    }

    for (auto& pi : processes) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    cout << "Все процессы завершены." << endl;
    return 0;
}