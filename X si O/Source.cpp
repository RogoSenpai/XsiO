#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>

using namespace std;

char  tabla[3][3];

void Tabla()
{
    cout << "      |      |       " << endl;
    cout << "  " << tabla[0][0] << "   |  " << tabla[0][1] << "   |  " << tabla[0][2] << "   " << endl;
    cout << "______|______|______ " << endl;
    cout << "      |      |       " << endl;
    cout << "  " << tabla[1][0] << "   |  " << tabla[1][1] << "   |  " << tabla[1][2] << "   " << endl;
    cout << "______|______|______ " << endl;
    cout << "      |      |       " << endl;
    cout << "  " << tabla[2][0] << "   |  " << tabla[2][1] << "   |  " << tabla[2][2] << "   " << endl;
    cout << "      |      |       " << endl;
}

int mutareValida(char c)
{
    if (c < '1' || c>'9')
        return 0;
    else
        if (tabla[(c - '1') / 3][(c - '1') % 3] == 'X' || tabla[(c - '1') / 3][(c - '1') % 3] == 'O')
            return 0;
        else
            return 1;
}

int egalitate()
{
    int egl = 0;
    for (int i = 0; i < 9; i++)
        if (tabla[i / 3][i % 3] == 'X')
            egl++;
    if (egl == 5)
        return 1;
    else
        return 0;
}

int castig()
{
    for (int i = 0; i < 3; i++)
    {
        if (tabla[i][0] == tabla[i][1] && tabla[i][1] == tabla[i][2])
        {
            return 1;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (tabla[0][i] == tabla[1][i] && tabla[1][i] == tabla[2][i])
        {
            return 1;
        }
    }


    if (tabla[0][0] == tabla[1][1] && tabla[1][1] == tabla[2][2])
        return 1;
    if (tabla[0][2] == tabla[1][1] && tabla[1][1] == tabla[2][0])
        return 1;

    if (egalitate())
        return 2;

    return 0;

}

int celuleGoale() {
    int contuar = 0;
    for (int i = 0; i < 9; i++)
    {
        if (isdigit(tabla[i / 3][i % 3]))
            contuar++;
    }
    return contuar;
}

int minimax_recursiv(bool jucator)
{
    if (celuleGoale() == 0)
        return 0;
    int scor[] = { 0,0,0,0,0,0,0,0,0 };
    for (int i = 0; i < 9; i++)
    {
        scor[i] = (jucator ? 1000 : -1000);
        if (mutareValida(i + '1'))
        {
            tabla[i / 3][i % 3] = (jucator ? 'X' : 'O');
            if (castig() == 1)
            {
                tabla[i / 3][i % 3] = i + '1';
                return (jucator ? -10 : 10);
            }
            else if (castig() == 0)
            {
                scor[i] = minimax_recursiv(!jucator);
            }
            tabla[i / 3][i % 3] = i + '1';
        }
    }
    int bestScore = (jucator ? 1000 : -1000);
    for (int i = 0; i < 9; i++)
    {
        if (scor[i] < bestScore && jucator)
            bestScore = scor[i];
        if (scor[i] > bestScore && !jucator)
            bestScore = scor[i];
    }
    return bestScore;
}

char minimax()
{
    int scor[] = { 0,0,0,0,0,0,0,0,0 };
    for (int i = 0; i < 9; i++)
    {
        if (mutareValida(i + '1'))
        {
            tabla[i / 3][i % 3] = 'O';
            if (castig() == 1)
            {
                tabla[i / 3][i % 3] = i + '1';

                return i + '1';
            }
            else if (castig() == 0)
            {
                scor[i] = minimax_recursiv(true);
            }
            tabla[i / 3][i % 3] = i + '1';
        }
    }
    int bestScore = -666;
    int pozitia = 0;
    for (int i = 0; i < 9; i++)
    {
        if (scor[i] > bestScore) {
            bestScore = scor[i];
            pozitia = i;
        }

    }
    return pozitia + '1';
}

void resetare()
{
    for (int i = 0; i < 9; i++)
        tabla[i / 3][i % 3] = '1' + i;
}

void start()
{
    char poz, jucator = 'X';
    Tabla();
    int status = 0;
    while (666)
    {
        if (jucator == 'X')
            do
            {
                cout << "\nIntroduceti pozitia CORECTA pe care doriti sa puneti : ";
                cin >> poz;
                Beep(3500, 400);
            } while (!mutareValida(poz));
        else
            poz = minimax();
        tabla[(poz - '1') / 3][(poz - '1') % 3] = jucator;
        system("cls");
        Tabla();
        status = castig();
        if (status)
            break;
        jucator = (jucator == 'X' ? 'O' : 'X');
    }
    if (status != 2)
        cout << "\nJucatorul cu " << jucator << " a castigat\n";
    else
        cout << "\nEste remiza\n";
}

int main()
{
    char optiune;
    resetare();
    start();
    while (666)
    {
        cout << "\nAlege r pentru resetare\n";
        cout << "Alege i pentru a iesi\n--->";
        while (!_kbhit())
            Beep(1200, 500);
        optiune = _getch();
        system("cls");
        switch (optiune)
        {
        case 'r':resetare(); start(); break;
        case 'i':return 0;
        default:cout << "Comanda invalida.\n";
        }
    }
    _getch();
    return 0;
}
