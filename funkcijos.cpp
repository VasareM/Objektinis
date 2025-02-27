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

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::endl;
using std::setw;
using std::ifstream;
using std::ofstream;
using std::sort;


bool ar_beda(int x, int pr=0, int pb=10)
{
    if (x<pr || x>pb)
    {
        cout << "Neteisinga įvestis" << endl;
        return true;
    }
    return false;
}
int mediana_skaiciavimas(vector <int> &pazymiai, studentai &temp)
{
    int n=temp.pazymiai.size(), med=0;
    sort(temp.pazymiai.begin(), temp.pazymiai.end());
        {
            if (n%2==0)
            {
                med=((temp.pazymiai[n/2-1]+temp.pazymiai[n/2]))/2;
            }
            else 
            {
                med=temp.pazymiai[n/2];
            }
        }
        //temp.mediana=median(temp.pazymiai);
        return med;
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
void spausdinimas(vector <studentai> grupe)
{
    cout << std::left << setw(25) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    cout << string(85, '-') << endl;
    for (const auto&m:grupe) //visi elementai is eiles is grupes; const, kad nesikopijuot7
    {
        cout << std::left << setw(25) << m.pavarde << setw(20) << m.vardas;
        cout << setw(20) << std::fixed << std::setprecision(2) << m.gal_vid << setw(20) << m.gal_med << endl;
        //for(const auto&n:m.pazymiai) cout << n << " ";
        //cout << endl;
    }
}
void spausdinimas_faile(vector <studentai> grupe)
{
    ofstream out ("rezultatai.txt");
    out << std::left << setw(25) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    out << string(85, '-') << endl;
    for (const auto&m:grupe) //visi elementai is eiles is grupes; const, kad nesikopijuot7
    {
        out << std::left << setw(25) << m.pavarde << setw(20) << m.vardas;
        out << setw(20) << std::fixed << std::setprecision(2) << m.gal_vid << setw(20) << m.gal_med << endl;
        //for(const auto&n:m.pazymiai) cout << n << " ";
        //cout << endl;
    }
}
void rikiavimas(int nr_rikiavimas, vector <studentai> &grupe)
{
    if (nr_rikiavimas==1) sort(grupe.begin(),grupe.end(), [](studentai a, studentai b) {return a.vardas<b.vardas;});
    else if (nr_rikiavimas==2) sort(grupe.begin(),grupe.end(), [](studentai a, studentai b) {return a.pavarde<b.pavarde;});
    else if (nr_rikiavimas==3) sort(grupe.begin(),grupe.end(), [](studentai a, studentai b) {return a.gal_vid<b.gal_vid;});
    else if (nr_rikiavimas==4) sort(grupe.begin(),grupe.end(), [](studentai a, studentai b) {return a.gal_med<b.gal_med;});
    else 
    {
        cout << "Tokio rikiavimo būdo nėra" << endl;
        return;
    }
}
void spausdinimo_parinkimas(vector <studentai> grupe, int nr_spausdinimas, int nr_rikiavimas, int n)
{
    if (n>0)
    {
        rikiavimas(nr_rikiavimas, grupe);
        if (nr_spausdinimas==1) spausdinimas(grupe);
        else if (nr_spausdinimas==2) spausdinimas_faile(grupe);
        else cout << "Tokio spausdinimo būdo nėra" << endl;
    }
    else cout << "Nėra duomenų" << endl;
}
void nuskaitymas(const string& failo_pavadinimas, vector<studentai>& grupe, int &n) {
    std::ios::sync_with_stdio(false); // Optimize input speed
    ifstream in(failo_pavadinimas);
    if (!in.is_open()) {
        cout << "Problema failo nuskaityme" << endl;
        return;
    }
    string eilute;
    //string laikina;
    //getline(in, eilute); // Skip the header line
    n=-3; // 3 - vardas, pavarde, egzamino pazymys
    if (getline(in, eilute)) {
        std::istringstream ss(eilute);
        n = std::distance(std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>()) - 3;
    }

    while (getline(in, eilute)) {
        std::istringstream iss(eilute);
        studentai temp;
        iss >> temp.vardas >> temp.pavarde;

        // Read grades efficiently
        temp.pazymiai.assign(std::istream_iterator<int>(iss), std::istream_iterator<int>());
        temp.egzam = temp.pazymiai.back(); // Last element is the exam grade
        temp.pazymiai.pop_back(); // Remove it from the vector
        grupe.push_back(std::move(temp)); // Move to optimize vector insertion
    }
    in.close();
}
void skaiciavimas(vector <studentai> &grupe, int n)
{
    for (auto& m:grupe)
    {
        m.suma=sumos_skaiciavimas(m.pazymiai, m);
        m.vidurkis=vidurkio_skaiciavimas(m.pazymiai, m);
        m.mediana=mediana_skaiciavimas(m.pazymiai, m);
        m.gal_vid=galutinis_vid_sk(m, m.vidurkis);
        m.gal_med=galutinis_med_sk(m, m.mediana);
    }
}

