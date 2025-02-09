#include "antrastes.h"

int main()
{
    int n, k;
    int paz, egz;
    vector <studentai> grupe;
    cin >> n;
    for (int i=0; i<n; i++)
    {
        studentai temp;
        cout << "Įveskite studento vardą ir pavardę" << endl;
        cin >> temp.vardas >> temp.pavarde;
        cout << "Įveskite studento namų darbų kiekį" << endl;
        cin >> k;
        cout << "Įveskite studento namų darbų pažymius" << endl;
        for (int y=0; y<k; y++)
        {
            cin >> paz;
            temp.pazymiai.push_back(paz); //prideda paz elementa i vektoriaus pazymiai gala
        }
        cout << "Įveskite studento egzamino rezultatą" << endl;
        cin >> temp.egzam;
        grupe.push_back(temp);
    }
    for (auto n:grupe)
    {
        cout << n.vardas << " " << n.pavarde << " ";
        for (auto y:n.pazymiai)
        {
            cout << y << " ";
        }
        cout << n.egzam << endl;
    }
    return 0;
}