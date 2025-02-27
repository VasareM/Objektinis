#ifndef strukt_antr_h
#define strukt_antr_h

#include <vector>
#include <string>

using std::vector;
using std::string;

struct studentai
{
    string vardas="var"; //default reiksmes testavimui
    string pavarde="pav";
    vector<int> pazymiai; //nd tarpiniai rezultatai
    int egzam;
    double suma=0;
    double vidurkis;
    int mediana;
    double gal_vid, gal_med;
};

#endif