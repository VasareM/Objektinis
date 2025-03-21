#include "antrastes.h"

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

void vartotojo_pasirinkimas(int &nr_meniu, int a, int b)
{
    while (true) 
        {
            try 
            {
                if (!ar_beda_bendras(nr_meniu, a, b)) break;
            } 
            catch (const std::out_of_range& e) 
            {
                cout << e.what() << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the input
                cin >> nr_meniu;
            }
        }
}
bool ar_beda(int x, int pr, int pb)
{
    if (x<pr || x>pb)
    {
        cout << "Neteisinga įvestis" << endl;
        return true;
    }
    return false;
}
bool ar_beda_bendras(int x, int pr, int pb)
{
    if (x<pr || x>pb)
    {
        throw std::out_of_range("Neteisinga įvestis");
    }
    return false;
}
int rand_pazymys()
{
    int pazymys;
    pazymys=rand()%10+1;
    return pazymys;
}

void failo_generavimas(string failo_pavadinimas, int nr_failo_dydis, int paz_kiekis)
{
    std::ofstream out(failo_pavadinimas);
    out << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde";
    for( int i=1; i<=paz_kiekis; i++)
    {
        out << std::setw(10) << ("ND" + std::to_string(i));
    }
    out << std::setw(10) << "Egz." << std::endl;
    for (int i=0; i<nr_failo_dydis; i++)
    {
        out << std::left << std::setw(20) << ("VardasNR" + std::to_string(i + 1)) << std::setw(20) << ("PavardeNR" + std::to_string(i + 1));
        for (int j=0; j<paz_kiekis; j++)
        {
            out << std::setw(10) << rand_pazymys();
        }
        out << std::setw(10) << rand_pazymys() << std::endl;
    }
}
int mediana_skaiciavimas(vector <int> &pazymiai, studentai &temp)
{
    int n=temp.pazymiai.size(), med=0;
    std::sort(temp.pazymiai.begin(), temp.pazymiai.end());
    if (n%2==0)
    {
        med=((temp.pazymiai[n/2-1]+temp.pazymiai[n/2]))/2;
    }
    else 
    {
        med=temp.pazymiai[n/2];
    }
    temp.mediana = med;
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
        //for(const auto&n:m.pazymiai) cout << " " ;
        //cout << endl;
    }
}
void spausdinimas_faile(vector <studentai> grupe, const string& outputo_pavadinimas)
//template <typename Container>
//void spausdinimas_faile(const Container& grupe, const string& outputo_pavadinimas)
{
    ofstream out (outputo_pavadinimas);
    out << std::left << setw(25) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    out << string(85, '-') << endl;
    for (const auto&m:grupe) //visi elementai is eiles is grupes; const, kad nesikopijuot7
    {
        out << std::left << setw(25) << m.pavarde << setw(20) << m.vardas;
        out << setw(20) << std::fixed << std::setprecision(2) << m.gal_vid << setw(20) << m.gal_med << endl;
        //for(const auto&n:m.pazymiai) cout << n << " "               //cout << endl;
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
void spausdinimo_parinkimas(std::vector<studentai> grupe, int nr_spausdinimas, int nr_rikiavimas)
{
    if (!grupe.empty())
    {
        rikiavimas(nr_rikiavimas, grupe);
        if (nr_spausdinimas==1) spausdinimas(grupe);
        else if (nr_spausdinimas==2) spausdinimas_faile(grupe, "rezultatai.txt");
        else cout << "Tokio spausdinimo būdo nėra" << endl;
    }
    else cout << "Nėra duomenų" << endl;
}
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

void nuskaitymas(const string& failo_pavadinimas, vector<studentai>& grupe, int &n) 
//template <typename Container>
//void nuskaitymas(const string& failo_pavadinimas, Container& grupe, int &n) 
{
    std::ios::sync_with_stdio(false); // Optimize input speed
    ifstream in;
    try {
        in.open(failo_pavadinimas);
        if (!in.is_open()) {
            throw std::runtime_error("Problema failo nuskaityme");
        }
    } catch (const std::exception& e) {
        cout << e.what() << endl;
        return;
    }
    string eilute;

    n=-3; // 3 - vardas, pavarde, egzamino pazymys
    if (getline(in, eilute)) {
        std::istringstream ss(eilute);
        n = std::distance(std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>()) - 3;
    }
    while (getline(in, eilute)) 
    {
        std::istringstream iss(eilute);
        studentai temp;
        iss >> temp.vardas >> temp.pavarde;

        temp.pazymiai.assign(std::istream_iterator<int>(iss), std::istream_iterator<int>());
        if (!temp.pazymiai.empty()) {
            temp.egzam = temp.pazymiai.back();
            temp.pazymiai.pop_back(); // Remove from the vector
        } else {
            temp.egzam = 0; // Default to 0 if no grades are found
        }
        grupe.push_back(std::move(temp)); // to optimize vector insertion
    }
    in.close();
}
void skaiciavimas(vector <studentai> &grupe, int n)
//template <typename Container>
//void skaiciavimas(Container& grupe, int n)
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

