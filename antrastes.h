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







///
int sumos_skaiciavimas(vector <int> &pazymiai, studentai &temp)
{
    int suma=0;
    suma=std::accumulate(temp.pazymiai.begin(), temp.pazymiai.end(), 0);
    return suma;
}
double vidurkio_skaiciavimas(vector <int> &pazymiai, studentai &temp)
{
    double vidurkis=0;
    vidurkis=sumos_skaiciavimas(pazymiai, temp)/(double)temp.pazymiai.size();
    return vidurkis;
}
double galutinis_vid_sk(studentai &temp, double &vidurkis)
{
    double gal_v=0;
    gal_v=0.4*temp.vidurkis+0.6*temp.egzam;
    return gal_v;
}
double galutinis_med_sk(studentai &temp, int &mediana)
{
    double gal_v=0;
    gal_v=0.4*temp.mediana+0.6*temp.egzam;
    return gal_v;
}
///


#endif // ANTRASTES_H