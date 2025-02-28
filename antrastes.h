#ifndef ANTRASTES_H
#define ANTRASTES_H

#include "strukt_antr.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm> // kad veiktu sort
#include <ctime> //rand
#include <random>
#include <fstream>
#include <sstream>
#include <chrono> //laiko skaiciavimui
#include <ctime>
#include <numeric> //accumulate
#include <iterator> //istream_iterator

using std::vector;
using std::string;

void vartotojo_pasirinkimas(int &nr_meniu, int a, int b);
bool ar_beda(int x, int pr, int pb);
bool ar_beda_bendras(int x, int pr, int pb);
int mediana_skaiciavimas(vector <int> &pazymiai, studentai &temp);
string vardo_generavimas();
string pavardes_generavimas();

void spausdinimas(vector<studentai> grupe);
void spausdinimas_faile(vector<studentai> grupe);

void rikiavimas(int nr_rikiavimas, vector<studentai> &grupe);
void spausdinimo_parinkimas(vector<studentai> grupe, int nr_spausdinimas, int nr_rikiavimas);


int sumos_skaiciavimas(vector <int> &pazymiai, studentai &temp);
double vidurkio_skaiciavimas(vector <int> &pazymiai, studentai &temp);
double galutinis_vid_sk(studentai &temp, double &vidurkis);
double galutinis_med_sk(studentai &temp, int &mediana);


void nuskaitymas(const string& failo_pavadinimas, vector<studentai>& grupe, int &n);
void skaiciavimas(vector<studentai>& grupe, int n);

#endif // ANTRASTES_H