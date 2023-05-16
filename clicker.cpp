#include <iostream>
#include <fstream>
#include <iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;
int itime = 1000;
bool game = true;
float score;
float scoreplus = 1;
int costx2 = 50;
int costup = 10;
int costac = 100;
bool enableautoclick = false;
string Myvoid(40, ' ');

void buy(int number) {
    switch (number) {
    case 1:
        if (score >= costx2) {
            score -= costx2;
            scoreplus *= 2;
            costx2 *= 2;
        }
        else {
            cout << "у тебя недостаточно денег!" << endl;
        }
        break;
    case 2:
        if (score >= costup) {
            score -= costup;
            scoreplus += 0.2;
            costup *= 2;
        }
        else {
            cout << "у тебя недостаточно денег!" << endl;
        }
        break;
    case 3:
        if (score >= costac) {
            enableautoclick = true;
            score -= 100;
        }
        else {
            cout << "у тебя недостаточно денег!" << endl;
        }
    }
}

void shop() {
    char key;
    bool inShop = true;
    while (inShop) {
        system("cls");
        cout << "(игра на паузе - деньги не зарабатываются)" << endl;
        cout << "твои деньги: " << score << endl;
        cout << "что хочешь купить?" << endl;
        cout << "1 - Удвоение получаемых очков за клик (стоимость: " << costx2 << ")" << endl;
        cout << "2 - Прибавку к получаемым очкам за клик на 0.2 (стоимость: " << costup << ")" << endl;
        if (enableautoclick == false) { cout << "3 - автоклик 1 клик в секунду (стоимость: " << costac << ")" << endl; }
        cout << "x - Выход из магазина" << endl;

        key = _getch();
        switch (key) {
        case '1':
            buy(1);
            break;
        case '2':
            buy(2);
            break;
        case '3':
            buy(3);
            break;
        case 'x':
            inShop = false;
            break;
        default:
            cout << "нет такой позиции!" << endl;
        }
    }
}

void click() {
    score += scoreplus;
}

void print() {
    itime = 1000;
    if (enableautoclick == true) {
        score++;
    }
    cout << "баланс: " << score << endl;
    cout << Myvoid << "управление:" << endl;
    cout << Myvoid << "пробел: клик" << endl;
    cout << Myvoid << "s: магазин улучшений" << endl;
    cout << Myvoid << "x: сохранить и выйти" << endl;
    Sleep(itime);
    system("cls");
}

int main() {
    setlocale(LC_ALL, "Russian");
    ifstream inputFile("data.txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    inputFile >> score >> scoreplus >> costx2 >> costup;
    inputFile.close();

    cout << "Нажмите любую клавишу чтобы начать" << endl;
    char knop = _getch();

    while (game) {
        print();

        if (_kbhit()) {
            char key = _getch();

            switch (key) {
            case ' ':
                click();
                itime = 1;
                break;
            case 's':
                shop();
                break;
            case 'x':
                game = false;
                ofstream outputFile("data.txt");

                if (!outputFile.is_open()) {
                    cout << "Ошибка открытия файла!" << endl;
                    return 1;
                }

                outputFile << score << " " << scoreplus << " " << costx2 << " " << costup;

                outputFile.close();
                break;
            }
        }
    }
    return 0;
}