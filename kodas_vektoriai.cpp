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
using std::list;

void septintas_meniu(const string& failo_pavadinimas, int nr_failo_dydis, int nr_rikiavimas, int& n, int strategijos_nr)
{
    vector <studentai> grupe;
    auto failo_nuskaitymo_pradzia=std::chrono::high_resolution_clock::now();
    //cout << failo_pavadinimas << endl;
    nuskaitymas(failo_pavadinimas, grupe, n);
    auto failo_nuskaitymo_pabaiga = std::chrono::high_resolution_clock::now();
    auto failo_nuskaitymo_trukme = std::chrono::duration_cast<std::chrono::seconds>(failo_nuskaitymo_pabaiga - failo_nuskaitymo_pradzia);
    cout << "Failo iš " << nr_failo_dydis << " įrašų nuskaitymo laikas: " << std::fixed << std::setprecision(5) << failo_nuskaitymo_trukme.count() << "s" << endl;
    ///
    skaiciavimas(grupe, n);
    vector <studentai> galvociai, nelaimingi;
    if (strategijos_nr==3)
    {
        auto failo3_sort_pradzia=std::chrono::high_resolution_clock::now();
        auto perskyrimas = std::stable_partition(grupe.begin(), grupe.end(), [&](const studentai& s) {
            return (nr_rikiavimas == 3 && s.gal_vid < 5) || (nr_rikiavimas == 4 && s.gal_med < 5);
        });
        auto failo3_sort_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo3_sort_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(failo3_sort_pabaiga - failo3_sort_pradzia);
        cout << nr_failo_dydis << " įrašų rūšiavimas didėjimo tvarka laikas, su stable_partition funkcija: " << std::fixed << std::setprecision(5) << failo3_sort_trukme.count() << "s" << endl;
        auto failo3_dalijimo_pradzia=std::chrono::high_resolution_clock::now();

        nelaimingi.assign(grupe.begin(), perskyrimas);
        galvociai.assign(perskyrimas, grupe.end());
        auto failo3_dalijimo_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo3_dalijimo_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(failo3_dalijimo_pabaiga - failo3_dalijimo_pradzia);
        cout << nr_failo_dydis << " įrašų dalijimo į dvi grupes laikas: " << std::fixed << std::setprecision(5) << failo3_dalijimo_trukme.count() << "s" << endl;
    } 

    else 
    {
        auto failo_sort_pradzia=std::chrono::high_resolution_clock::now();
        rikiavimas(nr_rikiavimas, grupe);
        auto failo_sort_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo_sort_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(failo_sort_pabaiga - failo_sort_pradzia);
        cout << nr_failo_dydis << " įrašų rūšiavimas didėjimo tvarka laikas, su sort funkcija: " << std::fixed << std::setprecision(5) << failo_sort_trukme.count() << "s" << endl;
        
        auto failo_dalijimo_pradzia=std::chrono::high_resolution_clock::now();
        if (strategijos_nr==1)
        {
            for (int i=0; i<grupe.size(); i++)
            {
                if (nr_rikiavimas==3 && grupe[i].gal_vid<5 || nr_rikiavimas==4 && grupe[i].gal_med<5) nelaimingi.push_back(grupe[i]);
                else galvociai.push_back(grupe[i]);
            }
        }
        if (strategijos_nr==2)
        {
            vector<studentai> temp;
            for (const auto& student : grupe)
            {
                if ((nr_rikiavimas == 3 && student.gal_vid < 5) || (nr_rikiavimas == 4 && student.gal_med < 5))
                    nelaimingi.push_back(student);
                else
                    temp.push_back(student);
            }
            grupe = std::move(temp);
            /*
            for (int i=0; i<grupe.size(); i++)
            {
                if (nr_rikiavimas==3 && grupe[i].gal_vid<5 || nr_rikiavimas==4 && grupe[i].gal_med<5) 
                {
                    nelaimingi.push_back(grupe[i]);
                    grupe.erase(grupe.begin()+i);
                }
            }
            */
        }
        auto failo_dalijimo_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo_dalijimo_trukme = std::chrono::duration_cast<std::chrono::seconds>(failo_dalijimo_pabaiga - failo_dalijimo_pradzia);
        cout << nr_failo_dydis << " įrašų dalijimo į dvi grupes laikas: " << std::fixed << std::setprecision(5) << failo_dalijimo_trukme.count() << "s" << endl;    
    }

    spausdinimas_faile(nelaimingi, "nelaimingi.txt");
    if (strategijos_nr==1 || strategijos_nr==3) spausdinimas_faile(galvociai, "galvociai.txt");
    else if (strategijos_nr==2) spausdinimas_faile(grupe, "galvociai.txt");
    /*
    auto nelaimingu_pradzia=std::chrono::high_resolution_clock::now();
    spausdinimas_faile(nelaimingi, "nelaimingi.txt");
    auto nelaimingu_pabaiga = std::chrono::high_resolution_clock::now();
    auto nelaimingu_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(nelaimingu_pabaiga - nelaimingu_pradzia);
    cout << nr_failo_dydis << " įrašų nelaimingų įrašymo į failą laikas: " << std::fixed << std::setprecision(5) << nelaimingu_trukme.count() << "s" << endl;
    
    auto galvociu_pradzia=std::chrono::high_resolution_clock::now();
    spausdinimas_faile(galvociai, "galvociai.txt");
    auto galvociu_pabaiga = std::chrono::high_resolution_clock::now();
    auto galvociu_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(galvociu_pabaiga - galvociu_pradzia);
    cout << nr_failo_dydis << " įrašų galvočių įrašymo į failą laikas: " << std::fixed << std::setprecision(5) << galvociu_trukme.count() << "s" << endl;
    */
    cout << endl;
    auto pilna_pabaiga = std::chrono::high_resolution_clock::now();
    auto pilna_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(pilna_pabaiga - failo_nuskaitymo_pradzia);
    cout << nr_failo_dydis << " įrašų testo laikas: " << std::fixed << std::setprecision(5) << pilna_trukme.count() << "s" << endl;
    cout << endl << endl;
    
}
void list_veiksmai(const string& failo_pavadinimas, int nr_failo_dydis, int nr_rikiavimas, int& n, int strategijos_nr)
{
    vector <studentai> grupe;
    auto failo_nuskaitymo_pradzia=std::chrono::high_resolution_clock::now();
    nuskaitymas(failo_pavadinimas, grupe, n);
    auto failo_nuskaitymo_pabaiga = std::chrono::high_resolution_clock::now();
    auto failo_nuskaitymo_trukme = std::chrono::duration_cast<std::chrono::seconds>(failo_nuskaitymo_pabaiga - failo_nuskaitymo_pradzia);
    cout << "Failo iš " << nr_failo_dydis << " įrašų nuskaitymo laikas: " << std::fixed << std::setprecision(5) << failo_nuskaitymo_trukme.count() << "s" << endl;
    skaiciavimas(grupe, n);
    vector <studentai> galvociai, nelaimingi;
    if (strategijos_nr==3)
    {
        auto failo3_sort_pradzia=std::chrono::high_resolution_clock::now();
        auto perskyrimas = std::stable_partition(grupe.begin(), grupe.end(), [&](const studentai& s) {
            return (nr_rikiavimas == 3 && s.gal_vid < 5) || (nr_rikiavimas == 4 && s.gal_med < 5);
        });
        auto failo3_sort_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo3_sort_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(failo3_sort_pabaiga - failo3_sort_pradzia);
        cout << nr_failo_dydis << " įrašų rūšiavimas didėjimo tvarka laikas, su stable_partition funkcija: " << std::fixed << std::setprecision(5) << failo3_sort_trukme.count() << "s" << endl;
        auto failo3_dalijimo_pradzia=std::chrono::high_resolution_clock::now();

        nelaimingi.assign(grupe.begin(), perskyrimas);
        galvociai.assign(perskyrimas, grupe.end());
        auto failo3_dalijimo_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo3_dalijimo_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(failo3_dalijimo_pabaiga - failo3_dalijimo_pradzia);
        cout << nr_failo_dydis << " įrašų dalijimo į dvi grupes laikas: " << std::fixed << std::setprecision(5) << failo3_dalijimo_trukme.count() << "s" << endl;
    } 

    else 
    {
        auto failo_sort_pradzia=std::chrono::high_resolution_clock::now();
        rikiavimas(nr_rikiavimas, grupe);
        auto failo_sort_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo_sort_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(failo_sort_pabaiga - failo_sort_pradzia);
        cout << nr_failo_dydis << " įrašų rūšiavimas didėjimo tvarka laikas, su sort funkcija: " << std::fixed << std::setprecision(5) << failo_sort_trukme.count() << "s" << endl;
        
        auto failo_dalijimo_pradzia=std::chrono::high_resolution_clock::now();
        if (strategijos_nr==1)
        {
            for (int i=0; i<grupe.size(); i++)
            {
                if (nr_rikiavimas==3 && grupe[i].gal_vid<5 || nr_rikiavimas==4 && grupe[i].gal_med<5) nelaimingi.push_back(grupe[i]);
                else galvociai.push_back(grupe[i]);
            }
        }
        if (strategijos_nr==2)
        {
            vector<studentai> temp;
            for (const auto& student : grupe)
            {
                if ((nr_rikiavimas == 3 && student.gal_vid < 5) || (nr_rikiavimas == 4 && student.gal_med < 5))
                    nelaimingi.push_back(student);
                else
                    temp.push_back(student);
            }
            grupe = std::move(temp);
        }
        auto failo_dalijimo_pabaiga = std::chrono::high_resolution_clock::now();
        auto failo_dalijimo_trukme = std::chrono::duration_cast<std::chrono::seconds>(failo_dalijimo_pabaiga - failo_dalijimo_pradzia);
        cout << nr_failo_dydis << " įrašų dalijimo į dvi grupes laikas: " << std::fixed << std::setprecision(5) << failo_dalijimo_trukme.count() << "s" << endl;    
    }

    spausdinimas_faile(nelaimingi, "nelaimingi.txt");
    if (strategijos_nr==1 || strategijos_nr==3) spausdinimas_faile(galvociai, "galvociai.txt");
    else if (strategijos_nr==2) spausdinimas_faile(grupe, "galvociai.txt");

    cout << endl;
    auto pilna_pabaiga = std::chrono::high_resolution_clock::now();
    auto pilna_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(pilna_pabaiga - failo_nuskaitymo_pradzia);
    cout << nr_failo_dydis << " įrašų testo laikas: " << std::fixed << std::setprecision(5) << pilna_trukme.count() << "s" << endl;
    cout << endl << endl;
}
void deque_veiksmai(const string& failo_pavadinimas, int nr_failo_dydis, int nr_rikiavimas, int& n, int strategijos_nr)
{
    cout << "deque" << endl;
}


int main()
{
    try {
        srand(time(0)); //kiekvieną kartą generuojami nauji pažymiai
        cout << "Meniu (įveskite pasirinktos programos eigos nr.):" << endl;
        cout << "1 - ranka įveskite duomenis, 2 - generuoti pažymius, 3 - generuoti pažymius ir studentų vardus, 4 - baigti darbą;" << endl;
        cout << "5 - nuskaityti duomenis iš failo, 6 - failų generatorius;" << endl;
        cout <<  "7 - testavimas su vector \n8 - testavimas su list \n9 - testavimas su deque" << endl;
        cout << "10 - testavimas su visais konteineriais" << endl;
        int nr_meniu;
        cin >> nr_meniu;
        vartotojo_pasirinkimas(nr_meniu, 1, 10);
        if (nr_meniu==4)
        {
            cout << "Darbas baigtas" << endl;
            return 0;
        }
        if (nr_meniu==6)
        {
            cout << "Kokio dydžio failą generuosime? (įveskite eilučių kiekį)" << endl;
            int failu_dydziai[5];
            for (int i=0; i<5; i++) {
                cin >> failu_dydziai[i];
            }
            for (int i=0; i<5; i++) {
                int nr_failo_dydis=failu_dydziai[i];
                auto kurimo_pradzia=std::chrono::high_resolution_clock::now();
                //cin >> nr_failo_dydis;
                string failo_pavadinimas;
                //int paz_kiekis=rand()%15+1; //galimas, bet visus failus bus vienodas
                int paz_kiekis=7;
                failo_pavadinimas="sukurtas_studentai"+std::to_string(nr_failo_dydis)+".txt";
                failo_generavimas(failo_pavadinimas, nr_failo_dydis, paz_kiekis);
                auto kurimo_pabaiga = std::chrono::high_resolution_clock::now();
                auto kurimo_trukme = std::chrono::duration_cast<std::chrono::duration<double>>(kurimo_pabaiga - kurimo_pradzia);
                cout << "Failo " << failo_pavadinimas << " kūrimo laikas: " << std::fixed << std::setprecision(4) << kurimo_trukme.count() << "s" << endl;
                
            }
            return 0;
        }
        if (nr_meniu>=7 && nr_meniu<=10)
        {
            cout << "Kaip išrikiuoti studentus? Pagal... \n 3 - galutinį pažymį pagal vidurkį, 4 - galutinį pažymį pagal medianą" << endl;
            int nr_rikiavimas;
            cin >> nr_rikiavimas;
            vartotojo_pasirinkimas(nr_rikiavimas, 3, 4);
            cout << "Įveskite strategijos nr." << endl;
            cout << "1 - įprastas, dvi grupės, 2 - šalinami nelaimingi, 3 - efektyvūs metodai" << endl;
            int strategijos_nr;
            cin >> strategijos_nr;
            vartotojo_pasirinkimas(strategijos_nr, 1, 3);
            int n=0, nr_failo_dydis, failu_dydziai[5]={1000, 10000, 100000, 1000000, 10000000};
            string failo_pavadinimas;
            int kiek_failu=5;
            for (int i=0; i<kiek_failu; i++)
            {
                nr_failo_dydis=failu_dydziai[i];
                failo_pavadinimas="sukurtas_studentai"+std::to_string(nr_failo_dydis)+".txt";
                
                if (nr_meniu==7)
                {
                    septintas_meniu(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
                }
                if (nr_meniu==8)
                {
                    list_veiksmai(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
                }
                if (nr_meniu==9)
                {
                    deque_veiksmai(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
                }
            }
            if (nr_meniu==10)
            {
                for (int i=0; i<kiek_failu; i++)
                {
                    nr_failo_dydis=failu_dydziai[i];
                    failo_pavadinimas="sukurtas_studentai"+std::to_string(nr_failo_dydis)+".txt";
                    septintas_meniu(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
                    list_veiksmai(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
                    deque_veiksmai(failo_pavadinimas, nr_failo_dydis, nr_rikiavimas, n, strategijos_nr);
                
                }
            }

            return 0;
        }

        cout << "Kaip išrikiuoti studentus? Pagal... \n 1 - vardą, 2 - pavardę, 3 - galutinį pažymį pagal vidurkį, 4 - galutinį pažymį pagal medianą" << endl;
        int nr_rikiavimas;
        cin >> nr_rikiavimas;
        vartotojo_pasirinkimas(nr_rikiavimas, 1, 4);
        cout << "Kaip norėsite išvesti duomenis? \n 1 - į ekraną, 2 - į failą" << endl;
        int nr_spausdinimas;
        cin >> nr_spausdinimas;
        vartotojo_pasirinkimas(nr_spausdinimas, 1, 2);
        int m=0, n=0; //m-studentai, n-nd
        int paz, egz;
        vector <studentai> grupe;     //grupes studentu pazymiai
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