#include "antrastes.h"

//
/*
papildyt galimai output pasirinkimu
iskelt f-jas i antrastes
testavimas su failais
*/
//




int main()
{
    srand(time(0)); //kiekvieną kartą generuojami nauji pažymiai
    cout << "Meniu (įveskite pasirinktos programos eigos nr.):" << endl;
    cout << "1 - ranka įveskite duomenis, 2 - generuoti pažymius, 3 - generuoti pažymius ir studentų vardus, 4 - baigti darbą, 5 - nuskaityti duomenis iš failo" << endl;
    int nr_meniu;
    cin >> nr_meniu;
    cout << "Kaip išrikiuoti studentus? Pagal... \n 1 - vardą, 2 - pavardę, 3 - galutinį pažymį pagal vidurkį, 4 - galutinį pažymį pagal medianą" << endl;
    int nr_rikiavimas;
    cin >> nr_rikiavimas;
    cout << "Kaip norėsite išvesti duomenis? \n 1 - į ekraną, 2 - į failą" << endl;
    int nr_spausdinimas;
    cin >> nr_spausdinimas;
    int m=0, n=0; //m-studentai, n-nd
    int paz, egz;
    vector <studentai> grupe; //vektorius-objektas, mokantis dirbti su 5vairiaus duomenimis
    //grupes studentu pazymiai

    if (nr_meniu==5)
    {
        cout << "Išsirinkite darbinį failą: \n 1 - kursiokai.txt, 2 - studentai10000.txt, 3 - studentai100000.txt, 4 - studentai1000000.txt" << endl;
    int nr_failas=1; //default reiksme
    cin >> nr_failas;
    n=15;
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
        for (int i=0; i<18; i++)
        {
            in >> temporary;
        }
        while (in >> temp.vardas >> temp.pavarde)
        {
            
            temp.suma=0;
            temp.pazymiai.clear();
            for (int i=0; i<n; i++)
            {
                in >> paz;
                temp.suma+=paz;
                temp.pazymiai.push_back(paz);
            }
            in >> temp.egzam;
            temp.vidurkis=temp.suma/n;

            mediana_skaiciavimas(temp.pazymiai, n, temp);

            //temp.gal_vid=average(temp.pazymiai)*0.4+temp.egzam*0.6;
            temp.gal_vid=0.4*temp.vidurkis+0.6*temp.egzam;
            temp.gal_med=0.4*temp.mediana+0.6*temp.egzam;
            grupe.push_back(temp);
            m++;
        }
        spausdinimo_parinkimas(grupe,nr_spausdinimas,nr_rikiavimas);
        in.close();

    }
    
    else 
    {
        cout << "Problema failo nuskaityme" << endl; 
        return 0;
    }
    }
    else if (nr_meniu==4)
    {
        cout << "Darbas baigtas" << endl;
        return 0;
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
        spausdinimo_parinkimas(grupe,nr_spausdinimas,nr_rikiavimas);
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
        spausdinimo_parinkimas(grupe,nr_spausdinimas,nr_rikiavimas);
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
        spausdinimo_parinkimas(grupe,nr_spausdinimas,nr_rikiavimas);
    }


}