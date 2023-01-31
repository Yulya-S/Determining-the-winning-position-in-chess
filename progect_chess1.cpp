#include <iostream>
#include "chess.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    if (argc != 3) {
        cout << "Ошибка! количество данных не верно." << endl;
        cout << "Запуск: progect_chess1.exe inFile.txt outFile.txt" << endl;
        system("pause");
        return 0;
    }

    matVDva(argv[1], argv[2]);
    system("pause");
}