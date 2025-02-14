#ifndef ANTRASTESMAS_H
#define ANTRASTESMAS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm> // kad veiktu sort
#include <ctime> //rand
#include <random>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::endl;
using std::setw;

struct studentai
{
    int N=0; //ateityje nebus problemu
    string vardas="var"; //default reiksmes testavimui
    string pavarde="pav";
    int *P=new int[N];
    //vector<int> pazymiai; //nd tarpiniai rezultatai
    //paz{1, 2, 3, 4, 5}; //paz.clear()
    int egzam;
    double suma=0;
    double vidurkis;
    int mediana;
    double gal_vid, gal_med;
};
bool ar_beda(int x, int pr=0, int pb=10)
{
    if (x<pr || x>pb)
    {
        cout << "Neteisinga įvestis" << endl;
        return true;
    }
    return false;
}

void spausdinimas(vector <studentai> grupe)
{
    cout << std::left << setw(25) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    cout << string(85, '-') << endl;
    for (const auto&m:grupe) //visi elementai is eiles is grupes; const, kad nesikopijuot7
    {
        cout << std::left << setw(25) << m.pavarde << setw(20) << m.vardas;
        cout << setw(20) << std::fixed << std::setprecision(2) << m.gal_vid << setw(20) << m.gal_med << endl;
    }
}
void mediana_skaiciavimas(int n, studentai &temp)
{
    std::sort(temp.P, temp.P+n);
        {
            if (n%2==0)
            {
                temp.mediana=((temp.P[n/2-1]+temp.P[n/2]))/2;
            }
            else 
            {
                temp.mediana=temp.P[n/2];
            }
        }
        //temp.mediana=median(temp.pazymiai);
}
string vardo_generavimas()
{
    vector <string> vardu_sar={"Petras", "Jonas", "Aloyzas", "Kastytis", "Gintaras", "Tomas", "Augustas", "Dovydas", "Markas"};
    int vardo_nr=rand()%vardu_sar.size();
    return vardu_sar[vardo_nr];
}
string pavardes_generavimas()
{
    vector <string> pavardu_sar={"Petraitis", "Jonaitis", "Sabonis", "Zukauskas", "Stankevicius", "Maciulis", "Kudirka", "Basanavicius", "Marcinkevicius"};
    int pavardo_nr=rand()%pavardu_sar.size();
    return pavardu_sar[pavardo_nr];
}

#endif // ANTRASTES_H