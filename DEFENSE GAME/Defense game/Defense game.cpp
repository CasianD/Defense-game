// Defense game.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <Mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")
#define INSTRUCTIUNI ifstream f("READ_ME.txt");

const int length = 20;
int Coins = 100,Damage_I,Damage_C;
using namespace std;
int Infanterie[] = {250,260,270,285,290,295,300,320,330,400};
int Cavalerie[] = { 255,265,265,270,280,295,305,310,315,320 };
int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };
/////////////V, S ,E , N 
int dxc[] = { -1,-2,-2,-1,1,2,2,1 };
int dyc[] = { -2,-1,1,2,2,1,-1,-2 };
char Matrice[25][25];
int M[25][25],P[25][25],C[25][25];
int I[25][25], L[25][25],A[25][25],B[25][25];

struct punct{
    int abs, ord;
};
class turela
{
private:
public:
    struct puncte
    {
        int st_x, dr_x, st_y, dr_y;
    };

    int damage, cost, raza,abs,ord;
    int level;
    turela(int nivel,int x,int y)
    {
        if (nivel == 1)
        {
            damage = -10;
            cost = 10;
            raza = 2;
        }
        if (nivel == 2)
        {
            damage = -15;
            cost = 20;
            raza = 3;
        }
        if (nivel == 3)
        {
            damage = -30;
            cost = 40;
            raza = 3;
        }
        abs = x;
        ord = y;
        level = nivel;
    }
    void imprimare()
    {
        if(level == 1)
            Matrice[abs][ord] = 't';//lv 1
        else
        {
            if (level == 2)
                Matrice[abs][ord] = 'T';//lv 2
            else
                Matrice[abs][ord] = 'H';//lv 3
        }
    }
    void stergere()
    {
        Matrice[abs][ord] = '_';
    }
    puncte P;
    void coordonate()
    {
        
        P.st_x = abs - raza;
        if (P.st_x <= 0)
            P.st_x = 1;
        P.st_y = ord  - raza;
        if (P.st_y <= 0)
            P.st_y = 1;
        P.dr_x = abs + raza;
        if (P.dr_x > 20)
            P.dr_x = 20;
        P.dr_y = ord + raza;
        if (P.dr_y > 20)
            P.dr_y = 20;
    }
};

bool inner(int i, int j)
{
    return i > 0 && j > 0 && i <= length && j <= length;
}
void copy(int a[25][25], int b[25][25])
{
    for (int i = 1; i <= length; ++i)
        for (int j = 1; j <= length; j++)
            a[i][j] = b[i][j];
}
void make_matrix(int x[][25])
{
    for(int i = 1;i<= length;i++)
        for (int j = 1; j <= length; j++)
        {
            if (Matrice[i][j] == '#')
                x[i][j] = -1;
            else
                x[i][j] = 0;
        }
}
bool drum_posibil_1()
{
    int x[25][25];
    make_matrix(x);
    queue<pair<int, int> > Q;
    Q.push(make_pair(length, 1));
    x[length][1] = 1;
    while (!Q.empty())
    {
        int i = Q.front().first;
        int j = Q.front().second;
        for (int k = 0; k < 4; k++)
        {
            int inou = i + dx[k];
            int jnou = j + dy[k];
            if (inner(inou, jnou) && !x[inou][jnou] && Matrice[inou][jnou] == '_')
            {
                Q.push(make_pair(inou, jnou));
                x[inou][jnou] = x[i][j] + 1;
            }
        }
        Q.pop();
    }
    return x[1][length]!=0;
}
bool drum_posibil_2()
{
    int x[25][25];
    make_matrix(x);
    queue<pair<int, int> > Q;
    Q.push(make_pair(length, 1));
    x[length][1] = 1;
    while (!Q.empty())
    {
        int i = Q.front().first;
        int j = Q.front().second;
        for (int k = 0; k < 8; k++)
        {
            int inou = i + dxc[k];
            int jnou = j + dyc[k];
            if (inner(inou, jnou) && !x[inou][jnou] && Matrice[inou][jnou] == '_')
            {
                Q.push(make_pair(inou, jnou));
                x[inou][jnou] = x[i][j] + 1;
            }
        }
        Q.pop();
    }
    return x[1][length];
}
bool drum_posibil()
{
    if (drum_posibil_1() && drum_posibil_2() && Matrice[20][1] == '_')
        return true;
    else
        return false;
}
void afis(char M[][25])
{
    for (int i = 0; i <= length; i++,cout<<'\n')
    {
        for (int j = 0; j <= length; j++)
            cout << M[i][j]<<' ';
    }
}

void fil(int x, int y)
{
    queue<pair<int ,int> > F;
    F.push(make_pair(x, x));
    Matrice[x][x] = '#';
    while (!F.empty())
    {
        int i = F.front().first;
        int j = F.front().second;
        for (int k = 0; k < 4; k++)
        {
            int inou = i + dx[k];
            int jnou = j + dy[k];
            if (inou >= x && inou <= y && jnou >= x && jnou <= y && Matrice[inou][jnou]!='#')
            {
                F.push(make_pair(inou, jnou));
                Matrice[inou][jnou] = '#';
            }
        }
        F.pop();
    }
}
void generare()
{
    pair<int, int> INAC[] = { {2,3},{5,6}, {7,8}, {10,12},{15,16},{18,19} };
    for (int i = 0; i <= length +1; i++)
    {
        for (int j = 0; j <= length +1; j++)
        {
            Matrice[i][j] = '_'; 
            if (i == length +1 && j == 0)
                Matrice[i][j] = 'S';
            if (i == 0 && j == length +1)
            {
                Matrice[i][j] = 'F';
            }
        }
    }
    for (int i = 0; i < 6; i++)
    {
        fil(INAC[i].first, INAC[i].second);
    }
    int nr = '1';
    for (int i = 1; i <= 9; ++i)
    {
        Matrice[0][i] = nr++;
    }
    int asc = 'A';
    for (int i = 10; i <= length; i++)
    {
        Matrice[0][i] = asc++;
    }
    /////////////////////
    nr = '1';
    for (int i = 1; i <= 9; ++i)
    {
        Matrice[i][0] = nr++;
    }
    asc = 'A';
    for (int i = 10; i <= length; i++)
    {
        Matrice[i][0] = asc++;
    }
    Matrice[0][0] = '0';
}

void D_arrays(punct a, punct b,int val)
{
    int x1 = a.abs, y1 = a.ord, x2 = b.abs, y2 = b.ord;
    M[x1][y1] += val;
    M[x1][y2 + 1] -= val;
    M[x2 + 1][y1] -= val;
    M[x2 + 1][y2 + 1] += val;
}
void Difference_aray()
{
    for (int i = 1; i <= length; i++)
        for (int j = 1; j <= length; j++)
            M[i][j] += M[i - 1][j] + M[i][j - 1] - M[i - 1][j - 1];
}
void afis_int(int M[][25])
{
    for (int i = 1; i <= length; i++, cout << '\n')
        for (int j = 1; j <= length; j++)
            //cout << M[i][j] << ' ';
            printf("%4d ", M[i][j]);
}
void make_int()
{
    for (int i = 1; i <= length; i++)
        for (int j = 1; j <= length; j++)
        {
            if (!(Matrice[i][j] =='_'))
                M[i][j] = -1,P[i][j] = -1;
        }
}
void traseu1()
{
    queue<pair<int, int> > Q;
    Q.push(make_pair(length, 1));
    P[length][1] = 1;
    while (!Q.empty())
    {
        int i = Q.front().first;
        int j = Q.front().second;
        for (int k = 0; k < 4; k++)
        {
            int inou = i + dx[k];
            int jnou = j + dy[k];
            if (inner(inou, jnou) && Matrice[inou][jnou] == '_' && !P[inou][jnou])
            {
                Q.push(make_pair(inou, jnou));
                P[inou][jnou] = P[i][j] + 1;
            }
        }
        Q.pop();
    }
}

bool ok = false;
void reconstituire1(int i,int j)
{
    if (i == length && j == 1)
    {
        ok = true;
        return;
    }
    for (int k = 0; k < 4; k++)
    {
        int inou = i + dx[k];
        int jnou = j + dy[k];
        if (!ok && inner(inou, jnou) && !I[inou][jnou] && P[inou][jnou] == P[i][j] - 1)
        {
            Damage_I += M[inou][jnou];
            I[inou][jnou] = I[i][j]-1;
            reconstituire1(inou, jnou);
        }
    }
}
void traseu2()
{
    queue<pair<int, int> > Q;
    Q.push(make_pair(length, 1));
    C[length][1] = 1;
    while (!Q.empty())
    {
        int i = Q.front().first;
        int j = Q.front().second;
        for (int k = 0; k < 8; k++)
        {
            int inou = i + dxc[k];
            int jnou = j + dyc[k];
            if (inner(inou, jnou) && Matrice[inou][jnou] == '_' && !C[inou][jnou])
            {
                Q.push(make_pair(inou, jnou));
                C[inou][jnou] = C[i][j] + 1;
            }
        }
        Q.pop();
    }
}
void reconstituire2(int i, int j)
{
    if (i == length && j == 1)
    {
        ok = true;
        return;
    }
    for (int k = 0; k < 8; k++)
    {
        int inou = i + dxc[k];
        int jnou = j + dyc[k];
        if (!ok && inner(inou, jnou) && !L[inou][jnou] && C[inou][jnou] == C[i][j] - 1)
        {
            Damage_C += M[inou][jnou];
            L[inou][jnou] = L[i][j] - 1;
            reconstituire2(inou, jnou);
        }
    }
}
void Damage1()
{
    for (int i = 0; i < 9; i++)
    {
        Infanterie[i] += Damage_I;
    }
}
void Damage2()
{
    for (int i = 0; i < 9; i++)
    {
        Cavalerie[i] += Damage_C;
    }
}
int Cautare_bin1(int st, int dr)
{
    if (dr == 0)
        return 0;
    if (st == 9)
        return 10;
    int m = (st + dr) / 2;
    if (Infanterie[m] > 0 && Infanterie[m - 1] <= 0)
    {
        return m;
    }
    if (Infanterie[m] <= 0)
        return Cautare_bin1(m + 1, dr);
    else
        return Cautare_bin1(st,m-1);

}
int Cautare_bin2(int st, int dr)
{
    if (dr == 0)
        return 0;
    if (st == 9)
        return 10;
    int m = (st + dr) / 2;
    if (Cavalerie[m] > 0 && Cavalerie[m - 1] <= 0)
    {
        return m;
    }
    if (Cavalerie[m] <= 0)
        return Cautare_bin2(m + 1, dr);
    else
        return Cautare_bin2(st, m - 1);

}
void animatie1()
{
    for (int i = 1; i <= 4; ++i) {

        cout << "\b\b\b\b\b\b\b\b\b\bLoading   " << flush;
        Sleep(100);
        cout << "\b\b\b\b\b\b\b\b\b\bLOading   " << flush;
        Sleep(100);
        cout << "\b\b\b\b\b\b\b\b\b\bLoAding   " << flush;
        Sleep(100);
        cout << "\b\b\b\b\b\b\b\b\b\bLoaDing   " << flush;
        Sleep(100);
        cout << "\b\b\b\b\b\b\b\b\b\bLoadIng   " << flush;
        Sleep(100);
        cout << "\b\b\b\b\b\b\b\b\b\bLoadiNg   " << flush;
        Sleep(100);
        cout << "\b\b\b\b\b\b\b\b\b\bLoadinG   " << flush;
        Sleep(100);
        cout << "\b\b\b\b\b\b\b\b\b\bLoading.  " << flush;
        Sleep(100);
        cout << "\b\b\b\b\b\b\b\b\b\bLoading.." << flush;
        Sleep(100);
        cout << "\b\b\b\b\b\b\b\b\b\bLoading..." <<flush;
        Sleep(100);
    }
}
void scor()
{
    int scor;
    ifstream in("scor.txt");
    in >> scor;

    ofstream out("scor.txt");
    int scor_nou = 10 - Cautare_bin1(0, 9) + 10 - Cautare_bin2(0, 9);
    if (scor_nou < scor)
    { 
        out << scor_nou;
        PlaySound(TEXT("sunet 1.wav"), NULL, SND_FILENAME);
        MessageBox(nullptr, TEXT("Ai atins un nou record!" ), TEXT("RECORD"), MB_OK);
    }
    else
    {
        out << scor;
    }
}

int main()
{   
    string In;
    char c;
    int nivel, abs, ord; 
    INSTRUCTIUNI;
    MessageBox(nullptr, TEXT("Bine ai venit!"), TEXT("TOWER DEFENSE"), MB_OK);
    animatie1();
    system("cls");
    while (getline(f, In))
    {
        cout << In;
        cout << '\n';
    }
    system("pause");
    system("cls");
    system("color E1");
    cout << "Iata harta ,zonele marcate cu # sunt inaccesibile"<<'\n'<<'\n';
    generare();
    afis(Matrice);
    cout << '\n' << '\n';
    cout << "Introduceti datele necesare amplasarii turelelor :" << '\n' << '\n';
    while (Coins>0)
    {
        if (Coins < 10)
            break;
        cout << "Nivel: ";
        cin >> nivel;
        cout << "Ordonata: ";
        cin >> abs;
        cout << "Abscisa: ";
        cin >> ord;
        cout << '\n';
        if (inner(abs, ord) && Matrice[abs][ord] == '_' && nivel>0 && nivel<=3)
        {
            turela tun(nivel, abs, ord);
            tun.coordonate();
            tun.imprimare();
            if (!drum_posibil())
            {
                tun.stergere();
                Coins += tun.cost;
                cout << "Traseu blocat.Introduceti alte date: " << '\n'<<'\n';
                continue;
            }
            Coins -= tun.cost;
            if (Coins < 0 && Coins + tun.cost >9)
            {
                tun.stergere();
                cout << "Alegeti un tun mai ieftin" << '\n';
                Coins += tun.cost;
                continue;
            }
            afis(Matrice);
            cout << '\n';
            cout << "Coins ramasi : " << Coins << '\n'<<'\n';
            punct a, b;
            a.abs = tun.P.st_x;
            a.ord = tun.P.st_y;
            b.abs = tun.P.dr_x;
            b.ord = tun.P.dr_y;
            D_arrays(a, b,tun.damage);
        }
        else
        {
            cout << "Alegeti alte coordonate intrucat cele alese anterior depasesc marginile hartii sau sunt inaccesibile, sau nivelul este nepotrivit:" << '\n';
            cout << '\n';
        }
    }
    cout << '\n'<<'\n';
    Difference_aray();
    make_int();
    cout << "Iata damage-ul ce va fi imprimat de turele: " << '\n'<<'\n';
    afis_int(M);
    cout << '\n' << '\n';
    traseu1();
    Damage_I += M[1][length];
    I[1][length] = P[1][length];
    reconstituire1(1, length);
    /////////////////////////
    system("pause");
    cout << '\n';
    cout << "Traseul efectuat de infanterie : " << '\n' << '\n';
    afis_int(I);
    cout << '\n';
    cout << "Damage-ul total imprimat asupra infanteriei: " << Damage_I;
    cout << '\n' << '\n';
    ok = false;
    system("pause");
    cout << '\n';
    traseu2();
    L[1][length] = C[1][length];
    Damage_C += M[1][length];
    reconstituire2(1, length);
    cout << "Traseul efectuat de cavalerie : " << '\n' << '\n';
    afis_int(L);
    cout << '\n';
    cout << "Damage-ul total imprimat asupra cavaleriei: " << Damage_C;
    cout << '\n' << '\n';
    Damage1();
    Damage2();
    system("pause");
    cout << '\n';
    cout<<"Numrul soldatilor de infanterie supravietuitori : "<<10- Cautare_bin1(0, 9)<<'\n';
    cout << "Numarul soldatilor de cavalerie supravietuitori : " << 10 - Cautare_bin2(0, 9) << '\n';
    cout << "Numarul total al soldatilor supravietuitori : " << 10 - Cautare_bin1(0, 9)+ 10 - Cautare_bin2(0, 9) << '\n'<<'\n';
    cin.get(c);
    animatie1();
    if (10 - Cautare_bin1(0, 9) + 10 - Cautare_bin2(0, 9) <= 5)
    {
        PlaySound(TEXT("WIN.wav"), NULL, SND_FILENAME);
        MessageBox(nullptr, TEXT("Felicitari ai castigat jocul"), TEXT("REZULTAT"), MB_OK);
    }
    else
        if (10 - Cautare_bin1(0, 9) + 10 - Cautare_bin2(0, 9) <= 8)
        {
            PlaySound(TEXT("LOSE.wav"), NULL, SND_FILENAME);
            MessageBox(nullptr, TEXT("Esti pe aproape!"), TEXT("REZULTAT"), MB_OK);
        }
        else
            if (10 - Cautare_bin1(0, 9) + 10 - Cautare_bin2(0, 9) <= 12)
            {
                PlaySound(TEXT("LOSE.wav"), NULL, SND_FILENAME);
                MessageBox(nullptr, TEXT("Slabut,mai incearca!"), TEXT("REZULTAT"), MB_OK);
            }
            else
            {
                PlaySound(TEXT("LOSE.wav"), NULL, SND_FILENAME);
                MessageBox(nullptr, TEXT("Ai pierdut!"), TEXT("REZULTAT"), MB_OK);
            }
    scor();
}
