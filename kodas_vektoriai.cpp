#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm> // kad veiktu sort

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
int main()
{
    int m, n;
    int paz, egz;
    vector <studentai> grupe; //vektorius-objektas, mokantis dirbti su 5vairiaus duomenimis
    //grupes studentu pazymiai
    cout << "Įveskite studentų skaičių" << endl;
    cin >> m;
    for (int i=0; i<m; i++)
    {
        studentai temp;
        cout << "Įveskite studento vardą ir pavardę" << endl;
        cin >> temp.vardas >> temp.pavarde;
        while (temp.vardas.size()>19 || temp.pavarde.size()>19)
        {
            cout << "Vardas arba pavardė per ilgi" << endl;
            cout << "Įveskite studento vardą ir pavardę" << endl;
            cin >> temp.vardas >> temp.pavarde;
        }
        cout << "Įveskite studento namų darbų kiekį (nuo 1 iki 15)" << endl;
        cin >> n;
        while (ar_beda(n, 1, 15))
        {
            cout << "Įveskite studento namų darbų kiekį (nuo 1 iki 15)" << endl;
            cin >> n;
        }
        cout << "Įveskite studento namų darbų pažymius (nuo 0 iki 10)" << endl;
        for (int y=0; y<n; y++)
        {
            cin >> paz;
            while (ar_beda(paz))
            {
                cout << "Įveskite studento namų darbų pažymius (nuo 0 iki 10)" << endl;
                cin >> paz;
            }
            temp.suma+=paz;
            temp.pazymiai.push_back(paz); //prideda paz elementa i vektoriaus pazymiai gala
        }
        temp.vidurkis=temp.suma/n;
        
        sort(temp.pazymiai.begin(), temp.pazymiai.end());
        {
            if (n%2==0)
            {
                temp.mediana=(temp.pazymiai[n/2-1]+temp.pazymiai[n/2]);
            }
            else 
            {
                temp.mediana=temp.pazymiai[n/2];
            }
        }
        //temp.mediana=median(temp.pazymiai);
        cout << "Įveskite studento egzamino rezultatą (nuo 0 iki 10)" << endl;
        cin >> temp.egzam;
        while (ar_beda(temp.egzam))
        {
            cout << "Įveskite studento egzamino rezultatą (nuo 0 iki 10)" << endl;
            cin >> temp.egzam;
        }
        //temp.gal_vid=average(temp.pazymiai)*0.4+temp.egzam*0.6;
        temp.gal_vid=0.4*temp.vidurkis+0.6*temp.egzam;
        temp.gal_med=0.4*temp.mediana+0.6*temp.egzam;
        grupe.push_back(temp);
    }
    cout << std::left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    cout << string(80, '-') << endl;
    for (auto m:grupe) //visi elementai is eiles is grupes
    {
        cout << std::left << setw(20) << m.pavarde << setw(20) << m.vardas;
        /*
        cout << " " ;
        for (auto y:m.pazymiai)
        {
            cout << y << " ";
        }
        */
        cout << /*setw(20) << m.egzam <<*/ setw(20) << std::fixed << std::setprecision(2) << m.gal_vid << setw(20) << m.gal_med << endl;
    }
    return 0;
}