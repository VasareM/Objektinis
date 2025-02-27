#ifndef strukt_antr_h
#define strukt_antr_h

#include <vector>
#include <string>

struct studentai
{
    string vardas="var"; //defalt reiksmes testavimui
    string pavarde="pav";
    vector<int> pazymiai; //nd tarpiniai rezultatai
    int egzam;
    double suma=0;
    double vidurkis;
    int mediana;
    double gal_vid, gal_med;
};

bool ar_beda(int x, int pr = 0, int pb = 10);
int mediana_skaiciavimas(vector <int> &pazymiai, studentai &temp)
string vardo_generavimas();
string pavardes_generavimas();

void spausdinimas(vector<studentai> grupe);
void spausdinimas_faile(vector<studentai> grupe);

void rikiavimas(int nr_rikiavimas, vector<studentai> &grupe);
void spausdinimo_parinkimas(vector<studentai> grupe, int nr_spausdinimas, int nr_rikiavimas);


void nuskaitymas(const string& failo_pavadinimas, vector<studentai>& grupe, int &n);
void skaiciavimas(vector<studentai>& grupe, int n);

#endif