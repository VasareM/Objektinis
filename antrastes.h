#ifndef ANTRASTES_H
#define ANTRASTES_H

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
    string vardas="var"; //defalt reiksmes testavimui
    string pavarde="pav";
    vector<int> pazymiai; //nd tarpiniai rezultatai
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

#endif // ANTRASTES_H