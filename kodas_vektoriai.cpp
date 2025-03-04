#include "antrastes.h"
#include "strukt_antr.h"

#include <exception>
#include <limits>
// vėliau ištrint:
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::setw;

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

int main()
{
    try {
        srand(time(0)); //kiekvieną kartą generuojami nauji pažymiai
        cout << "Meniu (įveskite pasirinktos programos eigos nr.):" << endl;
        cout << "1 - ranka įveskite duomenis, 2 - generuoti pažymius, 3 - generuoti pažymius ir studentų vardus, 4 - baigti darbą, 5 - nuskaityti duomenis iš failo, 6 - failų generatorius" << endl;
        int nr_meniu;
        cin >> nr_meniu;

        vartotojo_pasirinkimas(nr_meniu, 1, 6);

        if (nr_meniu==4)
        {
            cout << "Darbas baigtas" << endl;
            return 0;
        }
        if (nr_meniu==6)
        {
            cout << "Kokio dydžio failą generuosime? (įveskite eilučių kiekį)" << endl;
            int nr_failo_dydis;
            cin >> nr_failo_dydis;
            string failo_pavadinimas;
            //int paz_kiekis=rand()%15+1; //galimas, bet visus failus bus vienodas
            int paz_kiekis=7;
            failo_pavadinimas="sukurtas_studentai"+std::to_string(nr_failo_dydis)+".txt";
            failo_generavimas(failo_pavadinimas, nr_failo_dydis, paz_kiekis);
            return 0;
        }
        cout << "Kaip išrikiuoti studentus? Pagal... \n 1 - vardą, 2 - pavardę, 3 - galutinį pažymį pagal vidurkį, 4 - galutinį pažymį pagal medianą" << endl;
        int nr_rikiavimas;
        cin >> nr_rikiavimas;
        vartotojo_pasirinkimas(nr_rikiavimas, 1, 4);
        /*
        while (ar_beda(nr_rikiavimas, 1, 4))
        {
            cout << "Tokio pasirinkimo nėra, pakartokite" << endl;
            cin >> nr_rikiavimas;
        }
        */
        cout << "Kaip norėsite išvesti duomenis? \n 1 - į ekraną, 2 - į failą" << endl;
        int nr_spausdinimas;
        cin >> nr_spausdinimas;
        vartotojo_pasirinkimas(nr_spausdinimas, 1, 2);
        /*
        while (ar_beda(nr_spausdinimas, 1, 2))
        {
            cout << "Tokio pasirinkimo nėra, pakartokite" << endl;
            cin >> nr_spausdinimas;
        }
            */  
        int m=0, n=0; //m-studentai, n-nd
        int paz, egz;
        vector <studentai> grupe;
        //grupes studentu pazymiai

        if (nr_meniu==5)
        {
            cout << "Išsirinkite darbinį failą: \n 1 - kursiokai.txt, 2 - studentai10000.txt, 3 - studentai100000.txt, 4 - studentai1000000.txt" << endl;
            int nr_failas=1; //default reiksme
            cin >> nr_failas;
            string failo_pavadinimas;
            if (nr_failas == 1) failo_pavadinimas = "kursiok4ai.txt";
            else if (nr_failas == 2) failo_pavadinimas = "studentai10000.txt";
            else if (nr_failas == 3) failo_pavadinimas = "studentai100000.txt";
            else if (nr_failas == 4) failo_pavadinimas = "studentai1000000.txt";
            else {
                cout << "Tokio failo nėra" << endl;
                return 0;
            }
            auto pradzia=std::chrono::high_resolution_clock::now();
            auto pradzia_pilna=std::chrono::high_resolution_clock::now();
            nuskaitymas(failo_pavadinimas, grupe, n);
            auto pabaiga = std::chrono::high_resolution_clock::now();
            auto trukme = std::chrono::duration_cast<std::chrono::seconds>(pabaiga - pradzia);
            cout << "Nuskaitymo vykdymo laikas: " << trukme.count() << "s" << endl;
            skaiciavimas(grupe, n);
            spausdinimo_parinkimas(grupe, nr_spausdinimas, nr_rikiavimas);
            auto pabaiga_pilna = std::chrono::high_resolution_clock::now();
            auto trukme_pilna = std::chrono::duration_cast<std::chrono::seconds>(pabaiga_pilna - pradzia_pilna);
            cout << "Programos vykdymo laikas: " << trukme_pilna.count() << "s" << endl;
        }

        else if (nr_meniu==1)
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
                vartotojo_pasirinkimas(n, 1, 15);
                /*
                while (ar_beda(n, 1, 15))
                {
                    cout << "Įveskite studento namų darbų kiekį (nuo 1 iki 15)" << endl;
                    cin >> n;
                }
                    */
                cout << "Įveskite studento namų darbų pažymius (nuo 0 iki 10)" << endl;
                for (int y=0; y<n; y++)
                {
                    cin >> paz;
                    vartotojo_pasirinkimas(paz, 0, 10);
                    /*
                    while (ar_beda(paz, 0, 10))
                    {
                        cout << "Įveskite studento namų darbų pažymius (nuo 0 iki 10)" << endl;
                        cin >> paz;
                    }
                        */
                    temp.suma+=paz;
                    temp.pazymiai.push_back(paz); //prideda paz elementa i vektoriaus pazymiai gala
                }
                temp.vidurkis=temp.suma/n;
                
                temp.mediana=mediana_skaiciavimas(temp.pazymiai, temp);

                cout << "Įveskite studento egzamino rezultatą (nuo 0 iki 10)" << endl;
                cin >> temp.egzam;
                vartotojo_pasirinkimas(temp.egzam, 0, 10);
                /*
                while (ar_beda(temp.egzam, 0, 10))
                {
                    cout << "Įveskite studento egzamino rezultatą (nuo 0 iki 10)" << endl;
                    cin >> temp.egzam;
                }
                    */
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
            spausdinimo_parinkimas(grupe, nr_spausdinimas, nr_rikiavimas);
        }
        else if (nr_meniu==2)
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
                    paz=rand_pazymys();
                    temp.suma+=paz;
                    temp.pazymiai.push_back(paz);
                }
                temp.vidurkis=temp.suma/n;
                
                temp.mediana=mediana_skaiciavimas(temp.pazymiai, temp);

                temp.egzam=rand_pazymys();
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
            spausdinimo_parinkimas(grupe, nr_spausdinimas, nr_rikiavimas);
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

                n=rand()%15+1;
                for (int y=0; y<n; y++)
                {
                    paz=rand_pazymys();
                    temp.suma+=paz;
                    temp.pazymiai.push_back(paz);
                }
                temp.vidurkis=temp.suma/n;
                
                temp.mediana=mediana_skaiciavimas(temp.pazymiai, temp);

                temp.egzam=rand_pazymys();
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
            spausdinimo_parinkimas(grupe, nr_spausdinimas, nr_rikiavimas);
        }
        cout << endl << "Darbas baigtas" << endl;
    } 
    catch (const std::exception& e)
    {
        cout << "Įvyko klaida: " << e.what() << endl;
    }
    catch (...) 
    {
        cout << "Įvyko nežinoma klaida" << endl;
    }
    return 0;
}