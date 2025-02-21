#include "antrastes.h"


int main()
{
    srand(time(0)); //kiekvieną kartą generuojami nauji pažymiai
    cout << "Meniu (įveskite pasirinktos programos eigos nr.):" << endl;
    cout << "1 - ranka įveskite duomenis, 2 - generuoti pažymius, 3 - generuoti pažymius ir studentų vardus, 4 - baigti darbą, 5 - nuskaityti duomenis iš failo" << endl;
    int nr_meniu;
    cin >> nr_meniu;
    while (ar_beda(nr_meniu, 1, 5))
    {
        cout << "Tokio pasirinkimo nėra, pakartokite" << endl;
        cin >> nr_meniu;
    }
    if (nr_meniu==4)
    {
        cout << "Darbas baigtas" << endl;
        return 0;
    }
    cout << "Kaip išrikiuoti studentus? Pagal... \n 1 - vardą, 2 - pavardę, 3 - galutinį pažymį pagal vidurkį, 4 - galutinį pažymį pagal medianą" << endl;
    int nr_rikiavimas;
    cin >> nr_rikiavimas;
    while (ar_beda(nr_rikiavimas, 1, 4))
    {
        cout << "Tokio pasirinkimo nėra, pakartokite" << endl;
        cin >> nr_rikiavimas;
    }
    cout << "Kaip norėsite išvesti duomenis? \n 1 - į ekraną, 2 - į failą" << endl;
    int nr_spausdinimas;
    cin >> nr_spausdinimas;
    while (ar_beda(nr_spausdinimas, 1, 2))
    {
        cout << "Tokio pasirinkimo nėra, pakartokite" << endl;
        cin >> nr_spausdinimas;
    }
    int m=0, n=0; //m-studentai, n-nd
    int paz, egz;
    vector <studentai> grupe;
    //grupes studentu pazymiai

    if (nr_meniu==5)
    {
        auto pradzia=std::chrono::high_resolution_clock::now(); 
        //clock_t pradzia=clock();
        cout << "Išsirinkite darbinį failą: \n 1 - kursiokai.txt, 2 - studentai10000.txt, 3 - studentai100000.txt, 4 - studentai1000000.txt" << endl;
        int nr_failas=1; //default reiksme
        cin >> nr_failas;
        ifstream in;
        if (nr_failas==1) in.open("kursiokai.txt");
        else if (nr_failas==2) in.open("studentai10000.txt");
        else if (nr_failas==3) in.open("studentai100000.txt");
        else if (nr_failas==4) in.open("studentai1000000.txt");
        else 
        {
            cout << "Tokio failo nėra" << endl;
            return 0;
        }
        if(in.is_open())
        {
            studentai temp;  
            string temporary;
            //getline(in, temporary);
            n=0;
            while (in.peek()!='\n')
            {
                in >> temporary;
                n++;
            }
            n-=3;
            while (in >> temp.vardas >> temp.pavarde)
            {
                temp.suma = 0;
                temp.pazymiai.clear();
                for (int i = 0; i < n; i++)
                {
                    in >> paz;
                    temp.suma += paz;
                    temp.pazymiai.push_back(paz);
                }
                in >> temp.egzam;
                temp.vidurkis=static_cast<double>(temp.suma)/n;

                mediana_skaiciavimas(temp.pazymiai, n, temp);

                temp.gal_vid=0.4*temp.vidurkis+0.6*temp.egzam;
                temp.gal_med=0.4*temp.mediana+0.6*temp.egzam;
                grupe.push_back(temp);
                m++;
            }
            spausdinimo_parinkimas(grupe,nr_spausdinimas,nr_rikiavimas, n);
            in.close();
            auto pabaiga=std::chrono::high_resolution_clock::now();
            auto trukme = std::chrono::duration_cast<std::chrono::seconds>(pabaiga-pradzia);
            cout << "Programos vykdymo laikas: " << trukme.count() << "s" << endl;
        }
    
        else 
        {
            cout << "Problema failo nuskaityme" << endl; 
            return 0;
        }
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
        spausdinimo_parinkimas(grupe,nr_spausdinimas,nr_rikiavimas, n);
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
            paz=rand()%10+1;
            temp.suma+=paz;
            temp.pazymiai.push_back(paz);
        }
        temp.vidurkis=temp.suma/n;
        
        mediana_skaiciavimas(temp.pazymiai, n, temp);

        temp.egzam=rand()%10+1;
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
        spausdinimo_parinkimas(grupe,nr_spausdinimas,nr_rikiavimas, n);
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
            paz=rand()%10+1;
            temp.suma+=paz;
            temp.pazymiai.push_back(paz);
        }
        temp.vidurkis=temp.suma/n;
        
        mediana_skaiciavimas(temp.pazymiai, n, temp);

        temp.egzam=rand()%10+1;
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
        spausdinimo_parinkimas(grupe,nr_spausdinimas,nr_rikiavimas, n);
    }
    cout << endl << n << endl;

}