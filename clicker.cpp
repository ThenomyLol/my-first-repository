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
            cout << "ó òåáÿ íåäîñòàòî÷íî äåíåã!" << endl;
        }
        break;
    case 2:
        if (score >= costup) {
            score -= costup;
            scoreplus += 0.2;
            costup *= 2;
        }
        else {
            cout << "ó òåáÿ íåäîñòàòî÷íî äåíåã!" << endl;
        }
        break;
    case 3:
        if (score >= costac) {
            enableautoclick = true;
            score -= 100;
        }
        else {
            cout << "ó òåáÿ íåäîñòàòî÷íî äåíåã!" << endl;
        }
    }
}

void shop() {
    char key;
    bool inShop = true;
    while (inShop) {
        system("cls");
        cout << "(èãðà íà ïàóçå - äåíüãè íå çàðàáàòûâàþòñÿ)" << endl;
        cout << "òâîè äåíüãè: " << score << endl;
        cout << "÷òî õî÷åøü êóïèòü?" << endl;
        cout << "1 - Óäâîåíèå ïîëó÷àåìûõ î÷êîâ çà êëèê (ñòîèìîñòü: " << costx2 << ")" << endl;
        cout << "2 - Ïðèáàâêó ê ïîëó÷àåìûì î÷êàì çà êëèê íà 0.2 (ñòîèìîñòü: " << costup << ")" << endl;
        if (enableautoclick == false) { cout << "3 - àâòîêëèê 1 êëèê â ñåêóíäó (ñòîèìîñòü: " << costac << ")" << endl; }
        cout << "x - Âûõîä èç ìàãàçèíà" << endl;

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
            cout << "íåò òàêîé ïîçèöèè!" << endl;
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
    cout << "áàëàíñ: " << score << endl;
    cout << Myvoid << "óïðàâëåíèå:" << endl;
    cout << Myvoid << "ïðîáåë: êëèê" << endl;
    cout << Myvoid << "s: ìàãàçèí óëó÷øåíèé" << endl;
    cout << Myvoid << "x: ñîõðàíèòü è âûéòè" << endl;
    Sleep(itime);
    system("cls");
}

int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "Russian");
    ifstream inputFile("data.txt");
    if (!inputFile.is_open()) {
        cout << "Îøèáêà îòêðûòèÿ ôàéëà!" << endl;
        return 1;
    }

    inputFile >> score >> scoreplus >> costx2 >> costup;
    inputFile.close();

    cout << "Íàæìèòå ëþáóþ êëàâèøó ÷òîáû íà÷àòü" << endl;
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
                    cout << "Îøèáêà îòêðûòèÿ ôàéëà!" << endl;
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
