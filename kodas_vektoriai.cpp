#include "antrastes.h"

int main()
{
    srand(time(0)); //kiekvieną kartą generuojami nauji pažymiai
    
    cout << "Išsirinkite darbinį failą: \n 1 - kursiokai.txt, 2 - studentai10000.txt, 3 - studentai100000.txt, 4 - studentai1000000.txt" << endl;
    int nr_failas=1; //default reiksme
    cin >> nr_failas;
    
    cout << "Kaip išrūšiuoti studentus? Pagal... \n 1 - vardą, 2 - pavardę, 3 - galutinį pažymį pagal vidurkį, 4 - galutinį pažymį pagal medianą" << endl;
    int nr_rusiavimas;
    cin >> nr_rusiavimas;

    int m=0, n=15; //m-studentai, n-nd
    int paz, egz;
    vector <studentai> grupe; //vektorius-objektas, mokantis dirbti su 5vairiaus duomenimis
    //grupes studentu pazymiai

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
        while (!in.fail())
        {
            in >> temp.vardas >> temp.pavarde;
            //temp.suma=0;
            //temp.pazymiai.clear();
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
        spausdinimas(grupe);
        in.close();

    }
    
    else 
    {
        cout << "Problema failo nuskaityme" << endl; 
        return 0;
    }
}