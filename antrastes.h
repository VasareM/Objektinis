#ifndef ANTRASTES_H
#define ANTRASTES_H

#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::vector;
using std ::string;
using std::endl;

struct studentai
{
    string vardas;
    string pavarde;
    vector<int> pazymiai; //nd tarpiniai rezultatai
    int egzam;
    double vidurkis;
    int mediana;
    double gal_vid, gal_med;
};

#endif // ANTRASTES_H