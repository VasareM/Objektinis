#include "antrastes.h"


void spausdinimas(vector <studentai> grupe)
{
    cout << std::left << setw(25) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    cout << string(85, '-') << endl;
    for (const auto&m:grupe) //visi elementai is eiles is grupes; const, kad nesikopijuot7
    {
        cout << std::left << setw(25) << m.pavarde << setw(20) << m.vardas;
        cout << setw(20) << std::fixed << std::setprecision(2) << m.gal_vid << setw(20) << m.gal_med << endl;
    }
}
void mediana_skaiciavimas(vector <int> &pazymiai, int n, studentai &temp)
{
    std::sort(temp.pazymiai.begin(), temp.pazymiai.end());
        {
            if (n%2==0)
            {
                temp.mediana=((temp.pazymiai[n/2-1]+temp.pazymiai[n/2]))/2;
            }
            else 
            {
                temp.mediana=temp.pazymiai[n/2];
            }
        }
        //temp.mediana=median(temp.pazymiai);
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

int main()
{
    srand(time(0)); //kiekvieną kartą generuojami nauji pažymiai
    cout << "Meniu (įveskite pasirinktos programos eigos nr.):" << endl;
    cout << "1 - ranka įveskite duomenis, 2 - generuoti pažymius, 3 - generuoti pažymius ir studentų vardus, 4 - baigti darbą" << endl;
    int nr_meniu;
    cin >> nr_meniu;
    
    int m, n;
    int paz, egz;
    vector <studentai> grupe; //vektorius-objektas, mokantis dirbti su 5vairiaus duomenimis
    //grupes studentu pazymiai
    
    if (nr_meniu==4)
    {
        cout << "Darbas baigtas" << endl;
        return 0;
    }

    if (nr_meniu==1)
    {
        cout << "Ar norite įvesti naujo studento duomenis? (T/n)" << endl;
        char ats;
        m=0;
        cin >> ats;
        if (ats=='n')
        {
            cout << "Darbas baigtas" << endl;
            return 0;
        }
    while (ats=='T')
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
        
        mediana_skaiciavimas(temp.pazymiai, n, temp);

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
        m++;
        cout << "Ar norite įvesti naujo studento duomenis? (T/n)" << endl;
        cin >> ats;
        if (ats=='n')
        {
            break;
        }
    }
        spausdinimas(grupe);
    }
    if (nr_meniu==2)
    {
        cout << "Ar norite įvesti naujo studento duomenis? (T/n)" << endl;
        char ats;
        m=0;
        cin >> ats;
    while (ats=='T')
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
        /*
        cout << "Įveskite studento namų darbų kiekį (nuo 1 iki 15)" << endl;
        cin >> n;
        while (ar_beda(n, 1, 15))
        {
            cout << "Įveskite studento namų darbų kiekį (nuo 1 iki 15)" << endl;
            cin >> n;
        }
        */
        n=rand()%15+1;
        for (int y=0; y<n; y++)
        {
            paz=rand()%10+1;
            temp.suma+=paz;
            temp.pazymiai.push_back(paz); //prideda paz elementa i vektoriaus pazymiai gala
        }
        temp.vidurkis=temp.suma/n;
        
        mediana_skaiciavimas(temp.pazymiai, n, temp);

        temp.egzam=rand()%10+1;
        //temp.gal_vid=average(temp.pazymiai)*0.4+temp.egzam*0.6;
        temp.gal_vid=0.4*temp.vidurkis+0.6*temp.egzam;
        temp.gal_med=0.4*temp.mediana+0.6*temp.egzam;
        grupe.push_back(temp);
        m++;
        cout << "Ar norite įvesti naujo studento duomenis? (T/n)" << endl;
        cin >> ats;
        if (ats=='n')
        {
            break;
        }
    }
        spausdinimas(grupe);
    }
    else if (nr_meniu==3)
    {
        cout << "Ar norite įvesti naujo studento duomenis? (T/n)" << endl;
        char ats;
        m=0;
        cin >> ats;
    while (ats=='T')
    {
        studentai temp;

    ////////////////////////
        temp.vardas=vardo_generavimas();
        temp.pavarde=pavardes_generavimas();
    ////////////////////////
        /*
        cout << "Įveskite studento namų darbų kiekį (nuo 1 iki 15)" << endl;
        cin >> n;
        while (ar_beda(n, 1, 15))
        {
            cout << "Įveskite studento namų darbų kiekį (nuo 1 iki 15)" << endl;
            cin >> n;
        }
        */
        n=rand()%15+1;
        for (int y=0; y<n; y++)
        {
            paz=rand()%10+1;
            temp.suma+=paz;
            temp.pazymiai.push_back(paz); //prideda paz elementa i vektoriaus pazymiai gala
        }
        temp.vidurkis=temp.suma/n;
        
        mediana_skaiciavimas(temp.pazymiai, n, temp);

        temp.egzam=rand()%10+1;
        //temp.gal_vid=average(temp.pazymiai)*0.4+temp.egzam*0.6;
        temp.gal_vid=0.4*temp.vidurkis+0.6*temp.egzam;
        temp.gal_med=0.4*temp.mediana+0.6*temp.egzam;
        grupe.push_back(temp);
        m++;
        cout << "Ar norite įvesti naujo studento duomenis? (T/n)" << endl;
        cin >> ats;
        if (ats=='n')
        {
            break;
        }
    }
        spausdinimas(grupe);
    }
    
    return 0;
    
}