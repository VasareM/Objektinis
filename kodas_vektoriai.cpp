#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::vector;
using std ::string;
using std::endl;
using std::setw;

struct studentai
{
    string vardas;
    string pavarde;
    vector<int> pazymiai; //nd tarpiniai rezultatai
    int egzam;
    double suma=0;
    double vidurkis;
    int mediana;
    double gal_vid, gal_med;
};

int main()
{
    int m, n;
    int paz, egz;
    vector <studentai> grupe;
    cout << "Įveskite studentų skaičių" << endl;
    cin >> m;
    for (int i=0; i<m; i++)
    {
        studentai temp;
        cout << "Įveskite studento vardą ir pavardę" << endl;
        cin >> temp.vardas >> temp.pavarde;
        cout << "Įveskite studento namų darbų kiekį" << endl;
        cin >> n;
        cout << "Įveskite studento namų darbų pažymius" << endl;
        for (int y=0; y<n; y++)
        {
            cin >> paz;
            temp.suma+=paz;
            temp.pazymiai.push_back(paz); //prideda paz elementa i vektoriaus pazymiai gala
        }
        temp.vidurkis=temp.suma/n;
        cout << "Įveskite studento egzamino rezultatą" << endl;
        cin >> temp.egzam;
        temp.gal_vid=0.4*temp.vidurkis+0.6*temp.egzam;
        grupe.push_back(temp);
    }
    cout << std::left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << endl;
    cout << string(60, '-') << endl;
    for (auto m:grupe)
    {
        cout << std::left << setw(20) << m.vardas << setw(20) << m.pavarde;
        /*
        cout << " " ;
        for (auto y:m.pazymiai)
        {
            cout << y << " ";
        }
        */
        cout << /*setw(20) << m.egzam <<*/ setw(20) << std::fixed << std::setprecision(2) << m.gal_vid << endl;
    }
    return 0;
}